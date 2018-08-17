#include "stdafx.h"
#include "RoomMgr.h"
#include "Obj.h"
#include "NormalMonster.h"

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

	if (m_byPlayerRoomNumber == 1) {
		if (m_bEnterRoom1 == false) {
			// 룸1 몬스터 생성
			// 임시 Monster 생성
			CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNormalMonster>::CreateObj(D3DXVECTOR3{ 2000.f, 300.f, 0.f}),
				OBJ_MONSTER);
			// 임시 Monster 생성
			CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNormalMonster>::CreateObj(D3DXVECTOR3{ 2000.f, 500.f, 0.f }),
				OBJ_MONSTER);
			// 임시 Monster 생성
			CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNormalMonster>::CreateObj(D3DXVECTOR3{ 2000.f, 700.f, 0.f }),
				OBJ_MONSTER);
			m_bEnterRoom1 = true;
		}
	}
}
