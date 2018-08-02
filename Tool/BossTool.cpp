// BossTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "BossTool.h"
#include "afxdialogex.h"


// CBossTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(CBossTool, CDialog)

CBossTool::CBossTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_BOSSTOOL, pParent)
{

}

CBossTool::~CBossTool()
{
}

void CBossTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBossTool, CDialog)
END_MESSAGE_MAP()


// CBossTool 메시지 처리기입니다.
