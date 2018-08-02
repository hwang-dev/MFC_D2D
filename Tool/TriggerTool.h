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
};
