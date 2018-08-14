#pragma once

class CToolView;
class CTriggerMgr
{
	DECLARE_SINGLETON(CTriggerMgr)

private:
	CTriggerMgr();
	~CTriggerMgr();

public:
	void Initialize();
	void Update();
	void LateUpdate();
	void Render();
	void Release();

public:
	void SetMainView(CToolView* pView) { m_pMainView = pView; }
	void AddTrigger(D3DXVECTOR3& vPos, BYTE& RoomNum);
	vector<INFO*>& GetVecTrigger() { return m_vecTrigger; }

private:
	vector<INFO*>	m_vecTrigger;
	CToolView*		m_pMainView;
};

