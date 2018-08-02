#pragma once
#include "Scene.h"
class CBoss :
	public CScene
{
public:
	CBoss();
	virtual ~CBoss();

	// CScene을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
};

