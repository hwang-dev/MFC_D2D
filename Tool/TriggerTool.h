#pragma once


// CTriggerTool 대화 상자입니다.

class CTriggerTool : public CDialog
{
	DECLARE_DYNAMIC(CTriggerTool)

public:
	CTriggerTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTriggerTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TRIGGERTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	BYTE m_byRoomNumer;
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	BYTE m_byCursorRoomNum;
	afx_msg void OnBnClickedClear();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedLoad();
	afx_msg void OnBnClickedSave();
	afx_msg void OnEnChangeRoomNumber();
};
