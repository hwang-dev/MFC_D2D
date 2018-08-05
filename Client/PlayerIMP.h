#pragma once

/* Player ±¸ÇöÃþ */
class CObj;
class CPlayerIMP
{
public:
	CPlayerIMP();
	virtual ~CPlayerIMP();

	void SetObj(CObj* pObj) { m_pObj = pObj; }
	void SetStateKey(wstring wstrStateKey) { m_wstrStateKey = wstrStateKey; }

public:
	virtual HRESULT Initialize() PURE;
	virtual void LateInit();
	virtual int Update() PURE;
	virtual void LateUpdate() PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;

private:
	CObj*		m_pObj;
	wstring		m_wstrStateKey;
	bool		m_bIsInit;
};

