#pragma once

class CObj;
class CBossIMP
{
public:
	CBossIMP();
	virtual ~CBossIMP();

public:
	void SetObj(CObj* pObj) { m_pObj = pObj; }

public:
	virtual HRESULT Initialize() PURE;
	virtual void LateInit();
	virtual int Update() PURE;
	virtual void LateUpdate() PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;

protected:
	CObj*		m_pObj = nullptr;
	bool		m_bIsInit = nullptr;
	float		m_fSpeed = 0.f;
	float		m_fPatternTime = 0.f;
	float		m_fPatternDelay = 0.f;
	float		m_fAttackTime = 0.f;
};

