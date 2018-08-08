#pragma once
class CWeaponMgr
{
	DECLARE_SINGLETON(CWeaponMgr)

private:
	CWeaponMgr();
	~CWeaponMgr();

public:
	HRESULT Initialize();
	void Render();
	void LateUpdate();
	void AddWeapon(CObj* pObj);
	vector<CObj*>&	GetVecWeapon() { return m_vecWeapon; }

private:
	vector<CObj*>	m_vecWeapon;
	CObj*			m_pTarget;
};

