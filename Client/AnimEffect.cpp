#include "stdafx.h"
#include "AnimEffect.h"
#include "Obj.h"
#include "NormalMonster.h"
#include "Boss2.h"
CAnimEffect::CAnimEffect()
{
	ZeroMemory(&m_tFrame, sizeof(FRAME));
}


CAnimEffect::~CAnimEffect()
{
	Release();
}

HRESULT CAnimEffect::Initialize()
{
	
	return S_OK;
}

void CAnimEffect::LateInit()
{
	if (!wcscmp(L"Portal", m_wstrStateKey.c_str()))
		CSoundMgr::GetInstance()->PlaySound(L"Monster_Appear.wav", CSoundMgr::EFFECT);
}

int CAnimEffect::Update()
{
	CEffectIMP::LateInit();

	m_tFrame.fFrame += m_tFrame.fMax * CTimeMgr::GetInstance()->GetTime() * 1.f;

	if (m_tFrame.fFrame > m_tFrame.fMax)
	{
		if (!wcscmp(L"Portal", m_wstrStateKey.c_str())) {
			D3DXVECTOR3 vPos = m_pObj->GetInfo().vPos;
			CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNormalMonster>::CreateObj(vPos),
				OBJ_MONSTER);
			return DEAD_OBJ;
		}
		else if (!wcscmp(L"Book", m_wstrStateKey.c_str())) {
			m_tFrame.fFrame = 41.f;
		}
		if (!wcscmp(L"Boss", m_wstrStateKey.c_str())) {
			CObjMgr::GetInstance()->AddObject(CAbstractFactory<CBoss2>::CreateObj(D3DXVECTOR3{ 591.f, 1378.f, 0.f }),
				OBJ_BOSS);
			return DEAD_OBJ;
		}
		else
			return DEAD_OBJ;
	}


	return NO_EVENT;
}

void CAnimEffect::LateUpdate()
{
}

void CAnimEffect::Render()
{
	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(
		m_pObj->GetObjKey().c_str(), m_wstrStateKey.c_str(), (int)m_tFrame.fFrame);

	NULL_CHECK(pTexInfo);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_pObj->GetInfo().matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	
}

void CAnimEffect::Release()
{
}
