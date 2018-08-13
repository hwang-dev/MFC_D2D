#pragma once
class CWeaponMgr
{
	DECLARE_SINGLETON(CWeaponMgr)

private:
	CWeaponMgr();
	~CWeaponMgr();

public:
	HRESULT Initialize();
	void Release();
	void Update();
	void LateUpdate();
	void Render();

public:
	void AddWeapon(CObj* pObj);
	vector<CObj*>&	GetVecWeapon() { return m_vecWeapon; }

private:
	vector<CObj*>	m_vecWeapon;
	CObj*			m_pTarget;
	CObj*			m_pPlayerGun;

	D3DXMATRIX		m_matWorld;
	float			m_fAngle;
	float			m_fScaleX;
	float			m_fGunPos;
	
};

