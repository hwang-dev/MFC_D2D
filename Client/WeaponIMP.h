#pragma once

class CObj;
class CWeaponIMP
{
public:
	CWeaponIMP();
	virtual ~CWeaponIMP();

public:
	virtual HRESULT Initialize() PURE;
	virtual void Update() PURE;
	virtual void LateUpdate() PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;

protected:
	bool		m_bIsInit;
	CObj*		m_pObj;
	FRAME		m_tFrame;
	wstring		m_wstStateKey;
};

