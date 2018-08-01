// SubTileTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "SubTileTool.h"
#include "afxdialogex.h"


// CSubTileTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSubTileTool, CDialog)

CSubTileTool::CSubTileTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_SUBTILETOOL, pParent)
{

}

CSubTileTool::~CSubTileTool()
{
}

void CSubTileTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSubTileTool, CDialog)
END_MESSAGE_MAP()


// CSubTileTool 메시지 처리기입니다.
