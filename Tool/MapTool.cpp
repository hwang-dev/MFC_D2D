// MapTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "MapTool.h"
#include "afxdialogex.h"

#include "MainFrm.h"
#include "ToolView.h"
#include "Terrain.h"

// CMapTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMapTool, CDialog)

CMapTool::CMapTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MAPTOOL, pParent), m_iDrawID(0), m_pImage(nullptr)
	, m_strTileNum(_T(""))
	, m_byCursorIndex(0)
	, m_byCursorDrawID(0)
	, m_byTileOption(0)
	, m_byCursorRoomNum(0)
	, m_byTileRoomNum(0)
	, m_iTileX(0)
	, m_iTileY(0)
	, m_strStageName(_T(""))
{

}

CMapTool::~CMapTool()
{
	Release();
}

void CMapTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_TileBox);
	DDX_Control(pDX, IDC_PICTURE, m_PictureCtrl);
	DDX_Control(pDX, IDC_CHECK1, m_CheckMove);
	DDX_Text(pDX, IDC_EDIT1, m_strTileNum);
	DDX_Text(pDX, IDC_EDIT3, m_byCursorIndex);
	DDX_Text(pDX, IDC_EDIT4, m_byCursorDrawID);
	DDX_Text(pDX, IDC_EDIT6, m_byTileOption);
	DDX_Text(pDX, IDC_EDIT5, m_byCursorRoomNum);
	DDX_Text(pDX, IDC_EDIT2, m_byTileRoomNum);
	DDX_Text(pDX, IDC_EDIT7, m_iTileX);
	DDX_Text(pDX, IDC_EDIT9, m_iTileY);
	DDX_Control(pDX, IDC_LIST3, m_StageListBox);
	DDX_Text(pDX, IDC_EDIT10, m_strStageName);
}


BEGIN_MESSAGE_MAP(CMapTool, CDialog)

	ON_WM_DROPFILES()
	ON_LBN_SELCHANGE(IDC_LIST1, &CMapTool::OnLbnSelectTileBox)
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(IDC_BUTTON1, &CMapTool::OnBnClickedSaveTile)
	ON_BN_CLICKED(IDC_BUTTON2, &CMapTool::OnBnClickedLoadTile)
	ON_BN_CLICKED(IDC_BUTTON3, &CMapTool::OnBnClickedTileListSave)
	ON_BN_CLICKED(IDC_BUTTON4, &CMapTool::OnBnClickedTileListLoad)
	ON_EN_CHANGE(IDC_EDIT1, &CMapTool::OnEnChangeFindTileNum)
	ON_EN_CHANGE(IDC_EDIT2, &CMapTool::OnEnChangeRoomNumber)
	ON_BN_CLICKED(IDC_BUTTON9, &CMapTool::OnBnClickedMapSet)
END_MESSAGE_MAP()


// CMapTool 메시지 처리기입니다.


void CMapTool::Release()
{
	if (m_pImage)
	{
		m_pImage->Destroy();

		delete m_pImage;
		m_pImage = nullptr;
	}
}

void CMapTool::TileListLoad()
{
	// 리스트 박스 자동 로드
	HANDLE hFile = CreateFile(L"../Data/TileList.dat", GENERIC_READ, 0, 0,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		AfxMessageBox(L"TileList Load Failed!!");
		/*return;*/
	}

	int i = 0;

	DWORD dwByte = 0;
	TCHAR* pKey = L"";
	TCHAR* pPath = L"";
	int iLength = 0;

	while (true)
	{
		ReadFile(hFile, &iLength, sizeof(int), &dwByte, nullptr);
		pKey = new TCHAR[iLength];
		ReadFile(hFile, pKey, sizeof(TCHAR) * iLength, &dwByte, nullptr);

		ReadFile(hFile, &iLength, sizeof(int), &dwByte, nullptr);
		pPath = new TCHAR[iLength];
		ReadFile(hFile, pPath, sizeof(TCHAR) * iLength, &dwByte, nullptr);

		if (dwByte == 0)
		{
			delete pKey;
			pKey = nullptr;

			delete pPath;
			pPath = nullptr;

			break;
		}

		m_mapTilePath.insert({ pKey, pPath });
		m_TileBox.AddString(pKey);
	}
}

BOOL CMapTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	// 기본적으로 이동가능
	m_CheckMove.SetCheck(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CMapTool::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialog::OnDropFiles(hDropInfo);

	UpdateData(TRUE);

	//m_TileBox.ResetContent();
	TCHAR szFilePath[MAX_STR] = L"";

	int iFileCnt = DragQueryFile(hDropInfo, -1, nullptr, 0);
	TCHAR szFileName[MAX_STR] = L"";

	for (int i = 0; i < iFileCnt; ++i)
	{
		DragQueryFile(hDropInfo, i, szFilePath, MAX_STR);

		CString strRelativePath = CFileInfo::ConvertRelativePath(szFilePath);

		CString strFileName = PathFindFileName(strRelativePath.GetString());

		lstrcpy(szFileName, strFileName.GetString());	// 상대 경로
		PathRemoveExtension(szFileName);	// 파일명

		strFileName = szFileName;

		auto iter_find = m_mapTilePath.find(strFileName);

		if (m_mapTilePath.end() == iter_find)
		{
			m_mapTilePath.insert({ strFileName, strRelativePath });
			m_TileBox.AddString(szFileName);
		}
	}

	// 맵에 이미지 이름, 상대 경로 저장


	UpdateData(FALSE);
}


