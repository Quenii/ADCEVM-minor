// AdcTestPlatDoc.cpp : implementation of the CAdcTestPlatDoc class
//

#include "stdafx.h"
#include "AdcTestPlat.h"

#include "AdcTestPlatDoc.h"
#include "TestSetView.h"
#include "PlxApi.h"
#include "m2c.h"
#include "GlobalData.h"

#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


template<typename T>
static void copy2vector(std::vector<T>& vect, T* p, int count)
{
	vect.resize(count);
	memcpy(&vect[0], p, count * sizeof(T));
	
}

// �������ݿ���
//#define TEST_DATA

/////////////////////////////////////////////////////////////////////////////
// CAdcTestPlatDoc

IMPLEMENT_DYNCREATE(CAdcTestPlatDoc, CDocument)

BEGIN_MESSAGE_MAP(CAdcTestPlatDoc, CDocument)
	//{{AFX_MSG_MAP(CAdcTestPlatDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAdcTestPlatDoc construction/destruction

CAdcTestPlatDoc::CAdcTestPlatDoc()
{
	m_bTestBackNoise = FALSE;
	m_bTestSNR = TRUE;
	m_bTestSFDR = TRUE;
	m_bTestChanDisturb = FALSE;
	m_bTestSINAD = TRUE;

	m_bTestComp = TRUE;
	// Ĭ�����ܲ���
	m_nTestModeSel = 1;
	//
	m_nAlgDepth = MAX_FIFO; 
	// 
	m_bAlgAutoSave = FALSE;

	int i;
	for (i=1; i<5; ++i)
	{
		m_nR[i] = 20;
	}

	memset( m_waSignalBackNoise, 0, CHANNEL_NUM*sizeof(WORD) );

	memset( m_daResultBackNoise, 0, CHANNEL_NUM*sizeof(double) );
	memset( m_daResultSNR, 0, CHANNEL_NUM*sizeof(double) );
	memset( m_daResultSFDR, 0, CHANNEL_NUM*sizeof(double) );	
	memset( m_daResultSINAD, 0, CHANNEL_NUM*sizeof(double) );
	memset( m_daResultENOB, 0, CHANNEL_NUM*sizeof(double) );
	memset( m_daResultChanDisturbA, 0, CHANNEL_NUM*sizeof(double) );
	memset( m_daResultChanDisturbB, 0, CHANNEL_NUM*sizeof(double) );
	memset( m_daResultChanDisturbC, 0, CHANNEL_NUM*sizeof(double) );
	memset( m_daResultChanDisturbD, 0, CHANNEL_NUM*sizeof(double) );
	
	memset( m_waCh1Signal, 0, MAX_DEPTH * 2 );
	memset( m_waCh2Signal, 0, MAX_DEPTH * 2 );
	memset( m_waCh3Signal, 0, MAX_DEPTH * 2 );
	memset( m_waCh4Signal, 0, MAX_DEPTH * 2 );

	memset( m_waCh1SignalNoise, 0, MAX_DEPTH * 2 );
	memset( m_waCh2SignalNoise, 0, MAX_DEPTH * 2 );
	memset( m_waCh3SignalNoise, 0, MAX_DEPTH * 2 );
	memset( m_waCh4SignalNoise, 0, MAX_DEPTH * 2 );

	memset( m_waCh1SignalPerf, 0, MAX_DEPTH * 2 );
	memset( m_waCh2SignalPerf, 0, MAX_DEPTH * 2 );
	memset( m_waCh3SignalPerf, 0, MAX_DEPTH * 2 );
	memset( m_waCh4SignalPerf, 0, MAX_DEPTH * 2 );

	memset( m_waCh1SignalDisturb, 0, MAX_DEPTH * 2 );
	memset( m_waCh2SignalDisturb, 0, MAX_DEPTH * 2 );
	memset( m_waCh3SignalDisturb, 0, MAX_DEPTH * 2 );
	memset( m_waCh4SignalDisturb, 0, MAX_DEPTH * 2 );
	// �㷨��ػ������ĳ�ʼ��
	memset( m_waAiData, 0, MAX_DEPTH*sizeof(short) );
	memset( m_waAqData, 0, MAX_DEPTH*sizeof(short) );
	memset( m_waBiData, 0, MAX_DEPTH*sizeof(short) );
	memset( m_waBqData, 0, MAX_DEPTH*sizeof(short) );
	memset( m_waCiData, 0, MAX_DEPTH*sizeof(short) );
	memset( m_waCqData, 0, MAX_DEPTH*sizeof(short) );
	memset( m_waDiData, 0, MAX_DEPTH*sizeof(short) );
	memset( m_waDqData, 0, MAX_DEPTH*sizeof(short) );

	// ��������
#ifdef TEST_DATA
	double ppi = 3.1415926535;
	for ( int j = 0; j < MAX_DEPTH; j++ )// 
	{		
		m_waCh1Signal[j] = 16384*sin(2*ppi*j/80);
		m_waCh2Signal[j] = 16384*sin(2*ppi*j/40);
		m_waCh3Signal[j] = 8192*sin(2*ppi*j/80);		
		m_waCh4Signal[j] = 8192*sin(2*ppi*j/80);		
	}
	// �㷨����
	for ( j = 0; j < MAX_DEPTH; j++ )// 
	{		
		m_waAiData[j] = 16384*sin(2*ppi*j/80);
		m_waAqData[j] = 16384*sin(2*ppi*j/40);	
		m_waBiData[j] = 16384*sin(2*ppi*j/80);
		m_waBqData[j] = 16384*sin(2*ppi*j/40);
	}
	// �Ӵ��̶��ļ�����
	CString strData;
	CStdioFile file;
	BOOL bRet = file.Open( "V1_0_TB.txt", CFile::modeRead | CFile::typeText  );//V1_0_TB.txt
	if ( bRet )
	{
		for ( j = 0; j < MAX_DEPTH; j++ )
		{			
			file.ReadString(strData);
			m_waCh1Signal[j] = atoi(strData);
			m_waCh2Signal[j] = atoi(strData)/2;
			m_waCh3Signal[j] = atoi(strData)/3;
			m_waCh4Signal[j] = atoi(strData)/4;
		}
		file.Close();
	}	
	

	bRet = file.Open( "IQ20090122060735DI.txt", CFile::modeRead | CFile::typeText  );//V1_0_TB.txt
	if ( bRet )
	{
		for ( j = 0; j < MAX_DEPTH; j++ )
		{			
			file.ReadString(strData);
			m_waAiData[j] = atoi(strData);
			m_waBiData[j] = atoi(strData);
		}
		file.Close();
	}	
	
	
	bRet = file.Open( "IQ20090122060735DQ.txt", CFile::modeRead | CFile::typeText  );//V1_0_TB.txt
	if ( bRet )
	{
		for ( j = 0; j < MAX_DEPTH; j++ )
		{			
			file.ReadString(strData);
			m_waAqData[j] = atoi(strData);
			m_waBqData[j] = atoi(strData);
		}
		file.Close();
	}	
	
#endif
	
	CheckFC();

}

