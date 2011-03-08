// TestResultView1.cpp : implementation file
//

#include "stdafx.h"
#include "adctestplat.h"
#include "TestResultView1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestResultView


IMPLEMENT_DYNCREATE(CTestResultView, CFormView)

CTestResultView::CTestResultView()
	: CFormView(CTestResultView::IDD)
{
	//{{AFX_DATA_INIT(CTestResultView)
	m_strTestResult = _T("");
	//}}AFX_DATA_INIT
}

CTestResultView::~CTestResultView()
{
}

void CTestResultView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestResultView)
	DDX_Control(pDX, IDC_EDIT_TEST_RESULT, m_edtTestResult);
	DDX_Text(pDX, IDC_EDIT_TEST_RESULT, m_strTestResult);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestResultView, CFormView)
	//{{AFX_MSG_MAP(CTestResultView)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestResultView diagnostics

#ifdef _DEBUG
void CTestResultView::AssertValid() const
{
	CFormView::AssertValid();
}

void CTestResultView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestResultView message handlers

void CTestResultView::OnDraw(CDC* pDC) 
{	
	DrawResult();	
}

void CTestResultView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if ( cx > 0 && cy > 0 )
	{
		CRect rc( 0, 0, cx, cy );
		if ( m_edtTestResult )
		{
			m_edtTestResult.MoveWindow( &rc );
		}
	}
}

void CTestResultView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	CSize sizeTotal;	
	sizeTotal.cx = sizeTotal.cy = 10;
	SetScrollSizes(MM_TEXT, sizeTotal);

//	((CEdit*)GetDlgItem( IDC_EDIT_TEST_RESULT ))->SetSel( -1, 0, TRUE );
}

