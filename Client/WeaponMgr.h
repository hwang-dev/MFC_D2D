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
	void AddWeapon(CObj* pObj);

private:
	vector<CObj*>	m_vecWeapon;
	CObj*			m_pTarget;
};

