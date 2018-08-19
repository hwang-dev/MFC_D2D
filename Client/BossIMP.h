#pragma once

class CObj;
class BossIMP
{
public:
	BossIMP();
	virtual ~BossIMP();

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
	
};