CAdcTestPlatDoc::~CAdcTestPlatDoc()
{
}

BOOL CAdcTestPlatDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CAdcTestPlatDoc serialization

void CAdcTestPlatDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CAdcTestPlatDoc diagnostics

#ifdef _DEBUG
void CAdcTestPlatDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CAdcTestPlatDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAdcTestPlatDoc commands

void CAdcTestPlatDoc::SetTestMode(int nSel)
{		
	m_nSel = nSel;

	DWORD dwCmd;

	// �����㷨��ͼ
	CTestAlgView* pTestAlgView = NULL;
	POSITION pos = GetFirstViewPosition();
	while ( pos != NULL )
	{
		CView* pView = GetNextView( pos );			
		if ( pView->IsKindOf(RUNTIME_CLASS(CTestAlgView)) )
		{
			pTestAlgView = (CTestAlgView*)pView;
			break;
		}
	}

	// ADC����
	if ( m_nSel == 1 )
	{
		// �л���AD����ģʽʱ������Ҫ��������(dataout_model_sel/test��1)
		// dataout_mode_sel = '0'ΪLVDS��� 0x11 -> 0x01
		//dwCmd = (CMD_MODE << 16) + 0x01;
		//SendCommand( dwCmd );

		dwCmd = (CMD_MODE << 16) 
				+ (1 << 8) //m_nStart
				+ (1 << 6) //m_nM0
				+ (1 << 5) //m_nChanConfigCtrl  
				+ (1 << 4) //m_nDataOutModelSel  lvds
				+ (1 << 3) //m_nParaSerSel
				+ (1 << 1) //m_nLvdsAck
				+ 1; //m_nTest
		SendCommand( dwCmd ); 

		// ԭ���ĳ���û�����ã��ڽ���ģʽ�л�ʱ�����
		m_nTestModeSel = 1;
		// �ϴεĲɼ���ɺ󣬿��Խ������̣߳��ɼ��ͼ���
		if ( m_bTestComp )
		{
			// ������ͼ
			//UpdateAllViews( NULL );
			AfxBeginThread( TestAndCalc, this );
		}	
	}
	// �㷨����
	if ( m_nSel == 3 )
	{

		// ����ԭ�����úõ�����
		if ( pTestAlgView != NULL )
		{
			dwCmd = (CMD_MODE << 16) 
				+ (pTestAlgView->m_nStart << 8)
				+ (pTestAlgView->m_nM0 << 6)
				+ (pTestAlgView->m_nChanConfigCtrl << 5)
				+ (pTestAlgView->m_nDataOutModelSel << 4)
				+ (pTestAlgView->m_nParaSerSel << 3)
				+ (pTestAlgView->m_nLvdsAck << 1)
				+ pTestAlgView->m_nTest;
			SendCommand( dwCmd ); 
		}
		
		// ѡ��algģʽ
		m_nTestModeSel = 6;
		// �ϴεĲɼ���ɺ󣬿��Խ������̣߳��ɼ��ͼ���
		if ( m_bTestComp )
		{			
			AfxBeginThread( TestAndCalc, this );  ////////�ϵ��ִ��
		}	
	}
}

void CAdcTestPlatDoc::SendCommand(DWORD dwCmd)
{
	RETURN_CODE rc;

	/* ��ǰPCIE�����Ч */
	if ( ((CAdcTestPlatApp*)AfxGetApp())->m_hDevice != NULL )
	{
		rc = PlxBusIopWrite( ((CAdcTestPlatApp*)AfxGetApp())->m_hDevice,
			IopSpace0,
			LOCAL_ADDR_CMD, 
			TRUE,
			&dwCmd,
			4,
			BitSize32
			);
		if ( rc != ApiSuccess )
		{
			/* */
			return;
		}
	}
	
}

void CAdcTestPlatDoc::DmaRead( HANDLE hDevice, BYTE *pbyData, DWORD dwLocalAddr, DWORD dwSize)
{
	RETURN_CODE rc;
	DMA_CHANNEL_DESC DmaDesc;
	DMA_TRANSFER_ELEMENT DmaData;
	DWORD dwLastTick, dwTickCnt;
	dwLastTick = GetTickCount();

	// ����������
	if ( hDevice != NULL )
	{
		// Clear DMA descriptor structure
		memset(	&DmaDesc, 0, sizeof(DMA_CHANNEL_DESC) );
		// Set up DMA configuration structure
		DmaDesc.EnableReadyInput = 1;
		DmaDesc.DmaStopTransferMode = AssertBLAST;
		DmaDesc.DmaChannelPriority = Rotational;
		DmaDesc.IopBusWidth = 3; // 32 bit bus
		DmaDesc.EnableIopBurst = 1;
		DmaDesc.HoldIopAddrConst = 1;
		DmaDesc.EnableBTERMInput = 1;

		rc = PlxDmaSglChannelOpen( hDevice, PrimaryPciChannel0, &DmaDesc );
		if (rc != ApiSuccess)
		{
			// ERROR �C Unable to open DMA channel
			return;
		}
		DWORD dwValid;
		IoRead( 0, &dwValid);
		do{
			IoRead( 0, &dwValid);
			dwTickCnt = GetTickCount() - dwLastTick;
		}while ( dwValid * 4 < dwSize && dwTickCnt < 100 ); 

//		dwSize = dwValid * 4;

		// DMA paramter
		DmaData.u.UserVa = (U32)pbyData;
		DmaData.LocalAddr = dwLocalAddr;
		DmaData.TransferCount = dwSize;
		DmaData.LocalToPciDma = 1;

		if (dwValid * 4 >= dwSize)
		{
			dwValid = dwSize / 4;
			IoWrite(0, dwValid);
			rc = PlxDmaSglTransfer( hDevice, PrimaryPciChannel0, &DmaData, FALSE );
			if (rc != ApiSuccess)
			{
				// ERROR �C Unable to transfer buffer
				return;
			}
		}

		/* Dma close */
		rc = PlxDmaSglChannelClose( hDevice, PrimaryPciChannel0 );
		if (rc != ApiSuccess)
		{
			// ERROR �C Unable to transfer buffer
			return;
		} 
//		PlxPciBoardReset( hDevice );
		IoRead( 0, &dwValid);
		if (dwValid)
		{
			PlxPciBoardReset( hDevice );
		}
	}
	dwTickCnt = GetTickCount() - dwLastTick;
//	TRACE("\nDMARead: %d", dwTickCnt);

}

