#pragma once

class CToolView;
class CDark
{
	DECLARE_SINGLETON(CDark)

private:
	CDark();
	~CDark();

public:
	void Initialize();
	void Update();
	void LateUpdate();
	void Render();
	void Release();

	void SetMainView(CToolView* pView) { m_pMainView = pView; }
	void AddDark(D3DXVECTOR3& vPos, BYTE& RoomNum);
	vector<INFO*>& GetvecDark() { return m_vecDark; }

private:
	vector<INFO*>	m_vecDark;
	CToolView*		m_pMainView = nullptr;
};

