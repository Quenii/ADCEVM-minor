#ifndef		HDRINTERFACE_H_H_
#define		HDRINTERFACE_H_H_

#pragma  pack(4)

 typedef struct requestFrame 
 {
 	int anSTDTCPIPHheader[3];	//0-2标准记录帧TCP-IP头
 	int nTMChannel;				//3遥测通道
 	int nRequestCode;			//4请求码
 	int anReserved[3];			//5-7保留位
 	int nTMBlockCnt;			//8每条遥测数据信息包含的TM Block数据块数量
 	int nRate;					//9遥测信息速率调整
 	union						//10-11选择虚拟信道
 	{
 		__int64 i64VChannel;
 		int anVChannel[2];
 	}uVChannel;		
 	int	nSendFirstTMBOffset;	//12发送第一个数据块位置
 	union						//13-14发送第一个TM Block数据的时间下标
 	{
 		__int64 i64TimeTag;
 		int anTimeTag[2];
 	}uStartTimeTag;
 	int nSendEndTMB;			//15发送最后一个TM Block的数据
 	union 						//16-17发送最后一个TM block的数据的时间下标
 	{
 		__int64 i64TimeTag;
 		int anTimeTag[2];
 	}uEndTimeTag;
 	int anReserved2[13];		//18-30保留位
 	int nSTDTCPIPTail;			//31标准TCP-IP帧尾
 }REQUESTFRAME; 

#pragma pack(4)

 typedef struct TMDataSendFrame
 {
 	int anSTDTCPIPHheader[3];	//标准记录帧TCP-IP头 注: anSTDTCPIPHheader[0] = 1234567890, anSTDTCPIPHheader[1] = framesize; anSTDTCPIPHheader[2] = 0
 	int nTMChannel;				//遥测通道
 	int nRequestCode;			//请求码 
 	int anReserved[3];			//保留位
 	int nBlockSYNLen;			//Block的同步头长度(注: 单位是bit, 取值范围: 8~64)
 	int nBlockDataSize;			//每个Block中原始数据的长度(注: 单位是byte, 取值范围是: 10 ~ 1048576, 该值包含SW)
 	int nTimeTagLen;			//时间戳长度(单位是 64bit, 即该值为n时, 表示时间域长度为n*64bit)
 	int nstatuFieldLen;			//状态域长度(单位是64bit);
 	int nTMBlockSize;			//每个Block的大小(单位: 64bit, 最大值: 131082)
 	int nTMBlockCnt;			//当前TM信息中TM Block的数量(最大值为131072)
 	int nTMHeadSize;			//TM文件头大小
 	__int64 i64ForcedData;		//强制数据
 	int nPCRAMOverRunAlarm;		//PC RAM溢出警告
 	float fPCRAMOverRunMargin;	//PC RAM缓冲区的空闲率(以百分比记)
 	__int64 *pi64TMB;			//数据区
 	int nSTDTCPIPTail;			//标准TCP-IP帧尾
 
 }TMDATASENDFRAME;

bool validateReqFrame(void* pReqFrame, const int syn = 1234567890, const int reqCode = 4, const int frameEndFlag = -1234567890);

#endif
