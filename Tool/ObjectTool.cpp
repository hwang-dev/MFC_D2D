// ObjectTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "ObjectTool.h"
#include "afxdialogex.h"

#include "MainFrm.h"
#include "ToolView.h"

// CObjectTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(CObjectTool, CDialog)

CObjectTool::CObjectTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_OBJECTTOOL, pParent)
{

}

CObjectTool::~CObjectTool()
{
}

void CObjectTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CObjectTool, CDialog)
	ON_BN_CLICKED(IDC_BUTTON2, &CObjectTool::OnBnClickedClear)
	ON_BN_CLICKED(IDC_BUTTON5, &CObjectTool::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &CObjectTool::OnBnClickedSave)
	ON_BN_CLICKED(IDC_BUTTON8, &CObjectTool::OnBnClickedLoad)
	ON_WM_SYSCOMMAND()
END_MESSAGE_MAP()


// CObjectTool 메시지 처리기입니다.


void CObjectTool::OnBnClickedClear()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CToolView* pMainView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplit.GetPane(0, 1));

	CBox::GetInstance()->Release();
	pMainView->Invalidate(FALSE);

	UpdateData(FALSE);
}


void CObjectTool::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CToolView* pMainView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplit.GetPane(0, 1));

	if (CBox::GetInstance()->GetVecBox().empty() == false)
	{
		CBox::GetInstance()->GetVecBox().pop_back();
		pMainView->Invalidate(FALSE);
	}

	UpdateData(FALSE);
}


void CObjectTool::OnBnClickedSave()
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
			AfxMessageBox(L"Box Save Failed!!");
			return;
		}

		vector<INFO*>& vecBox = CBox::GetInstance()->GetVecBox();

		DWORD dwByte = 0;

		for (auto& pInfo : vecBox) {
			WriteFile(hFile, pInfo, sizeof(INFO), &dwByte, nullptr);
		}

		AfxMessageBox(L"Box Save Success");
		CloseHandle(hFile);
	}

	UpdateData(FALSE);
}


void CObjectTool::OnBnClickedLoad()
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
			AfxMessageBox(L"Box Load Failed!!");
			return;
		}

		CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
		CToolView* pMainView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplit.GetPane(0, 1));

		/* 초기화 */
		CBox::GetInstance()->Release();
		vector<INFO*>& vecBox = CBox::GetInstance()->GetVecBox();

		INFO tInfo = {};
		DWORD dwByte = 0;

		while (true)
		{
			ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);

			if (0 == dwByte)
			{
				AfxMessageBox(L"Box Load Success!!");
				break;
			}

			INFO* pInfo = new INFO(tInfo);
			vecBox.push_back(pInfo);
		}

		CloseHandle(hFile);
		pMainView->Invalidate(FALSE);
	}

	UpdateData(FALSE);
	
}


void CObjectTool::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (nID == SC_CLOSE) {
		CMainFrame* pMainFrame = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
		CToolView* pMainView = dynamic_cast<CToolView*>(pMainFrame->m_MainSplit.GetPane(0, 1));

		pMainView->m_bOnObjectTool = false;
	}

	CDialog::OnSysCommand(nID, lParam);
}
