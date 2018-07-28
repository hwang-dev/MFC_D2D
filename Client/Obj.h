#pragma once
class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	virtual HRESULT Initialize() PURE;
	virtual void LateInit();
	virtual int Update() PURE;
	virtual void LateUpdate() PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;

protected:
	INFO m_tInfo;
	bool m_bIsInit;
};