void CTestResultView::DrawResult()
{
	CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)GetDocument();	
	CString strTemp;
	CSize szText;
	int nCount;	
	nCount = 1;
	strTemp.Empty();
	m_strTestResult.Empty();	
	
	m_strTestResult += "\t���Խ��:\r\n";
	
	// ����doc����������״̬��ʾ
	if ( pDoc != NULL )
	{
		// �������ô���ѡ��Ĳ�����Ŀ����ʾ���Խ��
		switch ( pDoc->m_nTestModeSel )
		{
			case 0:
			{
				strTemp.Format( "\t\r\n%d. ����������\r\n\tAͨ��: %.2fdB\r\n\tBͨ��: %.2fdB\r\n\tCͨ��: %.2fdB\r\n\tDͨ��: %.2fdB\r\n ", 
				nCount++, \
				((CAdcTestPlatDoc*)pDoc)->m_daResultBackNoise[0], \
				((CAdcTestPlatDoc*)pDoc)->m_daResultBackNoise[1], \
				((CAdcTestPlatDoc*)pDoc)->m_daResultBackNoise[2], \
				((CAdcTestPlatDoc*)pDoc)->m_daResultBackNoise[3] );
				m_strTestResult += strTemp;
				break;
			}
			case 1:
			case 6:
			{
				strTemp.Format( "\t\r\n%d. SNR����\r\n\tAͨ��: %.2fdB\r\n\tBͨ��: %.2fdB\r\n\tCͨ��: %.2fdB\r\n\tDͨ��: %.2fdB\r\n ", 
				nCount++, \
				((CAdcTestPlatDoc*)pDoc)->m_daResultSNR[0], \
				((CAdcTestPlatDoc*)pDoc)->m_daResultSNR[1], \
				((CAdcTestPlatDoc*)pDoc)->m_daResultSNR[2], \
				((CAdcTestPlatDoc*)pDoc)->m_daResultSNR[3] );
				m_strTestResult += strTemp;

				strTemp.Format( "\t\r\n%d. SINAD����\r\n\tAͨ��: %.2fdB\r\n\tBͨ��: %.2fdB\r\n\tCͨ��: %.2fdB\r\n\tDͨ��: %.2fdB\r\n ", 
				nCount++, \
				((CAdcTestPlatDoc*)pDoc)->m_daResultSINAD[0], \
				((CAdcTestPlatDoc*)pDoc)->m_daResultSINAD[1], \
				((CAdcTestPlatDoc*)pDoc)->m_daResultSINAD[2], \
				((CAdcTestPlatDoc*)pDoc)->m_daResultSINAD[3] );
				m_strTestResult += strTemp;

				strTemp.Format( "\t\r\n%d. SFDR����\r\n\tAͨ��: %.2fdB\r\n\tBͨ��: %.2fdB\r\n\tCͨ��: %.2fdB\r\n\tDͨ��: %.2fdB\r\n ", 
				nCount++, \
				((CAdcTestPlatDoc*)pDoc)->m_daResultSFDR[0], \
				((CAdcTestPlatDoc*)pDoc)->m_daResultSFDR[1], \
				((CAdcTestPlatDoc*)pDoc)->m_daResultSFDR[2], \
				((CAdcTestPlatDoc*)pDoc)->m_daResultSFDR[3] );
				m_strTestResult += strTemp;
				
				strTemp.Format( "\t\r\n%d. ENOB����\r\n\tAͨ��: %.2f\r\n\tBͨ��: %.2f\r\n\tCͨ��: %.2f\r\n\tDͨ��: %.2f\r\n ", 
				nCount++, \
				((CAdcTestPlatDoc*)pDoc)->m_daResultENOB[0], \
				((CAdcTestPlatDoc*)pDoc)->m_daResultENOB[1], \
				((CAdcTestPlatDoc*)pDoc)->m_daResultENOB[2], \
				((CAdcTestPlatDoc*)pDoc)->m_daResultENOB[3] );
				m_strTestResult += strTemp;
				
				break;
			}
			case 2:
			{
				strTemp.Format( "\t\r\n%d. Aͨ����������\r\n\tAͨ��: %.2fdB\r\n\tBͨ��: %.2fdB\r\n\tCͨ��: %.2fdB\r\n\tDͨ��: %.2fdB\r\n ", 
				nCount++, \
				((CAdcTestPlatDoc*)pDoc)->m_daResultChanDisturbA[0], \
				((CAdcTestPlatDoc*)pDoc)->m_daResultChanDisturbA[1], \
				((CAdcTestPlatDoc*)pDoc)->m_daResultChanDisturbA[2], \
				((CAdcTestPlatDoc*)pDoc)->m_daResultChanDisturbA[3] );
				m_strTestResult += strTemp;
				break;
			}
			case 3:
			{
				strTemp.Format( "\t\r\n%d. Bͨ����������\r\n\tAͨ��: %.2fdB\r\n\tBͨ��: %.2fdB\r\n\tCͨ��: %.2fdB\r\n\tDͨ��: %.2fdB\r\n ", 
				nCount++, \
				((CAdcTestPlatDoc*)pDoc)->m_daResultChanDisturbB[0], \
				((CAdcTestPlatDoc*)pDoc)->m_daResultChanDisturbB[1], \
				((CAdcTestPlatDoc*)pDoc)->m_daResultChanDisturbB[2], \
				((CAdcTestPlatDoc*)pDoc)->m_daResultChanDisturbB[3] );
				m_strTestResult += strTemp;
				break;
			}
			case 4:
			{
				strTemp.Format( "\t\r\n%d. Cͨ����������\r\n\tAͨ��: %.2fdB\r\n\tBͨ��: %.2fdB\r\n\tCͨ��: %.2fdB\r\n\tDͨ��: %.2fdB\r\n ", 
				nCount++, \
				((CAdcTestPlatDoc*)pDoc)->m_daResultChanDisturbC[0], \
				((CAdcTestPlatDoc*)pDoc)->m_daResultChanDisturbC[1], \
				((CAdcTestPlatDoc*)pDoc)->m_daResultChanDisturbC[2], \
				((CAdcTestPlatDoc*)pDoc)->m_daResultChanDisturbC[3] );
				m_strTestResult += strTemp;
				break;
			}
			case 5:
			{
				strTemp.Format( "\t\r\n%d. Dͨ����������\r\n\tAͨ��: %.2fdB\r\n\tBͨ��: %.2fdB\r\n\tCͨ��: %.2fdB\r\n\tDͨ��: %.2fdB\r\n ", 
				nCount++, \
				((CAdcTestPlatDoc*)pDoc)->m_daResultChanDisturbD[0], \
				((CAdcTestPlatDoc*)pDoc)->m_daResultChanDisturbD[1], \
				((CAdcTestPlatDoc*)pDoc)->m_daResultChanDisturbD[2], \
				((CAdcTestPlatDoc*)pDoc)->m_daResultChanDisturbD[3] );
				m_strTestResult += strTemp;
				break;
			}
			default:
				break;
		}
		
		UpdateData( FALSE );
	}	
}

void CTestResultView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	DrawResult();	
}
