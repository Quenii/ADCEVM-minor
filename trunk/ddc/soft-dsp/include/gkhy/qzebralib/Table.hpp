#pragma once

#include "gkhy\qzebralib\qzebra_lib_global.hpp"
#include "gkhy\qzebralib\TableData.hpp"
#include <vector>
#include <list>
#include <assert.h>
#include <WinSock2.h>
#include <QObject>

namespace gkhy 
{
	namespace QZebraLib 
	{

		class QZEBRA_LIB_EXPORT Table : public QObject
		{
			Q_OBJECT

		public:
			enum Endian	{ NetEndian, HostEndian };
			enum ComponentCode : long
			{
				//DummyComponentCode	= 0xFFFF, 

				ConfigAckTab_Succeeded	= 0,
				RejectionTab_Code		= -2,
				NegtiveTab				= -1,

				HdrTab			= 0x3000,
				GlobalHdrTab	= 0x3001,
				DmuTab1			= 0x3010,
				DmuTab2			= 0x3011,
				MduTab			= 0x3020,
				DpuTab1			= 0x3070,
				DpuTab2			= 0x3071,
				DpuTab3			= 0x3072,
				DrgTab			= 0x3040,
				DruTab1			= 0x3041,
				DruTab2			= 0x3042,
				DruTab3			= 0x3043,
				HdrProjectTab	= 0x3080,
				AllComponentTab = 0x3100,

				VectorTab		= 0x4000, // not compitable with cortex
				ProbeTab		= 0x8000
			};

		public:
			Table(QObject* parent);
			virtual ~Table(void); 
			void copyFrom(Table& tab)
			{ 
				if(getComponentCode() == tab.getComponentCode())
				{
					setData(tab.getData(), tab.getEndian());
				}
				else
				{
					Q_ASSERT(false);
				}
			}

		public:						
			
			// ������Ϊlen(��byteΪ��λ)�����ݿ����������m_table
			virtual void setData(const void* data, Endian endian);
			virtual void* getData(void) = 0;		
			virtual int getDataLength(void) = 0;		

			// ��������m_table��parameter(������componentCode)�ĵ�ַ			
			virtual void* getParameter(void) = 0;
			// ��������m_table��parameter(������componentCode)
			virtual void setParameter(const void* addr, Endian endian);
			virtual int getParameterLength(void) = 0;		

			virtual ComponentCode  getComponentCode(void) = 0; 
			virtual void setComponentCode(ComponentCode nComponentCode)  = 0;			

			virtual bool verifyTable(int nComponentCode) = 0; 				

			Table::Endian getEndian() { return HostEndian; }			

		protected:
			// len - counted in sizeof(unsigned long)
			void copy(unsigned long* dest, const unsigned long* src, int len, Endian srcEndian);
		};


		/**
		 * class template.
		 * TableDataType refers to TableData.hpp
		 */
		template <class TableDataType>
		class  InstTable : public Table
		{
		public:
			InstTable(QObject* parent = 0) : Table(parent) {} 
			virtual ~InstTable(void) {}

		public:
			/**
			 *
			 * ����m_table�ĵ�ַ
			 *
			 */
			void* getData() { return &m_table; }

			/**
			 *
			 * ����m_table�ĳ���
			 *
			 */
			int getDataLength(void)  { return sizeof(TableDataType); }

			/**
			 *
			 * ����parameter��ĳ���
			 *
			 */
			int getParameterLength(void){ return sizeof(TableDataType) - sizeof(m_table.componentCode); }
			
			/**
			 *
			 * ����m_table��component code
			 *
			 */
			ComponentCode  getComponentCode(void) { return (ComponentCode)m_table.componentCode; }

			/**
			 *
			 * ����m_table��component code
			 *
			 */
			void setComponentCode(ComponentCode nComponentCode) { m_table.componentCode = nComponentCode; }

			/**
			 *
			 * ��֤Table
			 *
			 */
			bool verifyTable(int nComponentCode)
			{
				return (nComponentCode == m_table.componentCode)? true : false;
			}

			TableDataType& getTableData() { return m_table; }

		
			/**
			 *
			 * ����parameter����ʼ��ַ
			 *
			 */
			void* getParameter(){return (char*)&m_table + 4;}		

		protected:
			TableDataType m_table;
		};

		///////////////////////////////////////////////////////////////////////////////////////////
		// These tables belong to CMonitoringFlow 

		// MonitorReqTable��componentCode��Ҫ���û�ָ��,Ĭ����0x3010(Table::DmuTab1)
		class MonitorReqTable:public InstTable < MonitorReqTableData >
		{
		public:
			MonitorReqTable(QObject* parent = 0) : InstTable < MonitorReqTableData >(parent)
			{
				setComponentCode(Table::DmuTab1);
			}

