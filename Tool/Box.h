#pragma once

class CToolView;
class CBox
{
	DECLARE_SINGLETON(CBox)

private:
	CBox();
	~CBox();

public:
	void Initialize();
	void Update();
	void LateUpdate();
	void Render();
	void Release();

public:
	void SetMainView(CToolView* pView) { m_pMainView = pView; }
	void AddTrigger(D3DXVECTOR3& vPos);
	vector<INFO*>& GetVecBox() { return m_vecBox; }

private:
	vector<INFO*>	m_vecBox;
	CToolView*		m_pMainView = nullptr;
};

