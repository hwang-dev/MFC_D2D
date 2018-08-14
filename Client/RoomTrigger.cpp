#include "stdafx.h"
#include "RoomTrigger.h"


CRoomTrigger::CRoomTrigger()
{
}


CRoomTrigger::~CRoomTrigger()
{
	Release();
}

HRESULT CRoomTrigger::Initialize()
{
	m_wstrObjKey = L"RoomTrigger";
	m_tInfo.vSize = { 36.f, 36.f, 0.f};

	return S_OK;
}

void CRoomTrigger::LateInit()
{
}

int CRoomTrigger::Update()
{
	return NO_EVENT;;
}

void CRoomTrigger::LateUpdate()
{
}

void CRoomTrigger::Render()
{
}

void CRoomTrigger::Release()
{
}