			~MonitorReqTable(){}
		};

		typedef InstTable < HySeriesTableData > HySeriesTable;// component code:0,�Ѿ���HySeriesTableData���趨
		typedef InstTable < ConfigNamesTableData > ConfigNamesTable;// component code:200H,�Ѿ���ConfigNamesTableData���趨
		typedef InstTable < GlobHySeriesTableData > GlobHySeriesTable;// component code:201H,�Ѿ���GlobHySeriesTableData���趨
		typedef InstTable < AllHySeriesTableData > AllHySeriesTable;// component code:210H,�Ѿ���AllHySeriesTableData���趨
		typedef InstTable < AllHyProductTableData > AllHyProductTable;// component code:2FFH,�Ѿ���AllHyProductTableData���趨

		typedef InstTable < HdrTableData > HdrTable;// component code:3000H,�Ѿ���HdrTableData�趨

		// component code:3001H,�Ѿ���GlobalHdrTableData���趨
		class GlobalHdrTable:public InstTable < GlobalHdrTableData >
		{
		public:
			GlobalHdrTable(QObject* parent = 0) : InstTable < GlobalHdrTableData >(parent)  {}
			virtual ~GlobalHdrTable(){}
		public:
			/**
			 *
			 * ���Test Modulator �Ƿ�mounted
			 *
			 */
			bool mduMounted()
			{
				return (1 == m_table.TestModulator)? true : false;
			}
			
			/**
			 *
			 * ���DPU �Ƿ� mounted
			 *
			 */
			bool dpuMounted(){return (0 == m_table.DataProcessingUnit)?false : true;}
			
			/**
			 *
			 * �ֱ���DPU1,2,3�Ƿ�mounted
			 *
			 */
			bool dpu1Mounted(){return (1 == (m_table.DataProcessingUnit&1))? true : false;}
			bool dpu2Mounted(){return (2 == (m_table.DataProcessingUnit&1))? true : false;}
			bool dpu3Mounted(){return (4 == (m_table.DataProcessingUnit&1))? true : false;}

			/**
			 *
			 * ���dmu2�Ƿ�mounted,��dmu1����mounted(�μ��ĵ�)
			 *
			 */
			bool dmu2Mounted(){return (1 == m_table.DemodulatorUnit)? true : false;}

			/**
			 *
			 * ���DRU �Ƿ� mounted
			 *
			 */
			bool druMounted(){return (0 == m_table.DataRecordingUnit)?false : true;}

			/**
			 *
			 * �ֱ���DRU1,2,3�Ƿ�mounted
			 *
			 */
			bool dru1Mounted(){return (1 == (m_table.DataRecordingUnit&1))? true : false;}
			bool dru2Mounted(){return (2 == (m_table.DataRecordingUnit&1))? true : false;}
			bool dru3Mounted(){return (4 == (m_table.DataRecordingUnit&1))? true : false;}

		};
	
		// DmuTable/DpuTable/DruTable��componentCode���û��ĳ��Լ���Ҫ��ֵ
		
		// component code:3010H/3011,��Ҫ������ʱ�趨,Ĭ��Ϊ0x3010(Table::DmuTab1)
		class DmuTable:public InstTable < DmuTableData >
		{
		public:
			DmuTable(QObject* parent = 0) : InstTable < DmuTableData >(parent)
			{
				setComponentCode(Table::DmuTab1);
			}
			~DmuTable(){}
		};
		typedef InstTable < TestModulatorTableData > TestModulatorTable;// component code:3020H(���趨��)

		// component code:3070H/3071/3072, Data processing table,��Ҫ������ʱ�趨,Ĭ��Ϊ0x3070(Table::DpuTab1)
		class DpuTable:public InstTable < DpuTableData >
		{
		public:
			DpuTable(QObject* parent = 0) :  InstTable < DpuTableData >(parent)
			{
				setComponentCode(Table::DpuTab1);
			}
			~DpuTable(){}
		};
		typedef InstTable < DrgTableData > DrgTable;// component code:3040H(���趨��), Data Recording Global table

		// component code:3041H/3043/3042, Data Recording Unit table,��Ҫ������ʱ�趨,Ĭ��Ϊ0x3041(Table::DruTab1)
		class DruTable:public InstTable < DruTableData >
		{
		public:
			DruTable(QObject* parent = 0) : InstTable < DruTableData >(parent) 
			{
				setComponentCode(Table::DruTab1);
			}
			~DruTable(){}
		};
		typedef InstTable < HdrProSpeTableData > HdrProSpeTable;// component code:3080H(���趨��), HDR project specific table
		

