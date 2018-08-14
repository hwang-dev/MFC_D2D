// MyForm.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "MyForm.h"

#include "MainFrm.h"
#include "ToolView.h"

// CMyForm

IMPLEMENT_DYNCREATE(CMyForm, CFormView)

CMyForm::CMyForm()
	: CFormView(IDD_MYFORM)
{

}

CMyForm::~CMyForm()
{
}

void CMyForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMyForm, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CMyForm::OnBnClickedMapTool)
	ON_BN_CLICKED(IDC_BUTTON7, &CMyForm::OnBnClickedFilePath)
	ON_BN_CLICKED(IDC_BUTTON5, &CMyForm::OnBnClickedSubTileTool)
	ON_BN_CLICKED(IDC_BUTTON2, &CMyForm::OnBnClickedMonsterTool)
	ON_BN_CLICKED(IDC_BUTTON3, &CMyForm::OnBnClickedObjectTool)
	ON_BN_CLICKED(IDC_BUTTON4, &CMyForm::OnBnClickedTriggerTool)
	ON_BN_CLICKED(IDC_BUTTON6, &CMyForm::OnBnClickedBossTool)
END_MESSAGE_MAP()


// CMyForm 진단입니다.

#ifdef _DEBUG
void CMyForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMyForm 메시지 처리기입니다.


void CMyForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	m_Font.CreatePointFont(100, L"Consolas");

	GetDlgItem(IDC_BUTTON1)->SetFont(&m_Font);
	GetDlgItem(IDC_BUTTON2)->SetFont(&m_Font);
	GetDlgItem(IDC_BUTTON3)->SetFont(&m_Font);
	GetDlgItem(IDC_BUTTON4)->SetFont(&m_Font);
	GetDlgItem(IDC_BUTTON5)->SetFont(&m_Font);
	GetDlgItem(IDC_BUTTON6)->SetFont(&m_Font);
	GetDlgItem(IDC_BUTTON7)->SetFont(&m_Font);

}


void CMyForm::OnBnClickedMapTool()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CMainFrame* pMainFrame = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CToolView*	pMainView = dynamic_cast<CToolView*>(pMainFrame->m_MainSplit.GetPane(0, 1));

	if (m_MapTool.GetSafeHwnd() == nullptr)
		m_MapTool.Create(IDD_MAPTOOL);

	pMainView->m_bIsMapTool = true;
	m_MapTool.ShowWindow(SW_SHOW);
}




void CMyForm::OnBnClickedFilePath()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (m_FilePath.GetSafeHwnd() == nullptr)
		m_FilePath.Create(IDD_FILEPATH);

	m_FilePath.ShowWindow(SW_SHOW);
}


void CMyForm::OnBnClickedSubTileTool()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CMainFrame* pMainFrame = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CToolView*	pMainView = dynamic_cast<CToolView*>(pMainFrame->m_MainSplit.GetPane(0, 1));

	if (m_SubTileTool.GetSafeHwnd() == nullptr)
		m_SubTileTool.Create(IDD_SUBTILETOOL);

	pMainView->m_bOnSubTileTool = true;
	m_SubTileTool.ShowWindow(SW_SHOW);
	
}


void CMyForm::OnBnClickedMonsterTool()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CMainFrame* pMainFrame = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CToolView*	pMainView = dynamic_cast<CToolView*>(pMainFrame->m_MainSplit.GetPane(0, 1));

	if (m_MonsterTool.GetSafeHwnd() == nullptr)
		m_MonsterTool.Create(IDD_MONSTERTOOL);

	pMainView->m_bOnMonsterTool = true;
	m_MonsterTool.ShowWindow(SW_SHOW);
}


void CMyForm::OnBnClickedObjectTool()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CMainFrame* pMainFrame = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CToolView*	pMainView = dynamic_cast<CToolView*>(pMainFrame->m_MainSplit.GetPane(0, 1));

	if (m_ObjectTool.GetSafeHwnd() == nullptr)
		m_ObjectTool.Create(IDD_OBJECTTOOL);

	pMainView->m_bOnObjectTool = true;
	m_ObjectTool.ShowWindow(SW_SHOW);
}


void CMyForm::OnBnClickedTriggerTool()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CMainFrame* pMainFrame = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CToolView*	pMainView = dynamic_cast<CToolView*>(pMainFrame->m_MainSplit.GetPane(0, 1));

	if (m_TriggerTool.GetSafeHwnd() == nullptr)
		m_TriggerTool.Create(IDD_TRIGGERTOOL);

	pMainView->m_bOnTriggerTool = true;
	m_TriggerTool.ShowWindow(SW_SHOW);
}


void CMyForm::OnBnClickedBossTool()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CMainFrame* pMainFrame = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CToolView*	pMainView = dynamic_cast<CToolView*>(pMainFrame->m_MainSplit.GetPane(0, 1));

	if (m_BossTool.GetSafeHwnd() == nullptr)
		m_BossTool.Create(IDD_BOSSTOOL);

	pMainView->m_bOnBossTool = true;
	m_BossTool.ShowWindow(SW_SHOW);
}
