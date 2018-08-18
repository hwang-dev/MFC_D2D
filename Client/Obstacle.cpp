#include "stdafx.h"
#include "Obstacle.h"


CObstacle::CObstacle()
{
}


CObstacle::~CObstacle()
{
}

HRESULT CObstacle::Initialize()
{
	m_eObjectID = OBJ_OBSTACLE;

	return S_OK;
}

int CObstacle::Update()
{


	return NO_EVENT;
}

void CObstacle::LateUpdate()
{
}

void CObstacle::Render()
{
	UpdateRect();

	if (g_bOnRect)
		RenderLine();
}

void CObstacle::Release()
{
}

HRESULT CObstacle::LoadObstacle()
{
	HANDLE hFile = CreateFile(L"../Data/BoxData.dat", GENERIC_READ, 0, 0,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		ERR_MSG(L"Box Load Failed!!");
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

		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CObstacle>::CreateObj(tInfo), OBJ_OBSTACLE);

	}

	CloseHandle(hFile);
	return S_OK;
}
