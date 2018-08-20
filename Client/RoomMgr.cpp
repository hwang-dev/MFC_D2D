#include "stdafx.h"
#include "RoomMgr.h"
#include "Obj.h"
#include "NormalMonster.h"
#include "Boss2.h"

#include "AnimEffect.h"
#include "Effect.h"

IMPLEMENT_SINGLETON(CRoomMgr)

CRoomMgr::CRoomMgr()
{
}


CRoomMgr::~CRoomMgr()
{
}

void CRoomMgr::Initialize()
{
	m_byPlayerRoomNumber = CObjMgr::GetInstance()->GetPlayer()->GetInfo().byRoomNum;
}

void CRoomMgr::Update()
{
	m_byPlayerRoomNumber = CObjMgr::GetInstance()->GetPlayer()->GetInfo().byRoomNum;

	if (m_byPlayerRoomNumber == 2) {
		if (m_bEnterRoom1 == false) {
			
			// 룸1 몬스터 생성
			// 임시 Monster 생성
			
			CObjMgr::GetInstance()->AddObject(CEffectFactory<CEffect, CAnimEffect>::CreateEffect(D3DXVECTOR3(1700.f, 300.f, 0.f), L"Portal", { 0.f, 14.f })
				, OBJ_EFFECT);
			CObjMgr::GetInstance()->AddObject(CEffectFactory<CEffect, CAnimEffect>::CreateEffect(D3DXVECTOR3(1700.f, 500.f, 0.f), L"Portal", { 0.f, 14.f })
				, OBJ_EFFECT);
			CObjMgr::GetInstance()->AddObject(CEffectFactory<CEffect, CAnimEffect>::CreateEffect(D3DXVECTOR3(1700.f, 700.f, 0.f), L"Portal", { 0.f, 14.f })
				, OBJ_EFFECT);
			CObjMgr::GetInstance()->AddObject(CEffectFactory<CEffect, CAnimEffect>::CreateEffect(D3DXVECTOR3(2000.f, 300.f, 0.f), L"Portal", { 0.f, 14.f })
				, OBJ_EFFECT);
			CObjMgr::GetInstance()->AddObject(CEffectFactory<CEffect, CAnimEffect>::CreateEffect(D3DXVECTOR3(2000.f, 500.f, 0.f), L"Portal", { 0.f, 14.f })
				, OBJ_EFFECT);
			CObjMgr::GetInstance()->AddObject(CEffectFactory<CEffect, CAnimEffect>::CreateEffect(D3DXVECTOR3(2000.f, 700.f, 0.f), L"Portal", { 0.f, 14.f })
				, OBJ_EFFECT);
			CSoundMgr::GetInstance()->PlaySound(L"Monster_Appear2.wav", CSoundMgr::EFFECT);
			m_bEnterRoom1 = true;
		}
	}

	else if (m_byPlayerRoomNumber == 4)
	{
		if (m_bEnterRoom2 == false)
		{
			CObjMgr::GetInstance()->AddObject(CEffectFactory<CEffect, CAnimEffect>::CreateEffect(D3DXVECTOR3(2000.f, 1600.f, 0.f), L"Portal", { 0.f, 14.f })
				, OBJ_EFFECT);
			m_bEnterRoom2 = true;
		}
	}
	else if (m_byPlayerRoomNumber == 6) 
	{
		if (m_bEnterRoom3 == false) 
		{
			D3DXVECTOR3 vPos = CObjMgr::GetInstance()->GetPlayer()->GetInfo().vPos;
			CObjMgr::GetInstance()->AddObject(CEffectFactory<CEffect, CAnimEffect>::CreateEffect(vPos, L"Boss", { 0.f, 12.f })
				, OBJ_EFFECT);
			m_bEnterRoom3 = true;
		}
	}
}

