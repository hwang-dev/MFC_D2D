#pragma once

class CObj;
class MonsterIMP
{
public:
	MonsterIMP();
	virtual ~MonsterIMP();

public:
	void SetObj(CObj* pObj) { m_pObj = m_pObj; }
	const wstring& GetobjKey() { return m_wstrObjKey; }
	const wstring& GetStateKey() { return m_wstrStateKey; }

public:
	virtual HRESULT Initialize() PURE;
	virtual int Update() PURE;
	virtual void LateUpdate() PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;

protected:
	CObj*		m_pObj = nullptr;
	wstring		m_wstrObjKey = L"";
	wstring		m_wstrStateKey = L"";
	float		m_fAnimAcc = 0.f;
	FRAME		m_tFrame;
};