// ����ÿ��ͨ���ĵ�����
void CAdcTestPlatDoc::CalcBackNoise()
{
	int i;
	int j;
	//WORD* pwTemp = NULL;
	short* pwTemp = NULL;
	//WORD wMax;
	double dSum;
	double dMax;

	for ( i = 0; i < 4; i++ )
	{
		switch (i)
		{
			case 0:
			{
				pwTemp = m_waCh1Signal;
				break;
			}
			case 1:
			{
				pwTemp = m_waCh2Signal;
				break;
			}
			case 2:
			{
				pwTemp = m_waCh3Signal;
				break;
			}
			case 3:
			{
				pwTemp = m_waCh4Signal;
				break;
			}
			default:
			{
				pwTemp = m_waCh1Signal;
				break;
			}
		}
		// ����rms
		dSum = 0;
		for ( j = 0; j < MAX_DEPTH; j++ )
		{
			dSum += pow( pwTemp[j], 2 );
		}
		dSum = sqrt(dSum);
		// ���������(�ֱ�ֵ)
		//dMax = 8192;
		dMax = MAX_VALUE;
		if ( dSum > 0 )
		{
			m_daResultBackNoise[i] = 20 * log10( dSum / dMax );
		}
		
	}
}

// ͨ��matlab��������
void CAdcTestPlatDoc::CalcPerf()
{
	int i,j;
	double numpt;
	double fclk;
	double numbit;
	double SNR;
	double SINAD;
	double SFDR;
	double ENOB;
	//WORD* pwTemp;
	short* pwTemp;

	numpt = MAX_DEPTH;
	fclk = SAMP_FREQ;
	//numbit = 14;
	numbit = 16;

	FakeData();

	for ( i = 0; i < 4; i++ )
	{
		// ѡ��ĳ��ͨ�������ܲ��Խ��
		switch (i)
		{
			case 0:
			{
				pwTemp = m_waCh1Signal;
				break;
			}
			case 1:
			{
				pwTemp = m_waCh2Signal;
				break;
			}
			case 2:
			{
				pwTemp = m_waCh3Signal;
				break;
			}
			case 3:
			{
				pwTemp = m_waCh4Signal;
				break;
			}
			default:
			{
				pwTemp = m_waCh1Signal;
				break;
			}
		}
		// ԭʼ����
		for ( j = 0; j < MAX_DEPTH; j++ )
		{
			m_data[j] = pwTemp[j];
		}		

		static std::vector<double> y(MAX_DEPTH);
		AdcDynTest(m_data, MAX_DEPTH, fclk, numbit, MAX_DEPTH, 2, 1,
						SNR, SINAD, SFDR, ENOB, &y[0]);

		GlobalData& globalData = * GlobalData::lockInstance();		
		copy2vector(globalData.dataSet[i].i, m_data, MAX_DEPTH);		
		copy2vector(globalData.dataSet[i].y, &y[0], MAX_DEPTH);
		
		globalData.dataSet[i].SNR = SNR;
		globalData.dataSet[i].SFDR = SFDR;
		globalData.dataSet[i].SINAD = SINAD;
		globalData.dataSet[i].ENOB = ENOB;
		
		globalData.unlock();
		
		// ������
		m_daResultSNR[i] = SNR;
		m_daResultSFDR[i] = SFDR;
		m_daResultSINAD[i] = SINAD;
		m_daResultENOB[i] = ENOB;
	}	
}

// ����ÿ��ͨ����ͨ������
void CAdcTestPlatDoc::CalcChanDisturb( int nSel )
{
	int i;
	int j;
	//WORD* pwTemp = NULL;
	short* pwTemp = NULL;
	//WORD wMax;
	double dSum;
	double dMax;

	for ( i = 0; i < 4; i++ )
	{
		switch (i)
		{
			case 0:
			{
				pwTemp = m_waCh1Signal;
				break;
			}
			case 1:
			{
				pwTemp = m_waCh2Signal;
				break;
			}
			case 2:
			{
				pwTemp = m_waCh3Signal;
				break;
			}
			case 3:
			{
				pwTemp = m_waCh4Signal;
				break;
			}
			default:
			{
				pwTemp = m_waCh1Signal;
				break;
			}
		}
		
		// ����rms
		dSum = 0;
		for ( j = 0; j < MAX_DEPTH; j++ )
		{
			dSum += pow( pwTemp[j], 2 );
		}
		dSum = sqrt(dSum);
		// ����ͨ������(�ֱ�ֵ)		
		dMax = MAX_VALUE;
		if ( dSum > 0 )
		{
			m_daResultChanDisturb[i] = 20 * log10( dSum / dMax );
		}
		// �����ǰͨ��Ϊѡ�����������Ե�ͨ�������㴮����������Ϊ0
		if ( nSel == i )
		{
			// ����������
			if ( m_daResultChanDisturb[i] > m_daResultBackNoise[i] )
			{
				m_daResultChanDisturb[i] = m_daResultChanDisturb[i] - m_daResultBackNoise[i];
			}
			// ���ͨ��������С������Ϊ0
			else
			{
				m_daResultChanDisturb[i] = 0;
			}
		}
		else
		{
			m_daResultChanDisturb[i] = 0;
		}
		
	}
}

