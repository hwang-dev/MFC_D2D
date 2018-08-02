// TriggerTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "TriggerTool.h"
#include "afxdialogex.h"


// CTriggerTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(CTriggerTool, CDialog)

CTriggerTool::CTriggerTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_TRIGGERTOOL, pParent)
{

}

CTriggerTool::~CTriggerTool()
{
}

void CTriggerTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTriggerTool, CDialog)
END_MESSAGE_MAP()


// CTriggerTool 메시지 처리기입니다.
