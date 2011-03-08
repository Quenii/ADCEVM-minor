// AdcTestPlatDoc.h : interface of the CAdcTestPlatDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ADCTESTPLATDOC_H__F3A768C0_94E1_48C1_B17A_A355E0729D18__INCLUDED_)
#define AFX_ADCTESTPLATDOC_H__F3A768C0_94E1_48C1_B17A_A355E0729D18__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// matlab库
//#include "libadc.h"
//#include "libalg.h"
// for critical section
#include <afxmt.h>


#define CHANNEL_NUM 4
#define MAX_DEPTH  (32*1024) //////////////////q
#define MAX_FIFO   (32*1024)
#define SAMP_FREQ (80*1000*1000)
#define MAX_VALUE (32768)
#define SAMP_FREQ_M (80.0)

/* 命令地址 */
#define LOCAL_ADDR_CMD       0x10
/* 同步配置地址 */
#define LOCAL_ADDR_SYN_ADDR  0x64
/* 同步配置参数 */
#define LOCAL_ADDR_SYN_PARAM 0x6c
/* 独立配置地址 */
#define LOCAL_ADDR_DEP_ADDR  0x54
/* 独立配置参数 */
#define LOCAL_ADDR_DEP_PARAM 0x5c
// DMA的地址
#define LOCAL_ADDR_DMA 0x4

#define LOCAL_ADDR_CHECK 0x10

/* 电源开关 */
#define CMD_POWER 0x1000
//#define 

/* 模拟输入开关 */
#define CMD_ANALOG 0x2000

/* 改变工作模式 */
#define CMD_MODE 0x4000

/* 改变DDC配置 */
#define CMD_SET_CONFIG 0x8000

/* 读取DDC配置 */
#define CMD_GET_CONFIG 0x0100

/* 选择ADC通道 */
#define CMD_SELECT 0x0200

/* 采集数据 */
#define CMD_COLLECT 0x0010

// 光纤通道检测命令
#define CMD_FIBER_CHECK 0x0011

// 
#define PARAM_CHAN_A 0x11
#define PARAM_CHAN_B 0x12
#define PARAM_CHAN_C 0x14
#define PARAM_CHAN_D 0x18

//
#define CMD_IQ_DEPTH   0x0400
#define CMD_RESET   0x0800
#define CMD_IQ_COLLECT 0x0020


// IQ
#define CHAN_AI 0x11
#define CHAN_AQ 0x21
#define CHAN_BI 0x12
#define CHAN_BQ 0x22
#define CHAN_CI 0x14
#define CHAN_CQ 0x24
#define CHAN_DI 0x18
#define CHAN_DQ 0x28

// 算法测试的参数
#define ADDR_PARAM_SIZE 48
#define DMA_SIZE 64 


class CAdcTestPlatDoc : public CDocument
{
protected: // create from serialization only
	CAdcTestPlatDoc();
	DECLARE_DYNCREATE(CAdcTestPlatDoc)

// Attributes
public:

// Operations
public:
	// matlab相关的变量
	/*mxArray* mxSNR;
	mxArray* mxSINAD;
	mxArray* mxSFDR;
	mxArray* mxENOB;

	mxArray* mxData;
	mxArray* mxData1;
	mxArray* mxData2;
	mxArray* mxNumpt;// 1024
	mxArray* mxFclk;// 1000
	mxArray* mxNumbit;// 8
	mxArray* mxR;
	*/

	// 计算指标时的中间缓冲区
	double m_data[MAX_DEPTH];
	double m_data2[MAX_DEPTH];


	// 底噪声测试结果备份(最大值)
	WORD m_waSignalBackNoise[CHANNEL_NUM];
	// 测试结果
	double m_daResultBackNoise[CHANNEL_NUM];
	double m_daResultSNR[CHANNEL_NUM];
	double m_daResultSFDR[CHANNEL_NUM];	
	double m_daResultSINAD[CHANNEL_NUM];
	double m_daResultENOB[CHANNEL_NUM];
	double m_daResultChanDisturbA[CHANNEL_NUM];
	double m_daResultChanDisturbB[CHANNEL_NUM];
	double m_daResultChanDisturbC[CHANNEL_NUM];
	double m_daResultChanDisturbD[CHANNEL_NUM];
	double m_daResultChanDisturb[CHANNEL_NUM];
	short m_DmaABuffer[MAX_DEPTH * 2];
	short m_DmaBBuffer[MAX_DEPTH * 2];
	short m_DmaCBuffer[MAX_DEPTH * 2];
	short m_DmaDBuffer[MAX_DEPTH * 2];
	short m_DmaBuffer[MAX_DEPTH * 2];	
	
