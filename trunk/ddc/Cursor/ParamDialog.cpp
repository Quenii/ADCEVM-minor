// ParamDialog.cpp : implementation file
//

#include "stdafx.h"
#include "adctestplat.h"
#include "ParamDialog.h"
#include "AdcTestPlatDoc.h"
#include "PlxApi.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// 默认地址
DWORD g_dwaAddr[ADDR_PARAM_SIZE] = {
	0x00,
	0x01,
	0x10,
	0x11,
	0x12,
	0x13,
	0x20,
	0x30,
	0x31,
	0x32,
	0x33,
	0x40,
	0x50,
	0x51,
	0x52,
	0x53,
	0x54,
	0x55,
	0x56,
	0x57,
	0x58,
	0x59,
	0x5A,
	0x5B,
	0x5C,
	0x5D,
	0x5E,
	0x5F,
	0x60,
	0x61,
	0x62,
	0x63,
	0x64,
	0x65,
	0x66,
	0x67,
	0x68,
	0x69,
	0x6A,
	0x6B,
	0x6C,
	0x6D,
	0x6E,
	0x6F,
	0x70,
	0x71,
	0x72,
	0x73
};



CString g_strAAddrFileName = "add_a.dat";
CString g_strBAddrFileName = "add_b.dat";
CString g_strCAddrFileName = "add_c.dat";
CString g_strDAddrFileName = "add_d.dat";

#define IQ_SIZE (1024*1024)
//WORD m_waIQData[4*IQ_SIZE*2];
short m_waIQData[4*IQ_SIZE*2];

//#define TEST_DATA

/////////////////////////////////////////////////////////////////////////////
// CParamDialog dialog


CParamDialog::CParamDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CParamDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CParamDialog)
	m_nChanSel = 0;
	m_nChanConfigCtrl = 0;
	m_nDataOutModelSel = 0;
	m_nLvdsAck = 0;
	m_nParaSerSel = 0;
	m_nTest = 0;	
	m_nDepth = MAX_DEPTH / 1024;
	m_pParent = (CTestAlgView*)pParent;
	m_nM0 = 0;
	m_nStart = 0;
	m_strAPath = _T("");
	m_strBPath = _T("");
	m_strCPath = _T("");
	m_strDPath = _T("");
	m_nSampFreq = 80;
	m_nR[1] = 20;
	m_nR[2] = 20;
	m_nR[3] = 20;
	m_nR[4] = 20;
	m_strR = _T("20");
	//}}AFX_DATA_INIT
	memset( m_waIQData, 0, 4*IQ_SIZE*2*sizeof(short) );
	
#ifdef TEST_DATA
	//////////////////////////////////////////////////////////////////
	// 测试数据
	double ppi = 3.1415926535;
	for ( int j = 0; j < MAX_DEPTH; j++ )// 
	{		
		m_waIQData[j] = 16384*sin(2*ppi*j/80);
		m_waIQData[MAX_DEPTH+j] = 16384*sin(2*ppi*j/80);				
	}
	////////////////////////////////////////////////////////////////////
#endif

		// 默认地址	
	memset(m_dwaAAddr, 0x0, DMA_SIZE);
	memset(m_dwaBAddr, 0x0, DMA_SIZE);
	memset(m_dwaCAddr, 0x0, DMA_SIZE);
	memset(m_dwaDAddr, 0x0, DMA_SIZE);
	for ( int i = 0; i < ADDR_PARAM_SIZE; i++ )
	{
		m_dwaAAddr[i] = g_dwaAddr[i];
		m_dwaBAddr[i] = g_dwaAddr[i]+0x100;
		m_dwaCAddr[i] = g_dwaAddr[i]+0x200;
		m_dwaDAddr[i] = g_dwaAddr[i]+0x300;
	}

}

