#pragma once
#include "afxwin.h"


// CMonsterTool 대화 상자입니다.

class CMonsterTool : public CDialog
{
	DECLARE_DYNAMIC(CMonsterTool)

public:
	CMonsterTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMonsterTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MONSTERTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	/* MFC Ctrl */
	CButton m_RadioType[3];
	CListBox m_ListBox;
	CListBox m_SetBox;
	float m_fAttSpd;
	float m_fBulletSpd;

	/* MFC Func */
	afx_msg void OnBnClickedSetBtn();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	virtual BOOL OnInitDialog();

	/* User */
	int i = 0;

	/* User Func */
	void Release();
};
