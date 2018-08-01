#pragma once
#include "afxwin.h"


// CFilePath 대화 상자입니다.

class CFilePath : public CDialog
{
	DECLARE_DYNAMIC(CFilePath)

public:
	CFilePath(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CFilePath();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FILEPATH };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedLoad();

	list<IMGPATH*>	m_PathInfoLst;
	CListBox m_ListBox;
};
