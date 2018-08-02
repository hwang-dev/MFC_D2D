// MonsterTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "MonsterTool.h"
#include "afxdialogex.h"

#include "MainFrm.h"
#include "ToolView.h"
// CMonsterTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMonsterTool, CDialog)

CMonsterTool::CMonsterTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MONSTERTOOL, pParent)
	, m_fAttSpd(0)
	, m_fBulletSpd(0)
{

}

CMonsterTool::~CMonsterTool()
{
}

void CMonsterTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RADIO1, m_RadioType[0]);
	DDX_Control(pDX, IDC_RADIO2, m_RadioType[1]);
	DDX_Control(pDX, IDC_RADIO3, m_RadioType[2]);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	DDX_Control(pDX, IDC_LIST2, m_SetBox);
	DDX_Text(pDX, IDC_EDIT1, m_fAttSpd);
	DDX_Text(pDX, IDC_EDIT8, m_fBulletSpd);
}


BEGIN_MESSAGE_MAP(CMonsterTool, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CMonsterTool::OnBnClickedSetBtn)
	ON_WM_SYSCOMMAND()
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


// CMonsterTool 메시지 처리기입니다.

BOOL CMonsterTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	// 라디오 초기화
	m_RadioType[0].SetCheck(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CMonsterTool::Release()
{
}

void CMonsterTool::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (nID == SC_CLOSE)
	{
		CMainFrame* pMainFrame = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
		CToolView*	pMainView = dynamic_cast<CToolView*>(pMainFrame->m_MainSplit.GetPane(0, 1));

		pMainView->m_bOnMonsterTool = false;
	}

	CDialog::OnSysCommand(nID, lParam);
}


void CMonsterTool::OnBnClickedSetBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMonsterTool::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialog::OnDropFiles(hDropInfo);
}


