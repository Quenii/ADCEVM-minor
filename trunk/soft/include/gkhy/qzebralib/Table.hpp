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
			
			// 将长度为len(以byte为单位)的数据拷贝给子类的m_table
			virtual void setData(const void* data, Endian endian);
			virtual void* getData(void) = 0;		
			virtual int getDataLength(void) = 0;		

			// 返回子类m_table的parameter(不包括componentCode)的地址			
			virtual void* getParameter(void) = 0;
			// 设置子类m_table的parameter(不包括componentCode)
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
			 * 返回m_table的地址
			 *
			 */
			void* getData() { return &m_table; }

			/**
			 *
			 * 返回m_table的长度
			 *
			 */
			int getDataLength(void)  { return sizeof(TableDataType); }

			/**
			 *
			 * 返回parameter域的长度
			 *
			 */
			int getParameterLength(void){ return sizeof(TableDataType) - sizeof(m_table.componentCode); }
			
			/**
			 *
			 * 返回m_table的component code
			 *
			 */
			ComponentCode  getComponentCode(void) { return (ComponentCode)m_table.componentCode; }

			/**
			 *
			 * 设置m_table的component code
			 *
			 */
			void setComponentCode(ComponentCode nComponentCode) { m_table.componentCode = nComponentCode; }

			/**
			 *
			 * 验证Table
			 *
			 */
			bool verifyTable(int nComponentCode)
			{
				return (nComponentCode == m_table.componentCode)? true : false;
			}

			TableDataType& getTableData() { return m_table; }

		
			/**
			 *
			 * 返回parameter的起始地址
			 *
			 */
			void* getParameter(){return (char*)&m_table + 4;}		

		protected:
			TableDataType m_table;
		};

		///////////////////////////////////////////////////////////////////////////////////////////
		// These tables belong to CMonitoringFlow 

		// MonitorReqTable的componentCode需要由用户指定,默认是0x3010(Table::DmuTab1)
		class MonitorReqTable:public InstTable < MonitorReqTableData >
		{
		public:
			MonitorReqTable(QObject* parent = 0) : InstTable < MonitorReqTableData >(parent)
			{
				setComponentCode(Table::DmuTab1);
			}

			~MonitorReqTable(){}
		};

		typedef InstTable < HySeriesTableData > HySeriesTable;// component code:0,已经在HySeriesTableData中设定
		typedef InstTable < ConfigNamesTableData > ConfigNamesTable;// component code:200H,已经在ConfigNamesTableData中设定
		typedef InstTable < GlobHySeriesTableData > GlobHySeriesTable;// component code:201H,已经在GlobHySeriesTableData中设定
		typedef InstTable < AllHySeriesTableData > AllHySeriesTable;// component code:210H,已经在AllHySeriesTableData中设定
		typedef InstTable < AllHyProductTableData > AllHyProductTable;// component code:2FFH,已经在AllHyProductTableData中设定

		typedef InstTable < HdrTableData > HdrTable;// component code:3000H,已经在HdrTableData设定

		// component code:3001H,已经在GlobalHdrTableData中设定
		class GlobalHdrTable:public InstTable < GlobalHdrTableData >
		{
		public:
			GlobalHdrTable(QObject* parent = 0) : InstTable < GlobalHdrTableData >(parent)  {}
			virtual ~GlobalHdrTable(){}
		public:
			/**
			 *
			 * 检查Test Modulator 是否mounted
			 *
			 */
			bool mduMounted()
			{
				return (1 == m_table.TestModulator)? true : false;
			}
			
			/**
			 *
			 * 检查DPU 是否 mounted
			 *
			 */
			bool dpuMounted(){return (0 == m_table.DataProcessingUnit)?false : true;}
			
			/**
			 *
			 * 分别检查DPU1,2,3是否mounted
			 *
			 */
			bool dpu1Mounted(){return (1 == (m_table.DataProcessingUnit&1))? true : false;}
			bool dpu2Mounted(){return (2 == (m_table.DataProcessingUnit&1))? true : false;}
			bool dpu3Mounted(){return (4 == (m_table.DataProcessingUnit&1))? true : false;}

			/**
			 *
			 * 检查dmu2是否mounted,而dmu1必须mounted(参见文档)
			 *
			 */
			bool dmu2Mounted(){return (1 == m_table.DemodulatorUnit)? true : false;}

			/**
			 *
			 * 检查DRU 是否 mounted
			 *
			 */
			bool druMounted(){return (0 == m_table.DataRecordingUnit)?false : true;}

			/**
			 *
			 * 分别检查DRU1,2,3是否mounted
			 *
			 */
			bool dru1Mounted(){return (1 == (m_table.DataRecordingUnit&1))? true : false;}
			bool dru2Mounted(){return (2 == (m_table.DataRecordingUnit&1))? true : false;}
			bool dru3Mounted(){return (4 == (m_table.DataRecordingUnit&1))? true : false;}

		};
	
		// DmuTable/DpuTable/DruTable的componentCode由用户改成自己需要的值
		
		// component code:3010H/3011,需要在运行时设定,默认为0x3010(Table::DmuTab1)
		class DmuTable:public InstTable < DmuTableData >
		{
		public:
			DmuTable(QObject* parent = 0) : InstTable < DmuTableData >(parent)
			{
				setComponentCode(Table::DmuTab1);
			}
			~DmuTable(){}
		};
		typedef InstTable < TestModulatorTableData > TestModulatorTable;// component code:3020H(已设定好)

		// component code:3070H/3071/3072, Data processing table,需要在运行时设定,默认为0x3070(Table::DpuTab1)
		class DpuTable:public InstTable < DpuTableData >
		{
		public:
			DpuTable(QObject* parent = 0) :  InstTable < DpuTableData >(parent)
			{
				setComponentCode(Table::DpuTab1);
			}
			~DpuTable(){}
		};
		typedef InstTable < DrgTableData > DrgTable;// component code:3040H(已设定好), Data Recording Global table

		// component code:3041H/3043/3042, Data Recording Unit table,需要在运行时设定,默认为0x3041(Table::DruTab1)
		class DruTable:public InstTable < DruTableData >
		{
		public:
			DruTable(QObject* parent = 0) : InstTable < DruTableData >(parent) 
			{
				setComponentCode(Table::DruTab1);
			}
			~DruTable(){}
		};
		typedef InstTable < HdrProSpeTableData > HdrProSpeTable;// component code:3080H(已设定好), HDR project specific table
		

		// rejectionCode已经在RejectionTableData中设定
		class RejectionTable:public InstTable < RejectionTableData >
		{
		public:
			RejectionTable(QObject* parent = 0) : InstTable < RejectionTableData >(parent) {}
			~RejectionTable(){}
		private:
			// no componentCode,使用跟component相关的函数没有意义
			void setComponentCode(ComponentCode nComponentCode){}
			ComponentCode  getComponentCode(void) { return RejectionTab_Code; }

			// 使用跟parameter相关的函数没有意义
			void* getParameter(){return getData();}
			int getParameterLength(void){return sizeof(RejectionTableData);}
		};

		// negtiveCode已经设定好
		class NegtiveTable:public InstTable < NegtiveTableData >
		{
		public:
			NegtiveTable(QObject* parent = 0) : InstTable < NegtiveTableData >(parent) { }
			~NegtiveTable(){}
			
		private:
			// no componentCode,使用跟component相关的函数没有意义
			void setComponentCode(ComponentCode nComponentCode){}
			ComponentCode  getComponentCode(void){return NegtiveTab;}
			
			// 使用跟parameter相关的函数没有意义
			void* getParameter(){return getData();}
			int getParameterLength(void){return sizeof(NegtiveTableData);}
		};
		//////////////////////////////////////////////////////////////////////////////////////////




		//////////////////////////////////////////////////////////////////////////////////////////
		// These tables belong to CControlFlow

		// component code需要用户设定,默认为0x3010(Table::DmuTab1)
		class DmuConfigTable:public InstTable < DmuConfigTableData >
		{
		public:
			DmuConfigTable(QObject* parent = 0) :  InstTable < DmuConfigTableData >(parent)
			{
				setComponentCode(Table::DmuTab1);
			}
			~DmuConfigTable(){}
		};
		
		// component code需要用户设定,这里默认为3070H(Table::DpuTab1)
		class DpuConfigTable:public InstTable < DpuConfigTableData >
		{
		public:
			DpuConfigTable(QObject* parent = 0) : InstTable < DpuConfigTableData >(parent)
			{
				setComponentCode(Table::DpuTab1);
			}
			~DpuConfigTable(){}
		};
		typedef InstTable < GlobalHdrConfigTableData > GlobalHdrConfigTable;// component code:3001H(已设定好)

		// componentCode需要用户设定,默认为0x3010(Table::DmuTab1)
		class ResetBerTable:public InstTable < ResetBerTableData >
		{
		public:
			ResetBerTable(QObject* parent = 0) :  InstTable < ResetBerTableData >(parent)
			{
				setComponentCode(Table::DmuTab1);
			}
			~ResetBerTable(){}
		};
		
		// 已经设定好
		class ConfigAckTable:public InstTable < ConfigAckTableData >
		{
		public:
			ConfigAckTable(QObject* parent = 0) : InstTable < ConfigAckTableData >(parent) 
			{

			}
			~ConfigAckTable(){}
			
		private:
			// no componentCode,使用跟component相关的函数没有意义
			void setComponentCode(ComponentCode nComponentCode){}
			/*ComponentCode getComponentCode(void)
			{
				return DummyComponentCode; 
			}*/

			//	使用跟parameter相关的函数没有意义
			int getParameterLength(void){return sizeof(ConfigAckTableData);}
			void* getParameter(){return getData();}
		};
		/////////////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////////////
		// These tables belong to CVectorAnalysisFlow
		typedef InstTable < VectorAnalysisRequestTableData > VectorAnalysisRequestTable;//设定好componentCode
		typedef InstTable < NegativeVectorAnalysisAckTableData > NegativeVectorAnalysisAckTable;//设定好componentCode
		//typedef InstTable < VectorAnalysisDataMsgTableData > VectorAnalysisDataMsgTable;// 不需要componentCode
		class VectorAnalysisDataMsgTable : public InstTable < VectorAnalysisDataMsgTableData >		
		{
		public:
			VectorAnalysisDataMsgTable(QObject* parent = 0) :  InstTable < VectorAnalysisDataMsgTableData >(parent)
			{
				setComponentCode(Table::VectorTab);
			}

			~VectorAnalysisDataMsgTable(){}
		};

		typedef InstTable < ProbeRequestTableData > ProbeRequestTable;//设定好componentCode
		typedef InstTable < NegativeProbeAckTableData > NegativeProbeAckTable;//设定好componentCode

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
		// These tables belong to TelemetryFlow(遥测数据)
		typedef InstTable < TelemetryRequestTableData > TelemetryDataRequestTable;// 不需要componentCode
		//////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////
		// component code:3100H(已设定好), All component tables
		class AllComponentTable : public InstTable < AllComponentTableData >
		{
		public:			
			AllComponentTable(QObject* parent = 0);
			~AllComponentTable();

		public:
			/**
			 * 重载Table中的同名函数,在此函数中将挂上一些table
			 */
			void setComponentCode(int nComponentCode);

			/**
			 *
			 * 根据用户传进来的data,如果需要设置AllComponentTable,则设置allCompTable
			 * 如果需要设置单个table,则设置这个table.
			 *
			 */
			void setData(const void* data, int len, Endian endian);

			/**
			 *
			 * 返回m_validTableList的引用
			 *
			 */
			std::list<Table*>& getValidTableList();

			/**
			 * 返回m_allTableList的引用
			 */
			std::list<Table*>& getAllTableList();

			/**
			 *
			 * 返回m_validTableVec的地址
			 *
			 */
			void* getData(void);
			
			/**
			 *
			 * 返回m_validTableList中所有表格的长度之和
			 * 如果m_validTableList中存放的是allCompTable,则返回allCompTable的长度
			 * 如果m_validTableList中存放的某个Table，则返回这个Table的长度
			 * 否则返回0
			 *
			 */
			int getDataLength(void);


			/**
			 * 设置Endian状态
			 */
			//void setEndian(Endian newEndian, bool doParameterConversion);

			/**
			 *
			 * 根据componentCode在m_allTableList中得到subtable
			 * 如果在m_allTableList中能找到它,则ok = true;否则ok=false 
			 *
			 */
			void getSubTable(Table **table, int componentCode, bool& ok);

			/**
			 * 如果table合法(它的componentCode和m_allTableList中的某个table的componentCode相等),
			 * 将table插入到m_validTableList中并返回true;否则返回false
			 */
			bool insertValidTable(Table& table);

		private:
			/**
			 *
			 * 根据gobal hdr table重新挂载相应的table
			 *
			 */
			bool reMountTable(int len);

			/**
			 *
			 * 将m_validTableList的table拷贝到m_tableVector
			 * 如设置的是AllComponentTable,拷贝时,其componentCode = 0x3010
			 * 否则,其componentCode = m_validTableList的第一个table的componentCode
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

			std::list <Table*> m_allTableList;// 将所有table挂载到此list上,暂时仅做遍历用
			std::list <Table*> m_validTableList;// 用户设置的table挂载到此list上,有可能是单个table,也有可能是AllComponentTab

			std::vector <unsigned char> m_validTableVector;// 将用户设置的table的数据拷贝到此vector上

			bool m_bAllCompTab;// 等于true时,表示用户设置的是AllComponentTable			
		};
		//////////////////////////////////////////////////////////////////////////////////////////

		class TelemetryTable: public InstTable < TelemetryTableData >
		{
		public:
			TelemetryTable(QObject* parent = 0) : InstTable < TelemetryTableData >(parent) 	{ }
			~TelemetryTable(){}
		private:
			// no componentCode,使用跟component相关的函数没有意义
			void setComponentCode(ComponentCode nComponentCode){}
			ComponentCode getComponentCode(void){ assert(false); return (ComponentCode)0; }

			//	使用跟parameter相关的函数没有意义
			int getParameterLength(void){return sizeof(TelemetryTableData);}
			void* getParameterAddr(){return getData();}			
		};

	}

}