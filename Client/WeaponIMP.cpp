#include "stdafx.h"
#include "WeaponIMP.h"


CWeaponIMP::CWeaponIMP()
	: m_bIsInit(false),
	m_wstStateKey(L""),
	m_pObj(nullptr)
{
	ZeroMemory(&m_tFrame, sizeof(FRAME));
}


CWeaponIMP::~CWeaponIMP()
{
}