CParamDialog::CParamDialog( int nChanSel, int nChanCogfigCtrl, int nDataOutModeSel,
		int nLvdsAck, int nParaSerSel, int nTest, int nDepth, int nM0, int nStart, 
		CString strAPath, CString strBPath, CString strCPath, CString strDPath,
		DWORD* pdwAParam, DWORD* pdwBParam, DWORD* pdwCParam, DWORD* pdwDParam,
		int nSampFreq, int nR[5]/*1, int nR2, int nR3, int nR4*/,
		CWnd* pParent )
		: CDialog(CParamDialog::IDD, pParent)
{
	m_nChanSel = nChanSel;
	m_nChanConfigCtrl = nChanCogfigCtrl;
	m_nDataOutModelSel = nDataOutModeSel;
	m_nLvdsAck = nLvdsAck;
	m_nParaSerSel = nParaSerSel;
	m_nTest = nTest;	
	m_nDepth = nDepth;
	m_nM0 = nM0;
	m_nStart = nStart;
//	GetDlgItem( IDC_EDIT_A )->SetWindowText( strAPath );
//	GetDlgItem( IDC_EDIT_B )->SetWindowText( strBPath );
//	GetDlgItem( IDC_EDIT_C )->SetWindowText( strCPath );
//	GetDlgItem( IDC_EDIT_D )->SetWindowText( strDPath );
	m_strAPath = strAPath;
	m_strBPath = strBPath;
	m_strCPath = strCPath;
	m_strDPath = strDPath;
	if ( pdwAParam != NULL && pdwBParam != NULL && pdwCParam != NULL && pdwDParam != NULL )
	{
		memcpy( m_dwaAParam, pdwAParam, DMA_SIZE*sizeof(DWORD) );
		memcpy( m_dwaBParam, pdwBParam, DMA_SIZE*sizeof(DWORD) );
		memcpy( m_dwaCParam, pdwCParam, DMA_SIZE*sizeof(DWORD) );
		memcpy( m_dwaDParam, pdwDParam, DMA_SIZE*sizeof(DWORD) );
	}
	m_nSampFreq = nSampFreq;
	int i;
	for (i=1; i<5; ++i)
	{
		m_nR[i] = nR[i];
	}

	m_strR.Format( "%d", m_nR[m_nChanSel+1] );
// 	m_nR1 = nR1;
// 	m_nR2 = nR2;
// 	m_nR3 = nR3;
// 	m_nR4 = nR4;
	// 显示r值
// 	switch ( m_nChanSel )
// 	{
// 		case 0:
// 		{
// 			m_strR.Format( "%d", m_nR1 );
// 			break;
// 		}
// 		case 1:
// 		{
// 			m_strR.Format( "%d", m_nR2 );
// 			break;
// 		}
// 		case 2:
// 		{
// 			m_strR.Format( "%d", m_nR3 );
// 			break;
// 		}
// 		case 3:
// 		{
// 			m_strR.Format( "%d", m_nR4 );
// 			break;
// 		}
// 		default:
// 		{
// 			m_strR.Format( "%d", m_nR1 );
// 			break;
// 		}
// 	}
	
	m_pParent = (CTestAlgView*)pParent;
	
	memset( m_waIQData, 0, 4*IQ_SIZE*2*sizeof(short) );
	
#ifdef TEST_DATA
	//////////////////////////////////////////////////////////////////
	// 测试数据
	double ppi = 3.1415926535;
	for ( int j = 0; j < MAX_DEPTH; j++ )// 
	{		
		m_waIQData[j] = 16384*sin(2*ppi*j/80);
		m_waIQData[MAX_DEPTH+j] = 16384*sin(2*ppi*j/80);				
	}
	////////////////////////////////////////////////////////////////////
#endif

	
	// 默认地址	
	memset(m_dwaAAddr, 0x0, DMA_SIZE);
	memset(m_dwaBAddr, 0x0, DMA_SIZE);
	memset(m_dwaCAddr, 0x0, DMA_SIZE);
	memset(m_dwaDAddr, 0x0, DMA_SIZE);
	for ( i = 0; i < ADDR_PARAM_SIZE; i++ )
	{
		m_dwaAAddr[i] = g_dwaAddr[i];
		m_dwaBAddr[i] = g_dwaAddr[i]+0x100;
		m_dwaCAddr[i] = g_dwaAddr[i]+0x200;
		m_dwaDAddr[i] = g_dwaAddr[i]+0x300;
	}

// 	if ( ((CAdcTestPlatApp*)AfxGetApp())->m_hDevice != NULL )
// 	{
// 		((CAdcTestPlatApp*)AfxGetApp())->DetectedCards();
// 	}

	//qq	if ( !((CAdcTestPlatApp*)AfxGetApp())->DetectedCards() )

}

void CParamDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CParamDialog)
	DDX_Control(pDX, IDC_EDIT_R, m_edtR);
	DDX_Control(pDX, IDC_STATIC_REG, m_stcParamReg);
	DDX_Control(pDX, IDC_STATIC_CONTROL, m_stcParamControl);
	DDX_Control(pDX, IDC_STATIC_INPUT, m_stcParamInput);
	DDX_Radio(pDX, IDC_RADIO_CHAN_SEL, m_nChanSel);
	DDX_Radio(pDX, IDC_RADIO_CHANNEL_CONFIG_CTRL, m_nChanConfigCtrl);
	DDX_Radio(pDX, IDC_RADIO_DATAOUT_MODEL_SEL, m_nDataOutModelSel);
	DDX_Radio(pDX, IDC_RADIO_LVDS_ACK, m_nLvdsAck);
	DDX_Radio(pDX, IDC_RADIO_PARA_SER_SEL, m_nParaSerSel);
	DDX_Radio(pDX, IDC_RADIO_TEST, m_nTest);
	DDX_Text(pDX, IDC_EDIT_DEPTH, m_nDepth);
	DDV_MinMaxInt(pDX, m_nDepth, 1, 1024);
	DDX_Radio(pDX, IDC_RADIO_M0, m_nM0);
	DDX_Radio(pDX, IDC_RADIO_START, m_nStart);
	DDX_Text(pDX, IDC_EDIT_A, m_strAPath);
	DDX_Text(pDX, IDC_EDIT_B, m_strBPath);
	DDX_Text(pDX, IDC_EDIT_C, m_strCPath);
	DDX_Text(pDX, IDC_EDIT_D, m_strDPath);
	DDX_Text(pDX, IDC_EDIT_SAMP_FREQ, m_nSampFreq);
	DDX_Text(pDX, IDC_EDIT_R, m_strR);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CParamDialog, CDialog)
	//{{AFX_MSG_MAP(CParamDialog)
	ON_BN_CLICKED(ID_BTN_Read1, OnBTNRead1)
	ON_BN_CLICKED(ID_BTN_Read2, OnBTNRead2)
	ON_BN_CLICKED(ID_BTN_Read3, OnBTNRead3)
	ON_BN_CLICKED(ID_BTN_Read4, OnBTNRead4)
	ON_BN_CLICKED(IDC_RADIO_CHAN_SEL, OnRadioChanSel)
	ON_BN_CLICKED(IDC_RADIO_CHAN_SEL2, OnRadioChanSel2)
	ON_BN_CLICKED(IDC_RADIO_CHAN_SEL3, OnRadioChanSel3)
	ON_BN_CLICKED(IDC_RADIO_CHAN_SEL4, OnRadioChanSel4)
	ON_BN_CLICKED(ID_BTN_SEND, OnBtnSend)
	ON_BN_CLICKED(IDC_RADIO_CHANNEL_CONFIG_CTRL, OnRadioChannelConfigCtrl)
	ON_BN_CLICKED(IDC_RADIO_DATAOUT_MODEL_SEL, OnRadioDataoutModelSel)
	ON_BN_CLICKED(IDC_RADIO_LVDS_ACK, OnRadioLvdsAck)
	ON_BN_CLICKED(IDC_RADIO_PARA_SER_SEL, OnRadioParaSerSel)
	ON_BN_CLICKED(IDC_RADIO_TEST, OnRadioTest)
	ON_BN_CLICKED(IDC_RADIO_CHANNEL_CONFIG_CTRL1, OnRadioChannelConfigCtrl1)
	ON_BN_CLICKED(IDC_RADIO_DATAOUT_MODEL_SEL1, OnRadioDataoutModelSel1)
	ON_BN_CLICKED(IDC_RADIO_LVDS_ACK1, OnRadioLvdsAck1)
	ON_BN_CLICKED(IDC_RADIO_LVDS_ACK2, OnRadioLvdsAck2)
	ON_BN_CLICKED(IDC_RADIO_PARA_SER_SEL1, OnRadioParaSerSel1)
	ON_BN_CLICKED(IDC_RADIO_M0, OnM0_0)
	ON_BN_CLICKED(IDC_RADIO_M0_1, OnM0_1)
	ON_BN_CLICKED(IDC_RADIO_M0_2, OnM0_a)
	ON_BN_CLICKED(IDC_RADIO_START, OnStart0)
	ON_BN_CLICKED(IDC_RADIO_START_1, OnStart1)
	ON_BN_CLICKED(IDC_RADIO_START_2, OnStarta)	
	ON_BN_CLICKED(IDC_RADIO_TEST1, OnRadioTest1)
	ON_BN_CLICKED(IDC_BUTTON_COLLECT, OnButtonCollect)
	ON_WM_CLOSE()
	ON_BN_CLICKED(ID_BTN_SAVE, OnBtnSave)
	ON_BN_CLICKED(ID_BTN_RESET, OnBtnReset)
	ON_BN_CLICKED(ID_BTN_REPLY, OnBtnReply)
	ON_EN_CHANGE(IDC_EDIT_R, OnChangeEditR)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CParamDialog message handlers