void CAdcTestPlatDoc::TestBackNoise()
{
	DWORD dwCmd;

	/* ��ǰ�˰��Դ */
	dwCmd = (DWORD)CMD_POWER << 16;
	SendCommand( dwCmd );
	/* ��A��B��C��Dͨ���̵��� */
	dwCmd = (DWORD)CMD_ANALOG << 16;
	SendCommand( dwCmd );
	/* 60ms�����ζ�ȡA��B��C��Dͨ������ */
	Sleep( 100 );
	/* ��DMA���� */				
	GetData();
}

void CAdcTestPlatDoc::TestPerf()
{
	DWORD dwCmd;
	//int i;
	//int j;
	//BYTE* pbyData;

	/* ��ǰ�˰��Դ */
//	PowerOn();
	Sleep( 100 );
	/* �̵��� */
	dwCmd = ((DWORD)CMD_ANALOG << 16 );// + (1<<i)
	SendCommand( dwCmd );
	/* 60ms */
	Sleep( 50 );
	// ��ȡ4��ͨ������
	GetData();	
}

void CAdcTestPlatDoc::TestChanDisturb( int nSel )
{
	DWORD dwCmd;
	//int i;
	//int j;
	//BYTE* pbyData;

	/* ��ǰ�˰��Դ */
	dwCmd = (DWORD)CMD_POWER << 16;
	SendCommand( dwCmd );
	/* �̵��� */
	dwCmd = ((DWORD)CMD_ANALOG << 16 ) + (15 - (1<<nSel));
	SendCommand( dwCmd );
	/* 60ms */
	Sleep( 100 );
	// ��ȡ4��ͨ������
	GetData();
}

UINT CAdcTestPlatDoc::TestAndCalc( LPVOID pParam )
{
	CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)pParam;

	if ( pDoc != NULL )
	{
		// ����
		CSingleLock slDataBuf( &(pDoc->m_csDataBuf) );
		slDataBuf.Lock();
		// �ɼ���ʼ��������ɱ�־ΪFALSE
		pDoc->m_bTestComp = FALSE;
		// ���ݲ���������ͼ��ѡ�����ĳ�����͵Ĳ���
		switch ( pDoc->m_nTestModeSel )
		{
			// ���������� 	
			case 0:
			{
				pDoc->TestBackNoise();
				pDoc->CalcBackNoise();
				break;
			}
			// ���ܲ��� 	
			case 1:
			{
				pDoc->TestPerf();
				pDoc->CalcPerf();
				break;
			}
			// Aͨ���������� 	
			case 2:
			{
				pDoc->TestChanDisturb(0);
				pDoc->CalcChanDisturb(0);
				break;
			}
			// Bͨ���������� 	
			case 3:
			{
				pDoc->TestChanDisturb(1);
				pDoc->CalcChanDisturb(1);
				break;
			}
			// Cͨ���������� 	
			case 4:
			{
				pDoc->TestChanDisturb(2);
				pDoc->CalcChanDisturb(2);
				break;
			}
			// Dͨ���������� 	
			case 5:
			{
				pDoc->TestChanDisturb(3);
				pDoc->CalcChanDisturb(3);
				break;
			}
			// �㷨����
			case 6:
			{
				pDoc->TestAlg( );	
				pDoc->CalcAlgPerf();
				break;
			}
			default:
				break;
		}		
		// ���ݵ�ǰ��ǩҳ��ѡ��ȷ����ʾ���ֲ��Ե����ݺ�fft 
		//pDoc->SetTabSel();
		// �ɼ�����������ɱ�־ΪTRUE
		pDoc->m_bTestComp = TRUE;	
		slDataBuf.Unlock();
	}	

	return 0;
}

void CAdcTestPlatDoc::SetTabSel()
{
	CAdcTestPlatView* pTestPlatView;	
	pTestPlatView = NULL;
	
	POSITION pos = GetFirstViewPosition();
	while ( pos != NULL )
	{
		CView* pView = GetNextView( pos );		
		// ��ʾ��ͼ
		if ( pView->IsKindOf(RUNTIME_CLASS(CAdcTestPlatView)) )
		{			
			pTestPlatView = (CAdcTestPlatView*)pView;
			break;
		}
	}
	// ���ݵ�ǰ��ǩҳ��ѡ��ȷ����ʾ���ֲ��Ե����ݺ�fft
	int nTabSel = pTestPlatView->m_tcTestMode.GetCurSel();
	switch ( nTabSel )
	{
		case 0:
		{
			memcpy( m_waCh1Signal, m_waCh1SignalNoise, MAX_DEPTH * 2 );
			memcpy( m_waCh2Signal, m_waCh2SignalNoise, MAX_DEPTH * 2 );
			memcpy( m_waCh3Signal, m_waCh3SignalNoise, MAX_DEPTH * 2 );
			memcpy( m_waCh4Signal, m_waCh4SignalNoise, MAX_DEPTH * 2 );
			break;
		}
		case 1:
		case 2:
		case 4:
		{
			memcpy( m_waCh1Signal, m_waCh1SignalPerf, MAX_DEPTH * 2 );
			memcpy( m_waCh2Signal, m_waCh2SignalPerf, MAX_DEPTH * 2 );
			memcpy( m_waCh3Signal, m_waCh3SignalPerf, MAX_DEPTH * 2 );
			memcpy( m_waCh4Signal, m_waCh4SignalPerf, MAX_DEPTH * 2 );
			break;
		}
		case 3:
		{
			memcpy( m_waCh1Signal, m_waCh1SignalDisturb, MAX_DEPTH * 2 );
			memcpy( m_waCh2Signal, m_waCh2SignalDisturb, MAX_DEPTH * 2 );
			memcpy( m_waCh3Signal, m_waCh3SignalDisturb, MAX_DEPTH * 2 );
			memcpy( m_waCh4Signal, m_waCh4SignalDisturb, MAX_DEPTH * 2 );
			break;
		}
		default:
			break;
	}	
}

