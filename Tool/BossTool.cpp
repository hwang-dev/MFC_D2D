// BossTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "BossTool.h"
#include "afxdialogex.h"

#include "MainFrm.h"
#include "ToolView.h"


// CBossTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(CBossTool, CDialog)

CBossTool::CBossTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_BOSSTOOL, pParent)
	, m_byRoom(0)
{

}

CBossTool::~CBossTool()
{
}

void CBossTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_byRoom);
}


BEGIN_MESSAGE_MAP(CBossTool, CDialog)
	ON_EN_CHANGE(IDC_EDIT1, &CBossTool::OnEnChangeRoom)
	ON_BN_CLICKED(IDC_BUTTON1, &CBossTool::OnBnClickedClear)
	ON_BN_CLICKED(IDC_BUTTON1, &CBossTool::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON8, &CBossTool::OnBnClickedClear)
	ON_BN_CLICKED(IDC_BUTTON11, &CBossTool::OnBnClickedLoad)
	ON_BN_CLICKED(IDC_BUTTON12, &CBossTool::OnBnClickedSave)
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(IDC_BUTTON3, &CBossTool::OnBnClickedCancel)
END_MESSAGE_MAP()


// CBossTool 메시지 처리기입니다.


void CBossTool::OnEnChangeRoom()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);
	UpdateData(FALSE);
}






void CBossTool::OnBnClickedClear()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CToolView* pMainView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplit.GetPane(0, 1));

	CDark::GetInstance()->Release();
	pMainView->Invalidate(FALSE);

	UpdateData(FALSE);
}


void CBossTool::OnBnClickedLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	CFileDialog Dlg(TRUE, L"dat", L"*.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Data Files(*.dat)|*.dat||", this);

	TCHAR szPath[MAX_STR] = L"";

	GetCurrentDirectory(MAX_STR, szPath);
	PathRemoveFileSpec(szPath);
	lstrcat(szPath, L"\\Data");

	Dlg.m_ofn.lpstrInitialDir = szPath;

	if (IDOK == Dlg.DoModal())
	{
		HANDLE hFile = CreateFile(Dlg.GetPathName().GetString(), GENERIC_READ, 0, 0,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

		if (INVALID_HANDLE_VALUE == hFile)
		{
			AfxMessageBox(L"Dark Load Failed!!");
			return;
		}

		CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
		CToolView* pMainView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplit.GetPane(0, 1));

		/* 초기화 */
		CDark::GetInstance()->Release();
		vector<INFO*>& vecDark = CDark::GetInstance()->GetvecDark();

		INFO tInfo = {};
		DWORD dwByte = 0;

		while (true)
		{
			ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);

			if (0 == dwByte)
			{
				AfxMessageBox(L"Dark Load Success!!");
				break;
			}

			INFO* pInfo = new INFO(tInfo);
			vecDark.push_back(pInfo);
		}

		CloseHandle(hFile);
		pMainView->Invalidate(FALSE);
	}

	UpdateData(FALSE);
}


void CBossTool::OnBnClickedSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	CFileDialog Dlg(FALSE, L"dat", L"*.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Data Files(*.dat)|*.dat||", this);

	TCHAR szPath[MAX_STR] = L"";

	GetCurrentDirectory(MAX_STR, szPath);
	CFileInfo::ConvertRelativePath(szPath);
	PathRemoveFileSpec(szPath);
	lstrcat(szPath, L"\\Data");

	Dlg.m_ofn.lpstrInitialDir = szPath;

	if (IDOK == Dlg.DoModal())
	{
		HANDLE hFile = CreateFile(Dlg.GetPathName().GetString(), GENERIC_WRITE, 0, 0,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

		if (INVALID_HANDLE_VALUE == hFile)
		{
			AfxMessageBox(L"Dark Save Failed!!");
			return;
		}

		vector<INFO*>& vecDark = CDark::GetInstance()->GetvecDark();

		DWORD dwByte = 0;

		for (auto& pInfo : vecDark)
			WriteFile(hFile, pInfo, sizeof(INFO), &dwByte, nullptr);
		CloseHandle(hFile);
	}

	AfxMessageBox(L"Dark Save Success");
	UpdateData(FALSE);
}


void CBossTool::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (nID == SC_CLOSE) {
		CMainFrame* pMainFrame = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
		CToolView*	pMainView = dynamic_cast<CToolView*>(pMainFrame->m_MainSplit.GetPane(0, 1));

		pMainView->m_bOnBossTool = false;
	}

	CDialog::OnSysCommand(nID, lParam);
}


void CBossTool::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CToolView* pMainView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplit.GetPane(0, 1));

	if (CDark::GetInstance()->GetvecDark().empty() == false)
	{
		CDark::GetInstance()->GetvecDark().pop_back();
		pMainView->Invalidate(FALSE);
	}

	UpdateData(FALSE);
}