void CParamDialog::OnBTNRead1() 
{
	CString strParam;
	CString strFileName = FileOpen( m_dwaAParam );
	// 打开有效文件
	if ( !strFileName.IsEmpty() )
	{
		// 显示通道
		m_nChanSel = 0;	
		// 显示路径
		//GetDlgItem( IDC_EDIT_A )->SetWindowText( strFileName );
		m_strAPath = strFileName;
		// 通道参数
		OnRadioChanSel();
		// 更新
		UpdateData( FALSE );
	}
	
}

void CParamDialog::OnBTNRead2() 
{
	// TODO: Add your control notification handler code here
	CString strParam;
	CString strFileName = FileOpen( m_dwaBParam );
	// 打开有效文件
	if ( !strFileName.IsEmpty() )
	{
		// 显示通道
		m_nChanSel = 1;	
		// 显示路径
		//GetDlgItem( IDC_EDIT_B )->SetWindowText( strFileName );
		m_strBPath = strFileName;
		// 显示参数
		OnRadioChanSel2();
		// 更新
		UpdateData( FALSE );
	}
}

void CParamDialog::OnBTNRead3() 
{
	// TODO: Add your control notification handler code here
	CString strParam;
	CString strFileName = FileOpen( m_dwaCParam );
	// 打开有效文件
	if ( !strFileName.IsEmpty() )
	{
		// 显示通道
		m_nChanSel = 2;	
		// 显示路径
		//GetDlgItem( IDC_EDIT_C )->SetWindowText( strFileName );
		m_strCPath = strFileName;
		// 显示参数
		OnRadioChanSel3();
		// 更新
		UpdateData( FALSE );
	}
}

void CParamDialog::OnBTNRead4() 
{
	// TODO: Add your control notification handler code here
	CString strParam;
	CString strFileName = FileOpen( m_dwaDParam );
	// 打开有效文件
	if ( !strFileName.IsEmpty() )
	{
		// 显示通道
		m_nChanSel = 3;	
		// 显示路径
		//GetDlgItem( IDC_EDIT_D )->SetWindowText( strFileName );
		m_strDPath = strFileName;
		// 显示参数
		OnRadioChanSel4();
		// 更新
		UpdateData( FALSE );
	}
}