void CAdcTestPlatDoc::FileSave(BYTE *pbyData, DWORD *pdwSize)
{
	DWORD dwSize;

	// ����������
	if ( pbyData == NULL || pdwSize == NULL )
	{
		return;
	}
	
	dwSize = 0;
	// ������ѡ�����
	*(int*)(pbyData+dwSize) = m_nTestModeSel;
	dwSize += sizeof(int);
	// ���Խ��
	memcpy( pbyData+dwSize, m_daResultBackNoise, CHANNEL_NUM*sizeof(double) );
	dwSize += CHANNEL_NUM*sizeof(double);
	memcpy( pbyData+dwSize, m_daResultSNR, CHANNEL_NUM*sizeof(double) );
	dwSize += CHANNEL_NUM*sizeof(double);
	memcpy( pbyData+dwSize, m_daResultSINAD, CHANNEL_NUM*sizeof(double) );
	dwSize += CHANNEL_NUM*sizeof(double);
	memcpy( pbyData+dwSize, m_daResultSFDR, CHANNEL_NUM*sizeof(double) );
	dwSize += CHANNEL_NUM*sizeof(double);
	memcpy( pbyData+dwSize, m_daResultENOB, CHANNEL_NUM*sizeof(double) );
	dwSize += CHANNEL_NUM*sizeof(double);
	memcpy( pbyData+dwSize, m_daResultChanDisturbA, CHANNEL_NUM*sizeof(double) );
	dwSize += CHANNEL_NUM*sizeof(double);
	memcpy( pbyData+dwSize, m_daResultChanDisturbB, CHANNEL_NUM*sizeof(double) );
	dwSize += CHANNEL_NUM*sizeof(double);
	memcpy( pbyData+dwSize, m_daResultChanDisturbC, CHANNEL_NUM*sizeof(double) );
	dwSize += CHANNEL_NUM*sizeof(double);
	memcpy( pbyData+dwSize, m_daResultChanDisturbD, CHANNEL_NUM*sizeof(double) );
	dwSize += CHANNEL_NUM*sizeof(double);
	// ��������
	memcpy( pbyData+dwSize, m_waCh1Signal, MAX_DEPTH*2 );
	dwSize += MAX_DEPTH*2;
	memcpy( pbyData+dwSize, m_waCh2Signal, MAX_DEPTH*2 );
	dwSize += MAX_DEPTH*2;
	memcpy( pbyData+dwSize, m_waCh3Signal, MAX_DEPTH*2 );
	dwSize += MAX_DEPTH*2;
	memcpy( pbyData+dwSize, m_waCh4Signal, MAX_DEPTH*2 );
	dwSize += MAX_DEPTH*2;
	// ����ֵ	
	*pdwSize = dwSize;
}

void CAdcTestPlatDoc::FileOpen( BYTE* pbyData )
{
	DWORD dwSize;

	// ������
	if ( pbyData == NULL )
	{
		return;
	}
	
	dwSize = 0;
	// ������ѡ�����
	m_nTestModeSel = *(int*)(pbyData+dwSize);
	dwSize += sizeof(int);
	// ���Խ��	
	memcpy( m_daResultBackNoise, pbyData+dwSize, CHANNEL_NUM*sizeof(double) );
	dwSize += CHANNEL_NUM*sizeof(double);
	memcpy( m_daResultSNR, pbyData+dwSize, CHANNEL_NUM*sizeof(double) );
	dwSize += CHANNEL_NUM*sizeof(double);
	memcpy( m_daResultSINAD, pbyData+dwSize, CHANNEL_NUM*sizeof(double) );
	dwSize += CHANNEL_NUM*sizeof(double);
	memcpy( m_daResultSFDR, pbyData+dwSize, CHANNEL_NUM*sizeof(double) );
	dwSize += CHANNEL_NUM*sizeof(double);
	memcpy( m_daResultENOB, pbyData+dwSize, CHANNEL_NUM*sizeof(double) );
	dwSize += CHANNEL_NUM*sizeof(double);
	memcpy( m_daResultChanDisturbA, pbyData+dwSize, CHANNEL_NUM*sizeof(double) );
	dwSize += CHANNEL_NUM*sizeof(double);
	memcpy( m_daResultChanDisturbB, pbyData+dwSize, CHANNEL_NUM*sizeof(double) );
	dwSize += CHANNEL_NUM*sizeof(double);
	memcpy( m_daResultChanDisturbC, pbyData+dwSize, CHANNEL_NUM*sizeof(double) );
	dwSize += CHANNEL_NUM*sizeof(double);
	memcpy( m_daResultChanDisturbD, pbyData+dwSize, CHANNEL_NUM*sizeof(double) );
	dwSize += CHANNEL_NUM*sizeof(double);
	// ��������	
	memcpy( (BYTE*)m_waCh1Signal, pbyData+dwSize,  MAX_DEPTH*2 );
	dwSize += MAX_DEPTH*2;
	memcpy( (BYTE*)m_waCh2Signal, pbyData+dwSize,  MAX_DEPTH*2 );
	dwSize += MAX_DEPTH*2;
	memcpy( (BYTE*)m_waCh3Signal, pbyData+dwSize,  MAX_DEPTH*2 );
	dwSize += MAX_DEPTH*2;
	memcpy( (BYTE*)m_waCh4Signal, pbyData+dwSize,  MAX_DEPTH*2 );
	dwSize += MAX_DEPTH*2;
}

