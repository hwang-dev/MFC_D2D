#pragma once
class CWeaponMgr
{
	DECLARE_SINGLETON(CWeaponMgr)

private:
	CWeaponMgr();
	~CWeaponMgr();

public:
	void Render();
};