/* 打开参数文件，并把ASCII文件转换为十六进制保存 */
CString CParamDialog::FileOpen( DWORD* pdwDataBuf )
{
	CString strDefExt;
	CString strDefFileName;
	CString strFilter;	
	char szCurDir[100];	
	CString strFileName;
	CStdioFile fileOpen;
	CString strTemp;
	DWORD dwData;
	char c;
	int i;

	strFileName.Empty();
	::GetCurrentDirectory( 100, szCurDir );	

	strDefExt = ".dat";	
	strDefFileName = szCurDir;
	strDefFileName += "\\*.dat";
	// 文件类型不能加括号
	strFilter = "param file (*.dat)|*.dat|all files (*.*)|*.*||";	

	// 文件打开对话框
	CFileDialog fileDlg( TRUE, strDefExt, strDefFileName, 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		strFilter, this );
	
	if ( fileDlg.DoModal() == IDOK )
	{
		strFileName = fileDlg.GetPathName();
		if ( fileOpen.Open(strFileName , CFile::modeRead | CFile::typeText ) )
		{			
			// 至少包含48行 
			for ( i = 0; i < ADDR_PARAM_SIZE; i++ )
			{
				if ( fileOpen.ReadString( strTemp ) )
				{
					if ( strTemp.GetLength() == 4 )
					{
						dwData = 0;
						for ( int j = 0; j < 4; j++ )
						{
							c = strTemp.GetAt(j);
							if ( c >= '0' && c <= '9' )
							{
								dwData += (c - '0') << (12-4*j);
							}
							else if ( c >= 'a' && c <= 'f' )
							{
								dwData += (c - 'a' + 10) << (12-4*j);
							}
							else if ( c >= 'A' && c <= 'F' )
							{
								dwData += (c - 'A' + 10) << (12-4*j);
							}
						}
						//
						pdwDataBuf[i] = dwData;
					}
				}
			}
			fileOpen.Close();
		}
		
	}
	return strFileName;
}

void CParamDialog::OnRadioChanSel() 
{
	CString strParam;
	int i;

	m_nChanSel = 0;
	// 显示参数
	for ( i = 0; i < ADDR_PARAM_SIZE; i++ )
	{
		strParam.Format( "%04X", m_dwaAParam[i] );
		GetDlgItem( IDC_EDIT_A_REG0+i )->SetWindowText( strParam );
	}
	// 显示地址
	for ( i = 0; i < ADDR_PARAM_SIZE; i++ )
	{
		strParam.Format( "%03X", m_dwaAAddr[i] );
		GetDlgItem( IDC_STATIC_ADDR0+i )->SetWindowText( strParam );
	}
	// 显示r值(UpdateData使按钮的选择返回原来的项?)
	m_strR.Format( "%d", m_nR[1] );
	UpdateData( FALSE );
	// SetWindowText使原来文件名文本框的内容被清零?
	//strParam.Format( "%d", m_nR1 );
	//GetDlgItem( IDC_EDIT_R )->SetWindowText( strParam );
	//m_edtR.SetWindowText( strParam );
}

void CParamDialog::OnRadioChanSel2() 
{
	// TODO: Add your control notification handler code here
	CString strParam;
	int i;

	m_nChanSel = 1;
	// 显示参数
	for ( i = 0; i < ADDR_PARAM_SIZE; i++ )
	{
		strParam.Format( "%04X", m_dwaBParam[i] );
		GetDlgItem( IDC_EDIT_A_REG0+i )->SetWindowText( strParam );
	}
	// 显示地址
	for ( i = 0; i < ADDR_PARAM_SIZE; i++ )
	{
		strParam.Format( "%03X", m_dwaBAddr[i] );
		GetDlgItem( IDC_STATIC_ADDR0+i )->SetWindowText( strParam );
	}
	// 显示r值
	m_strR.Format( "%d", m_nR[2] );
	UpdateData( FALSE );
	//strParam.Format( "%d", m_nR2 );
	//GetDlgItem( IDC_EDIT_R )->SetWindowText( strParam );
}

void CParamDialog::OnRadioChanSel3() 
{
	// TODO: Add your control notification handler code here
	CString strParam;
	int i;

	m_nChanSel = 2;
	// 显示参数
	for ( i = 0; i < ADDR_PARAM_SIZE; i++ )
	{
		strParam.Format( "%04X", m_dwaCParam[i] );
		GetDlgItem( IDC_EDIT_A_REG0+i )->SetWindowText( strParam );
	}	
	// 显示地址
	for ( i = 0; i < ADDR_PARAM_SIZE; i++ )
	{
		strParam.Format( "%03X", m_dwaCAddr[i] );
		GetDlgItem( IDC_STATIC_ADDR0+i )->SetWindowText( strParam );
	}
	// 显示r值
	m_strR.Format( "%d", m_nR[3] );
	UpdateData( FALSE );
	//strParam.Format( "%d", m_nR3 );
	//GetDlgItem( IDC_EDIT_R )->SetWindowText( strParam );
}

void CParamDialog::OnRadioChanSel4() 
{
	// TODO: Add your control notification handler code here
	CString strParam;
	int i;

	m_nChanSel = 3;
	// 显示参数
	for ( i = 0; i < ADDR_PARAM_SIZE; i++ )
	{
		strParam.Format( "%04X", m_dwaDParam[i] );
		GetDlgItem( IDC_EDIT_A_REG0+i )->SetWindowText( strParam );
	}	
	// 显示地址
	for ( i = 0; i < ADDR_PARAM_SIZE; i++ )
	{
		strParam.Format( "%03X", m_dwaDAddr[i] );
		GetDlgItem( IDC_STATIC_ADDR0+i )->SetWindowText( strParam );
	}
	// 显示r值
	m_strR.Format( "%d", m_nR[4] );
	UpdateData( FALSE );
	//strParam.Format( "%d", m_nR4 );
	//GetDlgItem( IDC_EDIT_R )->SetWindowText( strParam );
}