void CMapTool::OnLbnSelectTileBox()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	int iSelect = m_TileBox.GetCurSel();

	if (LB_ERR == iSelect)
		return;

	CString strSelectName;
	m_TileBox.GetText(iSelect, strSelectName);


	// 이미지 띄우기
	auto& iter_find = m_mapTilePath.find(strSelectName);

	if (m_pImage)
	{
		m_pImage->Destroy();
		delete m_pImage;
		m_pImage = nullptr;
	}

	m_pImage = new CImage;
	m_pImage->Load(iter_find->second);
	m_PictureCtrl.SetBitmap(*m_pImage);

	// DrawID 변경
	int i = 0;

	for (; i < strSelectName.GetLength(); ++i)
	{
		if (0 != isdigit(strSelectName[i]))
			break;
	}

	strSelectName.Delete(0, i);
	m_iDrawID = _tstoi(strSelectName);

	UpdateData(FALSE);
}


void CMapTool::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (nID == SC_CLOSE)
	{
		CMainFrame* pMainFrame = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
		CToolView*	pMainView = dynamic_cast<CToolView*>(pMainFrame->m_MainSplit.GetPane(0, 1));

		pMainView->m_bIsMapTool = false;
	}

	CDialog::OnSysCommand(nID, lParam);
}


void CMapTool::OnBnClickedSaveTile()
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
			AfxMessageBox(L"Tile Save Failed!!");
			return;
		}

		vector<TILE*>& vecTile = CTerrain::GetInstance()->GetVecTile();

		DWORD dwByte = 0;

		for (auto& pTile : vecTile)
			WriteFile(hFile, pTile, sizeof(TILE), &dwByte, nullptr);

		CloseHandle(hFile);
	}

	UpdateData(FALSE);
}


void CMapTool::OnBnClickedLoadTile()
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
			AfxMessageBox(L"Tile Load Failed!!");
			return;
		}

		CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
		CToolView* pMainView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplit.GetPane(0, 1));
		

		CTerrain::GetInstance()->Release();
		vector<TILE*>& vecTile = CTerrain::GetInstance()->GetVecTile();

		TILE tTile = {};
		DWORD dwByte = 0;

		while (true)
		{
			ReadFile(hFile, &tTile, sizeof(TILE), &dwByte, nullptr);

			if (0 == dwByte)
				break;

			TILE* pTile = new TILE(tTile);
			vecTile.push_back(pTile);
		}

		CloseHandle(hFile);
		pMainView->Invalidate(FALSE);
	}

	UpdateData(FALSE);
}


void CMapTool::OnBnClickedTileListSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
		CString strGetPath = Dlg.GetPathName();
		const TCHAR* pGetPath = strGetPath.GetString();

		HANDLE hFile = CreateFile(pGetPath, GENERIC_WRITE, 0, 0,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

		if (INVALID_HANDLE_VALUE == hFile)
		{
			AfxMessageBox(L"TileList Save Failed!!");
			return;
		}

		DWORD dwByte = 0;

		for (auto& MyPair : m_mapTilePath)
		{
			const TCHAR* pKey = MyPair.first.GetString();
			int iKeyLength = MyPair.first.GetLength() + 1;
			const TCHAR* pPath = MyPair.second.GetString();
			int iPathLength = MyPair.second.GetLength() + 1;


			WriteFile(hFile, &iKeyLength, sizeof(int), &dwByte, nullptr);
			WriteFile(hFile, pKey, sizeof(TCHAR) * iKeyLength, &dwByte, nullptr);
			WriteFile(hFile, &iPathLength, sizeof(int), &dwByte, nullptr);
			WriteFile(hFile, pPath, sizeof(TCHAR) * iPathLength, &dwByte, nullptr);
		}

		CloseHandle(hFile);
	}

	AfxMessageBox(L"TileList Save Success");
	UpdateData(FALSE);
}


void CMapTool::OnBnClickedTileListLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 타일 리스트 불러오기
	TileListLoad();
}


void CMapTool::OnEnChangeFindTileNum()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	// Tile + 입력된 Num

	CString strTile = L"Tile" + m_strTileNum;

	auto& iter_find = m_mapTilePath.find(strTile);

	// 없으면 종료
	if (iter_find == m_mapTilePath.end())
		return;

	// 있으면 검색
	int iFindIndex = m_TileBox.FindString(0, strTile);

	// 탐색에 실패하면
	if (iFindIndex == LB_ERR)
		return;

	m_TileBox.SetCurSel(iFindIndex);

	// DrawID 변경
	m_iDrawID = _wtoi(m_strTileNum);

	// 이미지 변경
	if (m_pImage)
	{
		m_pImage->Destroy();
		delete m_pImage;
		m_pImage = nullptr;
	}

	m_pImage = new CImage;
	m_pImage->Load(iter_find->second);
	m_PictureCtrl.SetBitmap(*m_pImage);

	UpdateData(FALSE);
}



void CMapTool::OnEnChangeRoomNumber()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);


	UpdateData(FALSE);
}


void CMapTool::OnBnClickedMapSet()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	//m_StageListBox.AddString(m_strStageName);

	UpdateData(FALSE);
}
