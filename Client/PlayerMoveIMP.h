#pragma once
#include "PlayerIMP.h"
class CPlayerMoveIMP :
	public CPlayerIMP
{
public:
	CPlayerMoveIMP();
	~CPlayerMoveIMP();

	// CPlayerIMP을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
};