BOOL CParamDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	int i;
/*
	// 初始化参数缓冲区
	memset( m_dwaAParam, 0, sizeof(DWORD)*DMA_SIZE );
	memset( m_dwaBParam, 0, sizeof(DWORD)*DMA_SIZE );
	memset( m_dwaCParam, 0, sizeof(DWORD)*DMA_SIZE );
	memset( m_dwaDParam, 0, sizeof(DWORD)*DMA_SIZE );
*/
	UpdateData( FALSE );

	// 默认地址	
	for ( i = 0; i < ADDR_PARAM_SIZE; i++ )
	{
		m_dwaAAddr[i] = g_dwaAddr[i];
		m_dwaBAddr[i] = g_dwaAddr[i]+0x100;
		m_dwaCAddr[i] = g_dwaAddr[i]+0x200;
		m_dwaDAddr[i] = g_dwaAddr[i]+0x300;
	}
	// 如果找到地址文件，按照地址文件显示地址
	
	// 打开

	// 默认选择A通道
	//m_nChanSel = 0;
	
	// 根据通道做不同的设置
	switch ( m_nChanSel )
	{
		case 0:
		{
			OnRadioChanSel();
			break;
		}
		case 1:
		{
			OnRadioChanSel2();
			break;
		}
		case 2:
		{
			OnRadioChanSel3();
			break;
		}
		case 3:
		{
			OnRadioChanSel4();
			break;
		}
		default:
		{
			OnRadioChanSel();
			break;
		}
	}
	
	// 蓝色标签
	m_stcParamInput.SetTextColor( RGB(0,0,255) );
	m_stcParamControl.SetTextColor( RGB(0,0,255) );
	m_stcParamReg.SetTextColor( RGB(0,0,255) );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

// 发送当前配置
void CParamDialog::OnBtnSend() 
{
	DWORD dwCmd;

	// 发送配置参数前，先把DDC控制命令发送下去
	ChangeMode();

	UpdateData( TRUE );
	// 界面输入的参数更新到缓冲区
	CheckData();
	// 发送配置参数
	if ( ((CAdcTestPlatApp*)AfxGetApp())->m_hDevice != NULL )
	{
		// 同步配置
		if ( m_nChanConfigCtrl == 1 )
		{		
			// 地址
			DmaWrite( ((CAdcTestPlatApp*)AfxGetApp())->m_hDevice, 
				(BYTE*)m_dwaAAddr, LOCAL_ADDR_SYN_ADDR, DMA_SIZE*4 );
			// 参数
			DmaWrite( ((CAdcTestPlatApp*)AfxGetApp())->m_hDevice, 
				(BYTE*)m_dwaAParam, LOCAL_ADDR_SYN_PARAM, DMA_SIZE*4 );
			// 改变DDC配置寄存器
			dwCmd = (CMD_SET_CONFIG << 16) + 0x0001;
			SendCommand( dwCmd );		
		}
		// 独立配置
		else if ( m_nChanConfigCtrl == 0 )
		{
			// 目前使用下面一个一个发送方式
			for ( int i = 0; i < 4; i++ )
			{
				SendByChannel( i );
			}
		}

	}
	
	
}

/* DMA发送 */
void CParamDialog::DmaWrite( HANDLE hDevice, BYTE *pbyData, DWORD dwLocalAddr, DWORD dwSize )
{
	RETURN_CODE rc;
	DMA_CHANNEL_DESC DmaDesc;
	DMA_TRANSFER_ELEMENT DmaData;

	// Clear DMA descriptor structure
	memset(	&DmaDesc, 0, sizeof(DMA_CHANNEL_DESC) );
	// Set up DMA configuration structure
	DmaDesc.EnableReadyInput = 1;
	DmaDesc.EnableIopBurst = 1;
	DmaDesc.DmaStopTransferMode = AssertBLAST;
	DmaDesc.DmaChannelPriority = Rotational;
	DmaDesc.IopBusWidth = 3; // 32 bit bus
	DmaDesc.HoldIopAddrConst = 1;
	DmaDesc.EnableBTERMInput = 1;

	rc = PlxDmaSglChannelOpen( hDevice, PrimaryPciChannel0, &DmaDesc );
	if (rc != ApiSuccess)
	{
		// ERROR – Unable to open DMA channel
		return;
	}
	// DMA paramter
	DmaData.u.UserVa = (U32)pbyData;
	DmaData.LocalAddr = dwLocalAddr;
	DmaData.TransferCount = dwSize ;
	DmaData.LocalToPciDma = 0;
	// FALSE - Wait for completion
	rc = PlxDmaSglTransfer( hDevice, PrimaryPciChannel0, &DmaData, FALSE );
	if (rc != ApiSuccess)
	{
		// ERROR – Unable to transfer buffer
		return;
	}
	/* Dma close */
	rc = PlxDmaSglChannelClose( hDevice, PrimaryPciChannel0 );
	if (rc != ApiSuccess)
	{
		// ERROR – Unable to transfer buffer
		return;
	} 
}

