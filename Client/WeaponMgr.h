#pragma once
class CWeaponMgr
{
	DECLARE_SINGLETON(CWeaponMgr)

private:
	CWeaponMgr();
	~CWeaponMgr();

public:
	HRESULT Initialize();
	void Update();
	void LateUpdate();
	void Render();
	void AddWeapon(CObj* pObj);
	vector<CObj*>&	GetVecWeapon() { return m_vecWeapon; }

private:
	vector<CObj*>	m_vecWeapon;
	CObj*			m_pTarget;
	MATRIX			m_matWolrd;
	float			m_fAngle;
	float			m_fScaleY;
	float			m_fGunPos;
};

