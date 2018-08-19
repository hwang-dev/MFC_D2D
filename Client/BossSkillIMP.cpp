#include "stdafx.h"
#include "BossSkillIMP.h"
#include "Obj.h"

CBossSkillIMP::CBossSkillIMP()
{
}


CBossSkillIMP::~CBossSkillIMP()
{
}

HRESULT CBossSkillIMP::Initialize()
{
	return E_NOTIMPL;
}

void CBossSkillIMP::LateInit()
{
	
}

int CBossSkillIMP::Update()
{
	LateInit();

	return NO_EVENT;
}

void CBossSkillIMP::LateUpdate()
{
	LateInit();
}

void CBossSkillIMP::Render()
{
	LateInit();

	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"Boss",
		L"BSkill", (int)m_pObj->GetFrame().fFrame);

	NULL_CHECK(pTexInfo);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_pObj->GetInfo().matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CBossSkillIMP::Release()
{
}
