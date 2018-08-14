#pragma once
#include "Obj.h"
class CRoomTrigger :
	public CObj
{
public:
	CRoomTrigger();
	virtual ~CRoomTrigger();

	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
};

