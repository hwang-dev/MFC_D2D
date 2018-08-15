#pragma once
#include "Bullet.h"
class CMonsterBullet :
	public CBullet
{
public:
	CMonsterBullet();
	virtual ~CMonsterBullet();

	// CBullet을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	float	m_fAnimSpeed = 0.f;
};

