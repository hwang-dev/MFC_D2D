#pragma once
#include "Obj.h"
class CTrigger :
	public CObj
{
public:
	CTrigger();
	virtual ~CTrigger();

	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	HRESULT LoadTrigger();

private:

};

