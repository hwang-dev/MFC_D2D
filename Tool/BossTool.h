#pragma once


// CBossTool 대화 상자입니다.

class CBossTool : public CDialog
{
	DECLARE_DYNAMIC(CBossTool)

public:
	CBossTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CBossTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BOSSTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	BYTE m_byRoom;
	afx_msg void OnEnChangeRoom();
	afx_msg void OnBnClickedClear();
	afx_msg void OnBnClickedLoad();
	afx_msg void OnBnClickedSave();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnBnClickedCancel();
};
