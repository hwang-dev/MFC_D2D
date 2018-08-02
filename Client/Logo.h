#pragma once
#include "Scene.h"
class CLogo :
	public CScene
{
public:
	CLogo();
	virtual ~CLogo();

	// CScene을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
};

