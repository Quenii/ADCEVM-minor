#pragma  once
#include "gkhy/qzebralib/qzebra_lib_global.hpp"
#include <assert.h>
#include <Winsock2.h>
#include <vector>

namespace gkhy
{
	namespace QZebraLib
	{	
		#pragma pack (push, 4)
		struct MessageHeader 
		{
			int nStart;
			int nSize;
			int nFlowId;
		};
		#pragma pack (pop)


		#pragma pack (push, 4) 
		struct MessagePostamble 
		{
			int nPostamble;
		};
		#pragma pack (pop)	

		// message data are stored as net endian.
		class  QZEBRA_LIB_EXPORT Message
		{

		public:
			enum enumConstant
			{
				constStart = 1234567890,
				constPostamble = -1234567890
			};	
		
		public:
			Message();	
			virtual ~Message(void);

		private:
			Message(Message&);
			Message operator=(const Message&);

		public:		
			
			/**			 
			 * Attach��Detach�������ʹ�ã�������ʹ��Ҳ����
			 * ��Ϊ�����������л�����ж�
			 */
			void AttachFromNetEndian(int nTotalLen, int nFlowID, void *data);
			void AttachFromHostEndian(int nTotalLen, int nFlowID, void *data);
			void Detach();
			/*
			 * @return in bytes.
			 */
			static int GetMaxPossibleLen()  { return 3 * 1024 * 1024; }
			static int GetMinPossibleLen() 	{ return sizeof(MessageHeader) + sizeof(int) + sizeof(MessagePostamble); 	}

			/**
			 * VerifyHeader - У����Ϣͷ��
			 *
			 * @param buff ҪУ�����Ϣͷ����ָ�롣
			 * @param len У��ɹ��Ƿ�����Ϣ���ȡ�
			 * @return У��ɹ�����true��У��ʧ�ܷ���false��
			 */
			static bool VerifyHeader(void* buff, int& len, bool fromNetEndian);
			
			/**
			 * VerifyPostamble - У����Ϣβ��
			 *
			 * @param buff ҪУ�����Ϣͷ����ָ�롣
			 * @return У��ɹ�����true��У��ʧ�ܷ���false��
			 */
			static bool VerifyPostamble(void* buff, bool fromNetEndian);
			
			int GetTotalLen() const; 

			int GetHeaderLen() const { return sizeof(m_Msg.header); }
			int GetDataLen() const { return GetTotalLen() - GetHeaderLen() - GetPostambleLen();	}		
			int GetPostambleLen() const { return sizeof(m_Msg.postamble);	}
			int GetFlowID() const;
			
			MessageHeader* GetHeaderNetEndian() {	return &(m_Msg.header);	}
			void* GetDataNetEndian() { return m_Msg.pData;	}
			MessagePostamble* GetPostambleNetEndian() { return &(m_Msg.postamble);	}

		protected:
			static int toNetEndian(int dw, bool fromNetEndian);
			static int toHostEndian(int dw, bool fromNetEndian);
			
		private:
			#pragma pack (push, 4) 
			struct HdrMSG
			{
				MessageHeader header;
				void* pData;
				MessagePostamble postamble;
			} m_Msg;			
			#pragma pack (pop)		
			bool m_bAttached;

			// used by AttachFromHostEndian. 
			std::vector<unsigned long> buff;
		};	
	};
	
};
