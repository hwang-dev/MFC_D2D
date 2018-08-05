#pragma once
class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	const INFO& GetInfo() const { return m_tInfo; }
	void SetPos(D3DXVECTOR3& vPos) { m_tInfo.vPos = vPos; }

	const wstring& GetObjKey() { return m_wstrObjKey; }

public:
	virtual HRESULT Initialize() PURE;
	virtual void LateInit();
	virtual int Update() PURE;
	virtual void LateUpdate() PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;

protected:
	void MoveFrame();
	void UpdateRect();

protected:
	INFO	m_tInfo;
	RECT	m_tRect;
	FRAME	m_tFrame;

	bool	m_bIsInit;
	wstring	m_wstrObjKey;
};