		// rejectionCode�Ѿ���RejectionTableData���趨
		class RejectionTable:public InstTable < RejectionTableData >
		{
		public:
			RejectionTable(QObject* parent = 0) : InstTable < RejectionTableData >(parent) {}
			~RejectionTable(){}
		private:
			// no componentCode,ʹ�ø�component��صĺ���û������
			void setComponentCode(ComponentCode nComponentCode){}
			ComponentCode  getComponentCode(void) { return RejectionTab_Code; }

			// ʹ�ø�parameter��صĺ���û������
			void* getParameter(){return getData();}
			int getParameterLength(void){return sizeof(RejectionTableData);}
		};

		// negtiveCode�Ѿ��趨��
		class NegtiveTable:public InstTable < NegtiveTableData >
		{
		public:
			NegtiveTable(QObject* parent = 0) : InstTable < NegtiveTableData >(parent) { }
			~NegtiveTable(){}
			
		private:
			// no componentCode,ʹ�ø�component��صĺ���û������
			void setComponentCode(ComponentCode nComponentCode){}
			ComponentCode  getComponentCode(void){return NegtiveTab;}
			
			// ʹ�ø�parameter��صĺ���û������
			void* getParameter(){return getData();}
			int getParameterLength(void){return sizeof(NegtiveTableData);}
		};
		//////////////////////////////////////////////////////////////////////////////////////////




		//////////////////////////////////////////////////////////////////////////////////////////
		// These tables belong to CControlFlow

		// component code��Ҫ�û��趨,Ĭ��Ϊ0x3010(Table::DmuTab1)
		class DmuConfigTable:public InstTable < DmuConfigTableData >
		{
		public:
			DmuConfigTable(QObject* parent = 0) :  InstTable < DmuConfigTableData >(parent)
			{
				setComponentCode(Table::DmuTab1);
			}
			~DmuConfigTable(){}
		};
		
		// component code��Ҫ�û��趨,����Ĭ��Ϊ3070H(Table::DpuTab1)
		class DpuConfigTable:public InstTable < DpuConfigTableData >
		{
		public:
			DpuConfigTable(QObject* parent = 0) : InstTable < DpuConfigTableData >(parent)
			{
				setComponentCode(Table::DpuTab1);
			}
			~DpuConfigTable(){}
		};
		typedef InstTable < GlobalHdrConfigTableData > GlobalHdrConfigTable;// component code:3001H(���趨��)

		// componentCode��Ҫ�û��趨,Ĭ��Ϊ0x3010(Table::DmuTab1)
		class ResetBerTable:public InstTable < ResetBerTableData >
		{
		public:
			ResetBerTable(QObject* parent = 0) :  InstTable < ResetBerTableData >(parent)
			{
				setComponentCode(Table::DmuTab1);
			}
			~ResetBerTable(){}
		};
		
		// �Ѿ��趨��
		class ConfigAckTable:public InstTable < ConfigAckTableData >
		{
		public:
			ConfigAckTable(QObject* parent = 0) : InstTable < ConfigAckTableData >(parent) 
			{

			}
			~ConfigAckTable(){}
			
		private:
			// no componentCode,ʹ�ø�component��صĺ���û������
			void setComponentCode(ComponentCode nComponentCode){}
			/*ComponentCode getComponentCode(void)
			{
				return DummyComponentCode; 
			}*/

			//	ʹ�ø�parameter��صĺ���û������
			int getParameterLength(void){return sizeof(ConfigAckTableData);}
			void* getParameter(){return getData();}
		};
		/////////////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////////////
		// These tables belong to CVectorAnalysisFlow
		typedef InstTable < VectorAnalysisRequestTableData > VectorAnalysisRequestTable;//�趨��componentCode
		typedef InstTable < NegativeVectorAnalysisAckTableData > NegativeVectorAnalysisAckTable;//�趨��componentCode
		//typedef InstTable < VectorAnalysisDataMsgTableData > VectorAnalysisDataMsgTable;// ����ҪcomponentCode
		class VectorAnalysisDataMsgTable : public InstTable < VectorAnalysisDataMsgTableData >		
		{
		public:
			VectorAnalysisDataMsgTable(QObject* parent = 0) :  InstTable < VectorAnalysisDataMsgTableData >(parent)
			{
				setComponentCode(Table::VectorTab);
			}

			~VectorAnalysisDataMsgTable(){}
		};

		typedef InstTable < ProbeRequestTableData > ProbeRequestTable;//�趨��componentCode
		typedef InstTable < NegativeProbeAckTableData > NegativeProbeAckTable;//�趨��componentCode

		class ProbeTable : public InstTable < ProbeTableData >		
		{
		public:
			ProbeTable(QObject* parent = 0) :  InstTable < ProbeTableData >(parent)
			{
				setComponentCode(Table::ProbeTab);
			}

