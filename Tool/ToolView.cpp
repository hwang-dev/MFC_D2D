
// ToolView.cpp : CToolView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Tool.h"
#endif

#include "MainFrm.h"
#include "ToolDoc.h"
#include "ToolView.h"

#include "MiniView.h"
#include "Terrain.h"
#include "MyForm.h"
#include "MapTool.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HWND g_hWnd;

// CToolView

IMPLEMENT_DYNCREATE(CToolView, CScrollView)

BEGIN_MESSAGE_MAP(CToolView, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CToolView 생성/소멸

CToolView::CToolView()
	: m_bIsMapTool(false)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CToolView::~CToolView()
{
	CSubTile::GetInstance()->DestroyInstance();
	CTerrain::GetInstance()->DestroyInstance();

	CTextureMgr::GetInstance()->DestroyInstance();
	CDevice::GetInstance()->DestroyInstance();
}

BOOL CToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CToolView 그리기

void CToolView::OnDraw(CDC* /*pDC*/)
{
	CToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CDevice::GetInstance()->Render_Begin();

	
	CTerrain::GetInstance()->Render();
	CSubTile::GetInstance()->Render();
	
	CDevice::GetInstance()->Render_End();

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CToolView 인쇄

BOOL CToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CToolView 진단

#ifdef _DEBUG
void CToolView::AssertValid() const
{
	CView::AssertValid();
}

void CToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CToolDoc* CToolView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToolDoc)));
	return (CToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CToolView 메시지 처리기


void CToolView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	// 스크롤 바 추가
	SetScrollSizes(MM_TEXT, CSize(TILECX * TILEX_NORMAL, TILECY * TILEX_NORMAL));

	g_hWnd = m_hWnd;

	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetMainWnd());

	RECT rcMainWnd = {};
	pMainFrm->GetWindowRect(&rcMainWnd);

	SetRect(&rcMainWnd, 0, 0, rcMainWnd.right - rcMainWnd.left, rcMainWnd.bottom - rcMainWnd.top);

	RECT rcView = {};

	GetClientRect(&rcView);

	int iRowFrm = rcMainWnd.right - rcView.right;
	int iColFrm = rcMainWnd.bottom - rcView.bottom;

	pMainFrm->SetWindowPos(nullptr, 0, 0, WINCX + iRowFrm, WINCY + iColFrm, SWP_NOZORDER);

	if (FAILED(CDevice::GetInstance()->InitDevice()))
	{
		AfxMessageBox(L"Device Init Failed!!!");
		return;
	}

	// 터레인 초기화
	CTerrain::GetInstance()->Initialize();
	CTerrain::GetInstance()->SetMainView(this);

	// 서브 타일 초기화
	CSubTile::GetInstance()->Initialize();
	CSubTile::GetInstance()->SetMainView(this);
}


void CToolView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.


	UpdateData(TRUE);

	// 미니뷰를 갱신
	//CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CMyForm* pMyForm = dynamic_cast<CMyForm*>(pMainFrm->m_SecondSplit.GetPane(1, 0));

	// 마우스에 스크롤값 추가
	point.x += GetScrollPos(0);
	point.y += GetScrollPos(1);

	/* OnTileTool */
	if (m_bIsMapTool)
	{

		// 타일 DrawID 저장
		int iDrawID = pMyForm->m_MapTool.m_iDrawID;

		/* 타일옵션 저장(이동불가 유무) */
		BYTE byOption = 0;

		if (pMyForm->m_MapTool.m_CheckMove.GetCheck() == TRUE)
			byOption = 1;
		else
			byOption = 0;

		/* Room Number 저장 */
		BYTE byRoomNum = 0;
		byRoomNum = pMyForm->m_MapTool.m_byTileRoomNum;

		CTerrain::GetInstance()->TileChange(D3DXVECTOR3((float)point.x, (float)point.y, 0.f), iDrawID, byOption, byRoomNum);

		// Invalidate: WM_PAINT와 WM_ERASEBKGND 메시지를 발생.
		Invalidate(FALSE);


		CMiniView* pMiniView = dynamic_cast<CMiniView*>(pMainFrm->m_SecondSplit.GetPane(0, 0));
		pMiniView->Invalidate(FALSE);

	}
	else if (m_bOnSubTileTool)
	{
		int iIndex = CTerrain::GetInstance()->GetTileIndex(D3DXVECTOR3((float)point.x, (float)point.y, 0.f));

		// 타일 인덱스에서 벗어나면 종료
		if (iIndex < 0 || (size_t)iIndex > CTerrain::GetInstance()->GetVecTile().size())
			return;

		D3DXVECTOR3 vPos = CTerrain::GetInstance()->GetTilePos(iIndex);

		int iDrawID = pMyForm->m_SubTileTool.m_iDrawID;
		CSubTile::GetInstance()->AddSubTile(vPos, iDrawID);
		Invalidate(FALSE);
	}

	UpdateData(FALSE);

	CScrollView::OnLButtonDown(nFlags, point);

}


void CToolView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CScrollView::OnMouseMove(nFlags, point);

	/* 마우스 움직일 때 타일정보 출력하는 함수 */

	UpdateData(TRUE);

	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CMyForm* pMyForm = dynamic_cast<CMyForm*>(pMainFrm->m_SecondSplit.GetPane(1, 0));


	if (m_bIsMapTool)
	{

		// 마우스에 스크롤값 추가
		point.x += GetScrollPos(0);
		point.y += GetScrollPos(1);

		int iTileIndex = 0;

		iTileIndex = CTerrain::GetInstance()->GetTileIndex(D3DXVECTOR3((float)point.x, (float)point.y, 0.f));

		vector<TILE*>& vecTile = CTerrain::GetInstance()->GetVecTile();

		// 인덱스가 범위에서 벗어나면 return
		if (iTileIndex < 0 || (size_t)iTileIndex > vecTile.size())
			return;

		pMyForm->m_MapTool.UpdateData(TRUE);
		pMyForm->m_MapTool.m_byCursorIndex = iTileIndex;
		pMyForm->m_MapTool.m_byCursorDrawID = vecTile[iTileIndex]->byDrawID;
		pMyForm->m_MapTool.m_byTileOption = vecTile[iTileIndex]->byOption;
		pMyForm->m_MapTool.m_byCursorRoomNum = vecTile[iTileIndex]->byRoomNum;
		pMyForm->m_MapTool.UpdateData(FALSE);
	}

	UpdateData(FALSE);
}


void CToolView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	UpdateData(TRUE);

	if (m_bOnSubTileTool)
	{
		int iIndex = CTerrain::GetInstance()->GetTileIndex(D3DXVECTOR3((float)point.x, (float)point.y, 0.f));

		// 타일 인덱스에서 벗어나면 종료
		if (iIndex < 0 || (size_t)iIndex > CTerrain::GetInstance()->GetVecTile().size())
			return;

		// 타일 인덱스의 벡터를 받아온다.
		D3DXVECTOR3 vTilePos = CTerrain::GetInstance()->GetTilePos(iIndex);

		vector<TILE*> vecTile = CSubTile::GetInstance()->GetSubTile();

		auto& iter_find = vecTile.begin();

		for (; iter_find != vecTile.end();)
		{
			if ((*iter_find)->vPos == vTilePos)
			{
				SafeDelete(*iter_find);
				iter_find = vecTile.erase(iter_find);
				Invalidate(FALSE);
			}
			else
				++iter_find;
		}
	}
	UpdateData(FALSE);

	CScrollView::OnRButtonDown(nFlags, point);
}