void CAdcTestPlatDoc::GenFileName(CString &fileName)
{
	SYSTEMTIME CurrentTime;
	CString strTime;
	CString strMsg;
	GetSystemTime( &CurrentTime );	
	//CurrentTime.wHour += 8;
	strTime.Format( "%04d%02d%02d%02d%02d%02d", CurrentTime.wYear, CurrentTime.wMonth,
		CurrentTime.wDay, CurrentTime.wHour, CurrentTime.wMinute,CurrentTime.wSecond );
	fileName += strTime;

}
void CAdcTestPlatDoc::GetData()
{
	DWORD dwCmd;
	//DWORD dwState;
	DWORD dwTemp = 0;
	CString strCRC = "";
	CString strBag = "";
	CString strFileNamePre = "ADC";

	CheckFC();

	// ���ò����������(ע��������1����1K)
	dwCmd = (CMD_IQ_DEPTH << 16) + m_nAlgDepth / 1024;
	SendCommand( dwCmd );
	Sleep(1);

	GenFileName(strFileNamePre);

	CmdnStat(CHAN_AI, strCRC, strBag);
	// ȡ��
	DmaRead( ((CAdcTestPlatApp*)AfxGetApp())->m_hDevice,
		(BYTE*)m_DmaABuffer, LOCAL_ADDR_DMA, m_nAlgDepth*2*sizeof(short) );

	for ( dwTemp = 0; dwTemp < m_nAlgDepth; dwTemp ++)
	{
		m_waCh1Signal[dwTemp] = m_DmaABuffer[dwTemp*2+1];
	}
	 	
	SaveFile(strFileNamePre + "CHA", m_waCh1Signal);

	CmdnStat(CHAN_BI, strCRC, strBag);
	// ȡ��
	DmaRead( ((CAdcTestPlatApp*)AfxGetApp())->m_hDevice,
		(BYTE*)m_DmaBBuffer, LOCAL_ADDR_DMA, m_nAlgDepth*2*sizeof(short) );
	
	for ( dwTemp = 0; dwTemp < m_nAlgDepth; dwTemp ++)
	{
		m_waCh2Signal[dwTemp] = m_DmaBBuffer[dwTemp*2+1];
	}
	
	SaveFile(strFileNamePre + "CHB", m_waCh1Signal);

	CmdnStat(CHAN_CI, strCRC, strBag);
	// ȡ��
	DmaRead( ((CAdcTestPlatApp*)AfxGetApp())->m_hDevice,
		(BYTE*)m_DmaCBuffer, LOCAL_ADDR_DMA, m_nAlgDepth*2*sizeof(short) );
	
	for ( dwTemp = 0; dwTemp < m_nAlgDepth; dwTemp ++)
	{
		m_waCh3Signal[dwTemp] = m_DmaCBuffer[dwTemp*2+1];
	}
	
	SaveFile(strFileNamePre + "CHC", m_waCh1Signal);

	CmdnStat(CHAN_DI, strCRC, strBag);
	// ȡ��
	DmaRead( ((CAdcTestPlatApp*)AfxGetApp())->m_hDevice,
		(BYTE*)m_DmaDBuffer, LOCAL_ADDR_DMA, m_nAlgDepth*2*sizeof(short) );
	
	for ( dwTemp = 0; dwTemp < m_nAlgDepth; dwTemp ++)
	{
		m_waCh4Signal[dwTemp] = m_DmaDBuffer[dwTemp*2+1];
	}
	
	SaveFile(strFileNamePre + "CHD", m_waCh1Signal);

}

void CAdcTestPlatDoc::SaveFile(CString strFileNamePre, short * m_Data)
{
	// �����ļ�
	if ( m_bAlgAutoSave )
	{
		CString strDataFileName = strFileNamePre + ".txt";	
		CString strData;
		CStdioFile file;
		file.Open( strDataFileName, CFile::modeWrite | CFile::modeCreate | CFile::typeText  );
		for ( int i = 0; i < m_nAlgDepth; i++ )
		{		
			strData.Format( "%d\n", m_Data[i] );
			file.WriteString( strData );
// 			strData = Dec2Bin(m_waCh1Signal[i]);
// 			file.WriteString( strData );
		}	
		file.Close();
	}
}

