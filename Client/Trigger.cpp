#include "stdafx.h"
#include "Trigger.h"


CTrigger::CTrigger()
{
}


CTrigger::~CTrigger()
{
	Release();
}

HRESULT CTrigger::Initialize()
{
	m_eObjectID = OBJ_TRIGGER;
	return S_OK;
}

int CTrigger::Update()
{
	if (m_bIsDead)
		return DEAD_OBJ;

	return NO_EVENT;
}

void CTrigger::LateUpdate()
{
}

void CTrigger::Render()
{
	CObj::UpdateRect();

	if (g_bOnRect) {
		RenderLine();
	}
}

void CTrigger::Release()
{
}

HRESULT CTrigger::LoadTrigger()
{
	HANDLE hFile = CreateFile(L"../Data/Trigger.dat", GENERIC_READ, 0, 0,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		ERR_MSG(L"Trigger Load Failed!!");
		return E_FAIL;
	}

	Release();

	INFO tInfo = {};
	DWORD dwByte = 0;

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		tInfo.vSize = { 36.f, 36.f ,36.f };
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CTrigger>::CreateObj(tInfo), OBJ_TRIGGER);

	}

	CloseHandle(hFile);
	return S_OK;
}
