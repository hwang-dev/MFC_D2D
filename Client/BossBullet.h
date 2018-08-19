#pragma once
#include "Bullet.h"
class CBossBullet :
	public CBullet
{
public:
	CBossBullet();
	virtual ~CBossBullet();

	// CBullet을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
};