void CAdcTestPlatDoc::CmdnStat(int Chan, CString &strCRC, CString &strBag)
{
	DWORD dwCmd;
	DWORD dwTemp = 0;
	static DWORD dwLastTick, dwTickCnt;
	dwLastTick = GetTickCount();

	
	// ��ѡ��ͨ��
//	if (Chan >> 4 == 1)
	{
		dwCmd = ( (DWORD)CMD_SELECT << 16 ) + ( 32 << 6 ) + Chan;
		SendCommand( dwCmd );
	}
	// �ɼ�IQ��������
	dwCmd = (CMD_COLLECT << 16) + Chan;
	SendCommand( dwCmd );
	// ��ѯ״̬
	IoRead( LOCAL_ADDR_CHECK, &dwTemp );
//	Sleep(1);
// 	if ( dwTemp & 0x40000000 )
// 	{
// 		strCRC += "I";
// 	}
// 	if ( dwTemp & 0x20000000 )
// 	{
// 		strBag += "Q";
// 	}
	dwTickCnt = GetTickCount() - dwLastTick;
	TRACE("\nCmdnStat: %d", dwTickCnt);

}
void CAdcTestPlatDoc::TestAlg()
{
	DWORD dwCmd;
	DWORD dwState;
	DWORD dwTemp = 0;
	CString strCRC = "";
	CString strBag = "";
	static DWORD dwLastTick, dwTickCnt;
	dwLastTick = GetTickCount();

	CheckFC();
	// ����IQ��������������(ע��������1����1K)
	dwCmd = (CMD_IQ_DEPTH << 16) + m_nAlgDepth / 1024;
	SendCommand( dwCmd );
	// ��ѯ�Ƿ�ɼ����	
	do 
	{
		dwState = 0;
		IoRead( LOCAL_ADDR_CHECK, &dwState );
	}
	while (0);

	CString strFileNamePre = "IQ";
	GenFileName(strFileNamePre);

	// ȡ����������ϴε�����
	memset( m_DmaABuffer, 0, m_nAlgDepth*2*sizeof(short) );
	memset( m_DmaBBuffer, 0, m_nAlgDepth*2*sizeof(short) );
	memset( m_DmaCBuffer, 0, m_nAlgDepth*2*sizeof(short) );
	memset( m_DmaDBuffer, 0, m_nAlgDepth*2*sizeof(short) );

	CmdnStat(CHAN_AI, strCRC, strBag);
	// ȡ��
	DmaRead( ((CAdcTestPlatApp*)AfxGetApp())->m_hDevice,
		(BYTE*)m_DmaABuffer, LOCAL_ADDR_DMA, m_nAlgDepth*2*sizeof(short) );
	
	for ( dwTemp = 0; dwTemp < m_nAlgDepth; dwTemp ++)
	{
		m_waAiData[dwTemp] = m_DmaABuffer[dwTemp*2+1];
		m_waAqData[dwTemp] = m_DmaABuffer[dwTemp*2];
	}

	SaveFile(strFileNamePre + "AI", m_waAiData);
	SaveFile(strFileNamePre + "AQ", m_waAqData);

	CmdnStat(CHAN_BI, strCRC, strBag);
	// ȡ��
	DmaRead( ((CAdcTestPlatApp*)AfxGetApp())->m_hDevice,
		(BYTE*)m_DmaBBuffer, LOCAL_ADDR_DMA, m_nAlgDepth*2*sizeof(short) );
	
	for ( dwTemp = 0; dwTemp < m_nAlgDepth; dwTemp ++)
	{
		m_waBiData[dwTemp] = m_DmaBBuffer[dwTemp*2+1];
		m_waBqData[dwTemp] = m_DmaBBuffer[dwTemp*2];
	}
	
	SaveFile(strFileNamePre + "BI", m_waBiData);
	SaveFile(strFileNamePre + "BQ", m_waBqData);

	CmdnStat(CHAN_CI, strCRC, strBag);
	// ȡ��
	DmaRead( ((CAdcTestPlatApp*)AfxGetApp())->m_hDevice,
		(BYTE*)m_DmaCBuffer, LOCAL_ADDR_DMA, m_nAlgDepth*2*sizeof(short) );
	
	for ( dwTemp = 0; dwTemp < m_nAlgDepth; dwTemp ++)
	{
		m_waCiData[dwTemp] = m_DmaCBuffer[dwTemp*2+1];
		m_waCqData[dwTemp] = m_DmaCBuffer[dwTemp*2];
	}
	
	SaveFile(strFileNamePre + "CI", m_waCiData);
	SaveFile(strFileNamePre + "CQ", m_waCqData);

	CmdnStat(CHAN_DI, strCRC, strBag);
	// ȡ��
	DmaRead( ((CAdcTestPlatApp*)AfxGetApp())->m_hDevice,
		(BYTE*)m_DmaDBuffer, LOCAL_ADDR_DMA, m_nAlgDepth*2*sizeof(short) );
	
	for ( dwTemp = 0; dwTemp < m_nAlgDepth; dwTemp ++)
	{
		m_waDiData[dwTemp] = m_DmaDBuffer[dwTemp*2+1];
		m_waDqData[dwTemp] = m_DmaDBuffer[dwTemp*2];
	}
	
	SaveFile(strFileNamePre + "DI", m_waDiData);
	SaveFile(strFileNamePre + "DQ", m_waDqData);

	CMainFrame* pFrame = NULL;
	pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
	if ( pFrame != NULL )
	{
		// ���״̬
		if ( strCRC.GetLength() > 0 )
		{
			strCRC += "��CRC���� ";
		}
		if ( strBag.GetLength() > 0 )
		{
			strBag += "�а���������";
		}
		if ( strCRC.GetLength() > 0 || strBag.GetLength() > 0 )
		{
			pFrame->m_strState = strCRC + strBag;
		}
		else
		{
			pFrame->m_strState = "����ͨ������";
		}
	}
	dwTickCnt = GetTickCount() - dwLastTick;
	TRACE("\nTestAlg: %d", dwTickCnt);

}

void CAdcTestPlatDoc::IoRead( DWORD dwLocalAddr, DWORD* pdwData )
{
	RETURN_CODE rc;

	// ��ǰPCIE�����Ч
	if ( ((CAdcTestPlatApp*)AfxGetApp())->m_hDevice != NULL )
	{
		rc = PlxBusIopRead( ((CAdcTestPlatApp*)AfxGetApp())->m_hDevice,
			IopSpace0,
			dwLocalAddr, 
			TRUE,
			pdwData,
			4,
			BitSize32
			);
		if ( rc != ApiSuccess )
		{
			/* */
			return;
		}
	}
	
}

void CAdcTestPlatDoc::IoWrite(DWORD dwLocalAddr, DWORD dwData)
{
	RETURN_CODE rc;

	/* ��ǰPCIE�����Ч */
	if ( ((CAdcTestPlatApp*)AfxGetApp())->m_hDevice != NULL )
	{
		rc = PlxBusIopWrite( ((CAdcTestPlatApp*)AfxGetApp())->m_hDevice,
			IopSpace0,
			dwLocalAddr, 
			TRUE,
			&dwData,
			4,
			BitSize32
			);
		if ( rc != ApiSuccess )
		{
			/* */
			return;
		}
	}
	
}


void CAdcTestPlatDoc::CalcAlgPerf()
{
	int i,j;
	double numpt;
	double fclk;
	double numbit;
	double SNR;
	double SINAD;
	double SFDR;
	double ENOB;
	//WORD* pwTemp;
	short* pwTemp;
	short* pwTemp2;
	double r;

	numpt = MAX_DEPTH;
	fclk = SAMP_FREQ;
	//numbit = 14;
	numbit = 16;
	static DWORD dwLastTick, dwTickCnt;
	dwLastTick = GetTickCount();

	FakeData();

	for ( i = 0; i < 4; i++ )
	{
		// ѡ��ĳ��ͨ�������ܲ��Խ��
		r = m_nR[i+1];
		switch (i)
		{
			case 0:
			{
				pwTemp = m_waAiData;
				pwTemp2 = m_waAqData;
				break;
			}
			case 1:
			{
				pwTemp = m_waBiData;
				pwTemp2 = m_waBqData;
				break;
			}
			case 2:
			{
				pwTemp = m_waCiData;
				pwTemp2 = m_waCqData;
				break;
			}
			case 3:
			{
				pwTemp = m_waDiData;
				pwTemp2 = m_waDqData;
				break;
			}
			default:
			{
				pwTemp = m_waAiData;
				pwTemp2 = m_waAqData;
				break;
			}
		}
		// ԭʼ����
		for ( j = 0; j < MAX_DEPTH; j++ )
		{
			m_data[j] = pwTemp[j];
			m_data2[j] = pwTemp2[j];
		}		
		// ��ʼ���������

		static std::vector<double> y(MAX_DEPTH);		
		AlgDynTest(m_data, MAX_DEPTH, m_data2, MAX_DEPTH, numpt, fclk, numbit, r, SNR, SINAD, SFDR, ENOB, &y[0]);

		GlobalData& globalData = * GlobalData::lockInstance();		
		copy2vector(globalData.dataSet[i].i, m_data, MAX_DEPTH);		
		copy2vector(globalData.dataSet[i].q, m_data2, MAX_DEPTH);		
		copy2vector(globalData.dataSet[i].y, &y[0], MAX_DEPTH);

		globalData.dataSet[i].SNR = SNR;
		globalData.dataSet[i].SFDR = SFDR;
		globalData.dataSet[i].SINAD = SINAD;
		globalData.dataSet[i].ENOB = ENOB;
		
		globalData.unlock();
	
		// ������
		m_daResultSNR[i] = SNR;
		m_daResultSFDR[i] = SFDR;
		m_daResultSINAD[i] = SINAD;
		m_daResultENOB[i] = ENOB;
	}	
	dwTickCnt = GetTickCount() - dwLastTick;
	TRACE("\nCalcAlgPerf: %d", dwTickCnt);

}