	// 原始数据(用于显示)
	short m_waCh1Signal[MAX_DEPTH];
	short m_waCh2Signal[MAX_DEPTH];
	short m_waCh3Signal[MAX_DEPTH];
	short m_waCh4Signal[MAX_DEPTH];
	// 原始数据(底噪声测试)
	short m_waCh1SignalNoise[MAX_DEPTH];
	short m_waCh2SignalNoise[MAX_DEPTH];
	short m_waCh3SignalNoise[MAX_DEPTH];
	short m_waCh4SignalNoise[MAX_DEPTH];
	// 原始数据(性能测试)
//	WORD m_waCh1SignalPerf[MAX_DEPTH];
	short m_waCh1SignalPerf[MAX_DEPTH];
	short m_waCh2SignalPerf[MAX_DEPTH];
	short m_waCh3SignalPerf[MAX_DEPTH];
	short m_waCh4SignalPerf[MAX_DEPTH];
	// 原始数据(串音测试)
	short m_waCh1SignalDisturb[MAX_DEPTH];
	short m_waCh2SignalDisturb[MAX_DEPTH];
	short m_waCh3SignalDisturb[MAX_DEPTH];
	short m_waCh4SignalDisturb[MAX_DEPTH];
	// 从视图传递的工作模式选择
	int m_nSel;
	// 采集计算完成的标志
	BOOL m_bTestComp;
	// 需要测试的项的状态
	BOOL m_bTestBackNoise;
	BOOL m_bTestSNR;
	BOOL m_bTestSFDR;
	BOOL m_bTestChanDisturb;
	BOOL m_bTestSINAD;
	// 选择的测试项
	int m_nTestModeSel;
	// 算法测试相关的缓冲区

	short m_waAiData[MAX_FIFO];
	short m_waAqData[MAX_FIFO];
	short m_waBiData[MAX_FIFO];
	short m_waBqData[MAX_FIFO];
	short m_waCiData[MAX_FIFO];
	short m_waCqData[MAX_FIFO];
	short m_waDiData[MAX_FIFO];
	short m_waDqData[MAX_FIFO];
	// 算法测试的深度
	int m_nAlgDepth;
	// 是否自动保存算法测试数据
	BOOL m_bAlgAutoSave;
	// 4个通道缓冲区的读写保护
	CCriticalSection m_csDataBuf;

	int m_nR[5];//1, m_nR2, m_nR3, m_nR4;
	

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAdcTestPlatDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:		
	void CheckFC();
	CString Dec2Bin( int x );
	void PowerOff( void );
	void PowerOn( void );
	void CalcAlgPerf( void );
	void CmdnStat(int Chan, CString &strCRC, CString &strBag);
	void SaveFile(CString strFileNamePre, short * m_Data);
	void GenFileName(CString &fileName);
	void TestAlg( void );
	void GetData( void );
	void FileOpen( BYTE* pbyData );
	void FileSave( BYTE *pbyData, DWORD *pdwSize );
	void SetTabSel( void );
	void TestChanDisturb(  int nSel );
	void TestPerf( void );
	void TestBackNoise( void );
	void CalcBackNoise( void );
	void CalcPerf( void );
	void CalcChanDisturb( int nSel );
	void DmaRead( HANDLE hDevice, BYTE *pbyData, DWORD dwLocalAddr, DWORD dwSize);
	void SendCommand( DWORD dwCmd );
	void IoRead( DWORD dwLocalAddr, DWORD* pdwData );
	void IoWrite(DWORD dwLocalAddr, DWORD dwData);
	void SetTestMode( int nSel );
	static UINT TestAndCalc( LPVOID pParam );
	void CAdcTestPlatDoc::FakeData();

	
	
	virtual ~CAdcTestPlatDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAdcTestPlatDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADCTESTPLATDOC_H__F3A768C0_94E1_48C1_B17A_A355E0729D18__INCLUDED_)
