#ifndef		HDRINTERFACE_H_H_
#define		HDRINTERFACE_H_H_

#pragma  pack(4)

 typedef struct requestFrame 
 {
 	int anSTDTCPIPHheader[3];	//0-2��׼��¼֡TCP-IPͷ
 	int nTMChannel;				//3ң��ͨ��
 	int nRequestCode;			//4������
 	int anReserved[3];			//5-7����λ
 	int nTMBlockCnt;			//8ÿ��ң��������Ϣ������TM Block���ݿ�����
 	int nRate;					//9ң����Ϣ���ʵ���
 	union						//10-11ѡ�������ŵ�
 	{
 		__int64 i64VChannel;
 		int anVChannel[2];
 	}uVChannel;		
 	int	nSendFirstTMBOffset;	//12���͵�һ�����ݿ�λ��
 	union						//13-14���͵�һ��TM Block���ݵ�ʱ���±�
 	{
 		__int64 i64TimeTag;
 		int anTimeTag[2];
 	}uStartTimeTag;
 	int nSendEndTMB;			//15�������һ��TM Block������
 	union 						//16-17�������һ��TM block�����ݵ�ʱ���±�
 	{
 		__int64 i64TimeTag;
 		int anTimeTag[2];
 	}uEndTimeTag;
 	int anReserved2[13];		//18-30����λ
 	int nSTDTCPIPTail;			//31��׼TCP-IP֡β
 }REQUESTFRAME; 

#pragma pack(4)

 typedef struct TMDataSendFrame
 {
 	int anSTDTCPIPHheader[3];	//��׼��¼֡TCP-IPͷ ע: anSTDTCPIPHheader[0] = 1234567890, anSTDTCPIPHheader[1] = framesize; anSTDTCPIPHheader[2] = 0
 	int nTMChannel;				//ң��ͨ��
 	int nRequestCode;			//������ 
 	int anReserved[3];			//����λ
 	int nBlockSYNLen;			//Block��ͬ��ͷ����(ע: ��λ��bit, ȡֵ��Χ: 8~64)
 	int nBlockDataSize;			//ÿ��Block��ԭʼ���ݵĳ���(ע: ��λ��byte, ȡֵ��Χ��: 10 ~ 1048576, ��ֵ����SW)
 	int nTimeTagLen;			//ʱ�������(��λ�� 64bit, ����ֵΪnʱ, ��ʾʱ���򳤶�Ϊn*64bit)
 	int nstatuFieldLen;			//״̬�򳤶�(��λ��64bit);
 	int nTMBlockSize;			//ÿ��Block�Ĵ�С(��λ: 64bit, ���ֵ: 131082)
 	int nTMBlockCnt;			//��ǰTM��Ϣ��TM Block������(���ֵΪ131072)
 	int nTMHeadSize;			//TM�ļ�ͷ��С
 	__int64 i64ForcedData;		//ǿ������
 	int nPCRAMOverRunAlarm;		//PC RAM�������
 	float fPCRAMOverRunMargin;	//PC RAM�������Ŀ�����(�԰ٷֱȼ�)
 	__int64 *pi64TMB;			//������
 	int nSTDTCPIPTail;			//��׼TCP-IP֡β
 
 }TMDATASENDFRAME;

bool validateReqFrame(void* pReqFrame, const int syn = 1234567890, const int reqCode = 4, const int frameEndFlag = -1234567890);

#endif