void CAdcTestPlatDoc::PowerOn()
{
	DWORD dwCmd;

	// ��5λΪ0�ϵ�
	dwCmd = (DWORD)CMD_POWER << 16;
	SendCommand( dwCmd );

	Sleep(100);
		
	dwCmd = (CMD_RESET << 16); 
	SendCommand( dwCmd );

}

void CAdcTestPlatDoc::PowerOff()
{
	DWORD dwCmd;

	// ��5λ��1�ϵ�
	dwCmd = ( (DWORD)CMD_POWER << 16 ) + 0x001F;
	SendCommand( dwCmd );
}



CString CAdcTestPlatDoc::Dec2Bin( int x)
{
	CString strRet;
	CString strTemp;

	strRet = ' ';

	x &= 0xFFFF;
	for (int i = 15; i>=0; --i) {
		if ( ((x >> i) & 1) == 1) {
			strRet += '1';
		}
		else{
			strRet += '0';
		}
	}

	strRet += "\r\n";

	return strRet;
}

void CAdcTestPlatDoc::CheckFC()
{
	 	DWORD dwSend, dwRecv, dwCmd;
		CMainFrame* pFrame = NULL;
		pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
	 	dwCmd = 0;
	 	dwRecv = 0;
	 	srand( (unsigned)time( NULL ) );
	 	dwSend = abs( rand() );
	 		 ///���͹���ͨ���������
	 		dwSend &= 0x0000FFFF;
	 		dwCmd = (CMD_FIBER_CHECK << 16) + dwSend;
	 		IoWrite( LOCAL_ADDR_CMD, dwCmd );
	 		Sleep(10);
	 		/// ȡ������
	 		IoRead( LOCAL_ADDR_CHECK, &dwRecv );
	 		dwRecv &= 0x0000FFFF;
		if ( pFrame != NULL )
		{
	 		if ( dwRecv != dwSend )
	 		{
	 			pFrame->m_strState = "���˴������";
	 		}
	 		else
	 		{
	 			pFrame->m_strState = "����ͨ������";
	 		}
		}

}

void CAdcTestPlatDoc::FakeData()
{

#ifdef _DEBUG

	CString strData;
	CStdioFile file;
	BOOL bRet;
	int j;
	
	bRet = file.Open( ".\\IQ20090209013031AI.txt", CFile::modeRead | CFile::typeText  );//V1_0_TB.txt
	if ( bRet )
	{
		for ( j = 0; j < MAX_DEPTH; j++ )
		{			
			file.ReadString(strData);
			m_waAiData[j] = atoi(strData);
			m_waCh1Signal[j] = atoi(strData);
		}
		file.Close();
	}	

	bRet = file.Open( ".\\IQ20090209013031BI.txt", CFile::modeRead | CFile::typeText  );//V1_0_TB.txt
	if ( bRet )
	{
		for ( j = 0; j < MAX_DEPTH; j++ )
		{			
			file.ReadString(strData);
			m_waBiData[j] = atoi(strData);
			m_waCh2Signal[j] = atoi(strData);
		}
		file.Close();
	}	

	bRet = file.Open( ".\\IQ20090209013031CI.txt", CFile::modeRead | CFile::typeText  );//V1_0_TB.txt
	if ( bRet )
	{
		for ( j = 0; j < MAX_DEPTH; j++ )
		{			
			file.ReadString(strData);
			m_waCiData[j] = atoi(strData);
			m_waCh3Signal[j] = atoi(strData);
		}
		file.Close();
	}	

	bRet = file.Open( ".\\IQ20090209013031DI.txt", CFile::modeRead | CFile::typeText  );//V1_0_TB.txt
	if ( bRet )
	{
		for ( j = 0; j < MAX_DEPTH; j++ )
		{			
			file.ReadString(strData);
			m_waDiData[j] = atoi(strData);
			m_waCh4Signal[j] = atoi(strData);
		}
		file.Close();
	}	
	
	bRet = file.Open( ".\\IQ20090209013031AQ.txt", CFile::modeRead | CFile::typeText  );//V1_0_TB.txt
	if ( bRet )
	{
		for ( j = 0; j < MAX_DEPTH; j++ )
		{			
			file.ReadString(strData);
			m_waAqData[j] = atoi(strData);
		}
		file.Close();
	}	
	bRet = file.Open( ".\\IQ20090209013031BQ.txt", CFile::modeRead | CFile::typeText  );//V1_0_TB.txt
	if ( bRet )
	{
		for ( j = 0; j < MAX_DEPTH; j++ )
		{			
			file.ReadString(strData);
			m_waBqData[j] = atoi(strData);
		}
		file.Close();
	}	
	bRet = file.Open( ".\\IQ20090209013031CQ.txt", CFile::modeRead | CFile::typeText  );//V1_0_TB.txt
	if ( bRet )
	{
		for ( j = 0; j < MAX_DEPTH; j++ )
		{			
			file.ReadString(strData);
			m_waCqData[j] = atoi(strData);
		}
		file.Close();
	}	
	bRet = file.Open( ".\\IQ20090209013031DQ.txt", CFile::modeRead | CFile::typeText  );//V1_0_TB.txt
	if ( bRet )
	{
		for ( j = 0; j < MAX_DEPTH; j++ )
		{			
			file.ReadString(strData);
			m_waDqData[j] = atoi(strData);
		}
		file.Close();
	}	

#endif
}