void CParamDialog::SendCommand(DWORD dwCmd)
{
	RETURN_CODE rc;

	/* 当前PCIE句柄有效 */
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

/* 改变DDC配置寄存器 */
void CParamDialog::OnRadioChannelConfigCtrl() 
{
	// TODO: Add your control notification handler code here
	//OnBtnSend();
	ChangeMode();
}

void CParamDialog::OnRadioChannelConfigCtrl1() 
{
	// TODO: Add your control notification handler code here
	//OnBtnSend();
	ChangeMode();
}

void CParamDialog::OnRadioDataoutModelSel() 
{
	// TODO: Add your control notification handler code here
	ChangeMode();
}

void CParamDialog::OnRadioDataoutModelSel1() 
{
	// TODO: Add your control notification handler code here
	ChangeMode();
}

void CParamDialog::OnRadioLvdsAck() 
{
	// TODO: Add your control notification handler code here
	ChangeMode();
}

void CParamDialog::OnRadioLvdsAck1() 
{
	// TODO: Add your control notification handler code here
	ChangeMode();
}

void CParamDialog::OnRadioLvdsAck2() 
{
	// TODO: Add your control notification handler code here
	ChangeMode();
}

void CParamDialog::OnRadioParaSerSel() 
{
	// TODO: Add your control notification handler code here
	ChangeMode();
}

void CParamDialog::OnRadioParaSerSel1() 
{
	// TODO: Add your control notification handler code here
	ChangeMode();
}

void CParamDialog::OnRadioTest() 
{
	// TODO: Add your control notification handler code here
	ChangeMode();
}

void CParamDialog::OnRadioTest1() 
{
	// TODO: Add your control notification handler code here
	ChangeMode();
}

void CParamDialog::OnM0_0() 
{
	// TODO: Add your control notification handler code here
	ChangeMode();
}

void CParamDialog::OnM0_1() 
{
	// TODO: Add your control notification handler code here
	ChangeMode();
}

void CParamDialog::OnM0_a() 
{
	// TODO: Add your control notification handler code here
	ChangeMode();
}

void CParamDialog::OnStart0() 
{
	// TODO: Add your control notification handler code here
	ChangeMode();
}

void CParamDialog::OnStart1() 
{
	// TODO: Add your control notification handler code here
	ChangeMode();
}

void CParamDialog::OnStarta() 
{
	// TODO: Add your control notification handler code here
	ChangeMode();
}

void CParamDialog::ChangeMode()
{
	DWORD dwCmd;

	/* 同步到变量 */
	UpdateData( TRUE );
	// 保存到算法视图，因为在doc中采集数据前会先发送算法视图定义的设置
	if ( m_pParent != NULL )
	{		
		m_pParent->m_nChanConfigCtrl = m_nChanConfigCtrl;
		m_pParent->m_nDataOutModelSel = m_nDataOutModelSel;
		m_pParent->m_nLvdsAck = m_nLvdsAck;
		m_pParent->m_nParaSerSel = m_nParaSerSel;
		m_pParent->m_nTest = m_nTest;		
		m_pParent->m_nM0 = m_nM0;
		m_pParent->m_nStart = m_nStart;
	}
	/* 改变工作模式 */
	dwCmd = (CMD_MODE << 16) 
		+ (m_nStart << 8)
		+ (m_nM0 << 6)
		+ (m_nChanConfigCtrl << 5)
		+ (m_nDataOutModelSel << 4)
		+ (m_nParaSerSel << 3)
		+ (m_nLvdsAck << 1)
		+ m_nTest;
	SendCommand( dwCmd );
}

// 
void CParamDialog::OnButtonCollect() 
{
//	DWORD dwCmd;
//	DWORD dwState;
//
//	// 同步到变量
//	UpdateData( TRUE );
	
}

void CParamDialog::IoRead( DWORD dwLocalAddr, DWORD* pdwData )
{
	RETURN_CODE rc;

	// 当前PCIE句柄有效
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

void CParamDialog::IoWrite( DWORD dwLocalAddr, DWORD* pdwData )
{
	RETURN_CODE rc;
	
	// 当前PCIE句柄有效
	if ( ((CAdcTestPlatApp*)AfxGetApp())->m_hDevice != NULL )
	{
		rc = PlxBusIopWrite( ((CAdcTestPlatApp*)AfxGetApp())->m_hDevice,
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
void CParamDialog::DmaRead( HANDLE hDevice, BYTE *pbyData, DWORD dwLocalAddr, DWORD dwSize)
{
	RETURN_CODE rc;
	DMA_CHANNEL_DESC DmaDesc;
	DMA_TRANSFER_ELEMENT DmaData;

	// 检查输入参数
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


		rc = PlxDmaSglChannelOpen( hDevice, PrimaryPciChannel0, &DmaDesc );
		if (rc != ApiSuccess)
		{
			// ERROR – Unable to open DMA channel
			return;
		}
		// DMA paramter
		DmaData.u.UserVa = (U32)pbyData;
		DmaData.LocalAddr = dwLocalAddr;
		DmaData.TransferCount = dwSize;
		DmaData.LocalToPciDma = 1;

		DWORD dwValid;
		IoRead( 0, &dwValid);
		if (dwValid * 4 >= dwSize)
		{
			dwValid = dwSize / 4;
			IoWrite(0, &dwValid);
			rc = PlxDmaSglTransfer( hDevice, PrimaryPciChannel0, &DmaData, FALSE );
			if (rc != ApiSuccess)
			{
				// ERROR – Unable to transfer buffer
				return;
			}
		}
		// FALSE - Wait for completion
		/* Dma close */
		rc = PlxDmaSglChannelClose( hDevice, PrimaryPciChannel0 );
		if (rc != ApiSuccess)
		{
			// ERROR – Unable to transfer buffer
			return;
		} 
		PlxPciBoardReset( hDevice );
	}	
}

void CParamDialog::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	// 删除对话框对象
	//delete this;

	CDialog::PostNcDestroy();
}

// 检查配置参数的合法性
void CParamDialog::CheckData()
{
	CString strParam;
	int i;
	int j;
	int c;
	DWORD dwData;
	DWORD* pdwTemp = NULL;

	// 根据当前选择，查找对应的参数缓冲区
	UpdateData( TRUE );
	switch ( m_nChanSel )
	{
		case 0:
		{
			pdwTemp = m_dwaAParam;
			break;
		}
		case 1:
		{
			pdwTemp = m_dwaBParam;
			break;
		}
		case 2:
		{
			pdwTemp = m_dwaCParam;
			break;
		}
		case 3:
		{
			pdwTemp = m_dwaDParam;
			break;
		}
		default:
		{
			pdwTemp = m_dwaAParam;
			break;
		}
	}
	// 检查配置参数
	for ( i = 0; i < ADDR_PARAM_SIZE; i++ )
	{		
		GetDlgItem( IDC_EDIT_A_REG0+i )->GetWindowText( strParam );
		// 长度检查
		if ( strParam.GetLength() != 4 )
		{
			GetDlgItem( IDC_EDIT_A_REG0+i )->SetWindowText( "" );
			GetDlgItem( IDC_EDIT_A_REG0+i )->SetFocus();
			AfxMessageBox( "DDC参数有误!" );
			return;
		}
		// 数字和字母检查
		else
		{
			for ( j = 0; j < 4; j++ )
			{
				c = strParam.GetAt(j);
				if ( !( (c >= '0' && c <= '9') 
					|| (c >= 'a' && c <= 'f') 
					|| (c >= 'A' && c <= 'F') ) )
				{
					GetDlgItem( IDC_EDIT_A_REG0+i )->SetWindowText( "" );
					GetDlgItem( IDC_EDIT_A_REG0+i )->SetFocus();
					AfxMessageBox( "DDC参数有误!" );
					return;
				}
			}
		}
		// 检查通过，计算输入的参数值
		dwData = 0;
		for ( j = 0; j < 4; j++ )
		{
			c = strParam.GetAt(j);
			if ( c >= '0' && c <= '9' )
			{
				dwData += (c - '0') << (12-4*j);
			}
			else if ( c >= 'a' && c <= 'f' )
			{
				dwData += (c - 'a' + 10) << (12-4*j);
			}
			else if ( c >= 'A' && c <= 'F' )
			{
				dwData += (c - 'A' + 10) << (12-4*j);
			}
		}
		//
		pdwTemp[i] = dwData;
	}
}

void CParamDialog::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	
	UpdateData( TRUE );
	// 退出前保存现场
	int i;
	if ( m_pParent != NULL )
	{		
		m_pParent->m_nChanSel = m_nChanSel;
		m_pParent->m_nChanConfigCtrl = m_nChanConfigCtrl;
		m_pParent->m_nDataOutModelSel = m_nDataOutModelSel;
		m_pParent->m_nLvdsAck = m_nLvdsAck;
		m_pParent->m_nParaSerSel = m_nParaSerSel;
		m_pParent->m_nTest = m_nTest;
		m_pParent->m_nDepth = m_nDepth;
		m_pParent->m_nM0 = m_nM0;
		m_pParent->m_nStart = m_nStart;

		m_pParent->m_strAPath = m_strAPath;
		m_pParent->m_strBPath = m_strBPath;
		m_pParent->m_strCPath = m_strCPath;
		m_pParent->m_strDPath = m_strDPath;
		memcpy( m_pParent->m_dwaAParam, m_dwaAParam, DMA_SIZE*sizeof(DWORD) );
		memcpy( m_pParent->m_dwaBParam, m_dwaBParam, DMA_SIZE*sizeof(DWORD) );
		memcpy( m_pParent->m_dwaCParam, m_dwaCParam, DMA_SIZE*sizeof(DWORD) );
		memcpy( m_pParent->m_dwaDParam, m_dwaDParam, DMA_SIZE*sizeof(DWORD) );
		m_pParent->m_nSampFreq = m_nSampFreq;
		for (i=1; i<5; ++i)
		{
			m_pParent->m_nR[i] = m_nR[i];
		}
// 		m_pParent->m_nR1 = m_nR1;
// 		m_pParent->m_nR2 = m_nR2;
// 		m_pParent->m_nR3 = m_nR3;
// 		m_pParent->m_nR4 = m_nR4;
	}
	// 有些参数设置到doc
	CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)(m_pParent->GetDocument());
	if ( pDoc != NULL )
	{
		// 注意两者区别
		pDoc->m_nAlgDepth = m_nDepth*1024;
		// 查找显示视图
		CAdcTestPlatView* pTestPlatView = NULL;
		POSITION pos = pDoc->GetFirstViewPosition();
		while ( pos != NULL )
		{
			CView* pView = pDoc->GetNextView( pos );			
			if ( pView->IsKindOf(RUNTIME_CLASS(CAdcTestPlatView)) )
			{
				pTestPlatView = (CAdcTestPlatView*)pView;
				break;
			}
		}
		// 找到了，修改初始采样频率
		if ( pTestPlatView != NULL )
		{
			if ( m_nSampFreq > 0 
				&& m_nR[1] > 0 && m_nR[2] > 0 && m_nR[3] > 0 && m_nR[4] > 0
				&& m_nSampFreq / m_nR[1] > 0 && m_nSampFreq / m_nR[2] > 0
				&& m_nSampFreq / m_nR[3] > 0 && m_nSampFreq / m_nR[4] > 0 )
			{
				//pTestPlatView->m_FFTDisp.m_dOrgSampFreq = m_nSampFreq / m_nR1;
				for (i=0; i<5; ++i)
				{
					pTestPlatView->m_FFTDisp[i].m_dOrgSampFreq = m_nSampFreq / m_nR[i];
//					pTestPlatView->m_FFTDisp[i].ZoomRestore();

				}
// 				pTestPlatView->m_FFTDisp[1].m_dOrgSampFreq = m_nSampFreq / m_nR1;
// 				pTestPlatView->m_FFTDisp[2].m_dOrgSampFreq = m_nSampFreq / m_nR2;
// 				pTestPlatView->m_FFTDisp[3].m_dOrgSampFreq = m_nSampFreq / m_nR3;
// 				pTestPlatView->m_FFTDisp[4].m_dOrgSampFreq = m_nSampFreq / m_nR4;
				// 通过调用视图恢复同步变量
// 				pTestPlatView->m_FFTDisp[0].ZoomRestore();
// 				pTestPlatView->m_FFTDisp[1].ZoomRestore();
// 				pTestPlatView->m_FFTDisp[2].ZoomRestore();
// 				pTestPlatView->m_FFTDisp[3].ZoomRestore();
// 				pTestPlatView->m_FFTDisp[4].ZoomRestore();

			}
		}
	}

	CDialog::OnClose();
}

void CParamDialog::OnBtnSave() 
{
	// TODO: Add your control notification handler code here
	UpdateData( TRUE );
	// 界面输入的参数更新到缓冲区
	CheckData();
}

// 复位
void CParamDialog::OnBtnReset() 
{
	// TODO: Add your control notification handler code here
	DWORD dwCmd = (CMD_RESET << 16); 
	SendCommand( dwCmd );
}

// 回读
void CParamDialog::OnBtnReply() 
{
	
	if ( ((CAdcTestPlatApp*)AfxGetApp())->m_hDevice != NULL )
	{

		DWORD dwCmd;
		
		int iM0 = m_nM0;
		int iStart = m_nStart;
		m_nM0 = 0;
		m_nStart = 0;
		ChangeMode();

		// 现在采用的方式
		for ( int i = 0; i < 4; i++ )
		{
			ReadByChannel( i );
		}
		
		// 更新到界面		
		OnRadioChanSel2();
		OnRadioChanSel3();
		OnRadioChanSel4();
		OnRadioChanSel();
		UpdateData( FALSE );

		m_nM0 = iM0;
		m_nStart = iStart;
		ChangeMode();
	}
	
}

void CParamDialog::SendByChannel(BYTE byChannel)
{
	DWORD* pdwAddr = NULL;
	DWORD* pdwParam = NULL;
	DWORD dwCmd;

	switch ( byChannel )
	{
		case 0:
		{
			pdwAddr = m_dwaAAddr;
			pdwParam = m_dwaAParam;
			break;
		}
		case 1:
		{
			pdwAddr = m_dwaBAddr;
			pdwParam = m_dwaBParam;
			break;
		}
		case 2:
		{
			pdwAddr = m_dwaCAddr;
			pdwParam = m_dwaCParam;
			break;
		}
		case 3:
		{
			pdwAddr = m_dwaDAddr;
			pdwParam = m_dwaDParam;
			break;
		}
		default:
			break;
	}
	
	if ( pdwAddr != NULL && pdwParam != NULL )
	{
		// 地址
		DmaWrite( ((CAdcTestPlatApp*)AfxGetApp())->m_hDevice, 
			(BYTE*)pdwAddr, LOCAL_ADDR_SYN_ADDR, DMA_SIZE*4 );
		// 参数
		DmaWrite( ((CAdcTestPlatApp*)AfxGetApp())->m_hDevice, 
			(BYTE*)pdwParam, LOCAL_ADDR_SYN_PARAM, DMA_SIZE*4 );
		// 改变DDC配置寄存器
		dwCmd = (CMD_SET_CONFIG << 16) + 0;
		SendCommand( dwCmd );
	}
	
}

void CParamDialog::ReadByChannel(BYTE byChannel)
{
	DWORD* pdwAddr = NULL;
	DWORD* pdwParam = NULL;
	DWORD dwCmd;

	switch ( byChannel )
	{
		case 0:
		{
			pdwAddr = m_dwaAAddr;
			pdwParam = m_dwaAParam;
			break;
		}
		case 1:
		{
			pdwAddr = m_dwaBAddr;
			pdwParam = m_dwaBParam;
			break;
		}
		case 2:
		{
			pdwAddr = m_dwaCAddr;
			pdwParam = m_dwaCParam;
			break;
		}
		case 3:
		{
			pdwAddr = m_dwaDAddr;
			pdwParam = m_dwaDParam;
			break;
		}
		default:
			break;
	}
	
	if ( pdwAddr != NULL && pdwParam != NULL )
	{
		for (int j=0; j <4; ++j)
		{
			DmaWrite( ((CAdcTestPlatApp*)AfxGetApp())->m_hDevice, 
				(BYTE*)pdwAddr, LOCAL_ADDR_DEP_ADDR, DMA_SIZE*4 );
		}
		// 地址
		// 发送回读命令
		dwCmd = (CMD_GET_CONFIG << 16) + 0;
		SendCommand( dwCmd );		

		IoRead(0, &dwCmd);

		// DMA读取参数
		memset( m_dwaAllAddrParam, 0, DMA_SIZE*4 );
		DmaRead( ((CAdcTestPlatApp*)AfxGetApp())->m_hDevice,
			(BYTE*)m_dwaAllAddrParam, LOCAL_ADDR_DMA, DMA_SIZE*4*4 );
		
		// 数据为16位		
		for ( int i = 0; i < ADDR_PARAM_SIZE; i++ )
		{
			pdwParam[i] = *( (WORD*)m_dwaAllAddrParam + i );			
		}
	}
}

void CParamDialog::OnChangeEditR() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
	UpdateData( TRUE );
	// 根据通道设置不同的r值

	m_nR[m_nChanSel+1] = atoi( m_strR );
	int i;
	if (m_nChanConfigCtrl = 1)
	{
		for (i=1; i<5; ++i)
		{
			m_nR[i] = atoi( m_strR );
		}
	}
	
	CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)((CMainFrame*) AfxGetMainWnd())->GetActiveDocument();
	//	CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)GetDocument();

	for (i=1; i<5; ++i)
	{
		pDoc->m_nR[i]=m_nR[i];
	}


}