			~ProbeTable(){}
		};
			
		/////////////////////////////////////////////////////////////////////////////////////////


		//////////////////////////////////////////////////////////////////////////////////////////
		// These tables belong to TelemetryFlow(ң������)
		typedef InstTable < TelemetryRequestTableData > TelemetryDataRequestTable;// ����ҪcomponentCode
		//////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////
		// component code:3100H(���趨��), All component tables
		class AllComponentTable : public InstTable < AllComponentTableData >
		{
		public:			
			AllComponentTable(QObject* parent = 0);
			~AllComponentTable();

		public:
			/**
			 * ����Table�е�ͬ������,�ڴ˺����н�����һЩtable
			 */
			void setComponentCode(int nComponentCode);

			/**
			 *
			 * �����û���������data,�����Ҫ����AllComponentTable,������allCompTable
			 * �����Ҫ���õ���table,���������table.
			 *
			 */
			void setData(const void* data, int len, Endian endian);

			/**
			 *
			 * ����m_validTableList������
			 *
			 */
			std::list<Table*>& getValidTableList();

			/**
			 * ����m_allTableList������
			 */
			std::list<Table*>& getAllTableList();

			/**
			 *
			 * ����m_validTableVec�ĵ�ַ
			 *
			 */
			void* getData(void);
			
			/**
			 *
			 * ����m_validTableList�����б��ĳ���֮��
			 * ���m_validTableList�д�ŵ���allCompTable,�򷵻�allCompTable�ĳ���
			 * ���m_validTableList�д�ŵ�ĳ��Table���򷵻����Table�ĳ���
			 * ���򷵻�0
			 *
			 */
			int getDataLength(void);


			/**
			 * ����Endian״̬
			 */
			//void setEndian(Endian newEndian, bool doParameterConversion);

			/**
			 *
			 * ����componentCode��m_allTableList�еõ�subtable
			 * �����m_allTableList�����ҵ���,��ok = true;����ok=false 
			 *
			 */
			void getSubTable(Table **table, int componentCode, bool& ok);

			/**
			 * ���table�Ϸ�(����componentCode��m_allTableList�е�ĳ��table��componentCode���),
			 * ��table���뵽m_validTableList�в�����true;���򷵻�false
			 */
			bool insertValidTable(Table& table);

		private:
			/**
			 *
			 * ����gobal hdr table���¹�����Ӧ��table
			 *
			 */
			bool reMountTable(int len);

			/**
			 *
			 * ��m_validTableList��table������m_tableVector
			 * �����õ���AllComponentTable,����ʱ,��componentCode = 0x3010
			 * ����,��componentCode = m_validTableList�ĵ�һ��table��componentCode
			 *
			 */
			void copyDataToVector();

		private:
			HdrTable m_HdrTable;// component code:3000H
			GlobalHdrTable m_GlobalHdrTable;// component code:3001H
			DmuTable m_DmuTable1;// component code:3010H
			DmuTable m_DmuTable2;// component code:3011H
			TestModulatorTable m_testModulatorTable;// component code: 3020H
			DpuTable m_dpuTable1;// component code:3070H
			DpuTable m_dpuTable2;// component code:3071H
			DpuTable m_dpuTable3;// component code:3072H
			DrgTable m_DrgTable;// component code:3040H
			DruTable m_druTable1;// component code:3041H
			DruTable m_druTable2;// component code:3042H
			DruTable m_druTable3;// component code:3043H
			HdrProSpeTable m_hdrProSpeTable;// component code:3080H

			std::list <Table*> m_allTableList;// ������table���ص���list��,��ʱ����������
			std::list <Table*> m_validTableList;// �û����õ�table���ص���list��,�п����ǵ���table,Ҳ�п�����AllComponentTab

			std::vector <unsigned char> m_validTableVector;// ���û����õ�table�����ݿ�������vector��

			bool m_bAllCompTab;// ����trueʱ,��ʾ�û����õ���AllComponentTable			
		};
		//////////////////////////////////////////////////////////////////////////////////////////

		class TelemetryTable: public InstTable < TelemetryTableData >
		{
		public:
			TelemetryTable(QObject* parent = 0) : InstTable < TelemetryTableData >(parent) 	{ }
			~TelemetryTable(){}
		private:
			// no componentCode,ʹ�ø�component��صĺ���û������
			void setComponentCode(ComponentCode nComponentCode){}
			ComponentCode getComponentCode(void){ assert(false); return (ComponentCode)0; }

			//	ʹ�ø�parameter��صĺ���û������
			int getParameterLength(void){return sizeof(TelemetryTableData);}
			void* getParameterAddr(){return getData();}			
		};

	}

}