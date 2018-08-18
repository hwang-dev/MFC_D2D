#include "stdafx.h"
#include "SoundMgr.h"

IMPLEMENT_SINGLETON(CSoundMgr)

CSoundMgr::CSoundMgr()
{
}


CSoundMgr::~CSoundMgr()
{
	Release();
}

void CSoundMgr::Initialize()
{
	FMOD_System_Create(&m_pSystem);
	FMOD_System_Init(m_pSystem, END, FMOD_INIT_NORMAL, nullptr);

	LoadSoundFile();
}

void CSoundMgr::UpdateSound()
{
	FMOD_System_Update(m_pSystem);
}

void CSoundMgr::PlaySound(const TCHAR * pSoundKey, CHANNEL eID)
{
	auto& iter_find = find_if(m_MapSound.begin(), m_MapSound.end(), 
		[&pSoundKey](auto& MyPair)
	{
		return !lstrcmp(pSoundKey, MyPair.first);
	});

	if (m_MapSound.end() == iter_find)
		return;

	FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, 
		iter_find->second, FALSE, &m_pChannel[eID]);
}

void CSoundMgr::PlayBGM(const TCHAR * pSoundKey)
{
	auto& iter_find = find_if(m_MapSound.begin(), m_MapSound.end(),
		[&pSoundKey](auto& MyPair)
	{
		return !lstrcmp(pSoundKey, MyPair.first);
	});

	if (m_MapSound.end() == iter_find)
		return;

	FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE,
		iter_find->second, FALSE, &m_pChannel[BGM]);

	FMOD_Channel_SetMode(m_pChannel[BGM], FMOD_LOOP_NORMAL);
}

void CSoundMgr::StopSound(CHANNEL eID)
{
	FMOD_Channel_Stop(m_pChannel[eID]);
}

void CSoundMgr::StopAll()
{
	for(int i = 0; i < END; ++i)
		FMOD_Channel_Stop(m_pChannel[i]);
}

void CSoundMgr::Release()
{
	for (auto& MyPair : m_MapSound)
	{
		delete[] MyPair.first;
		FMOD_Sound_Release(MyPair.second);
	}

	m_MapSound.clear();

	FMOD_System_Release(m_pSystem);
	FMOD_System_Close(m_pSystem);
}

void CSoundMgr::LoadSoundFile()
{
	_finddata_t fd;
	long handle = _findfirst("../Sound/*.*", &fd);

	if (0 == handle)
	{
		MessageBox(g_hWnd, L"_findfirst failed", L"fail!!", MB_OK);
		return;
	}

	char szCurPath[128] = "../Sound/";
	char szFullpath[128] = "";

	int iResult = 0;

	while (-1 != iResult)
	{
		strcpy_s(szFullpath, szCurPath);
		strcat_s(szFullpath, fd.name);

		FMOD_SOUND* pSound = nullptr;
		FMOD_RESULT eRes = FMOD_System_CreateSound(m_pSystem, szFullpath, FMOD_HARDWARE,
			nullptr, &pSound);

		if (FMOD_OK == eRes)
		{
			int iMaxLen = strlen(fd.name) + 1;
			TCHAR* pSoundKey = new TCHAR[iMaxLen]{};

			// 멀티바이트 -> 와이드바이트
			MultiByteToWideChar(CP_ACP, 0, fd.name, iMaxLen, pSoundKey, iMaxLen);

			m_MapSound.insert({ pSoundKey, pSound });
		}

		// 더 이상 찾을 파일이 없다면 -1을 반환.
		iResult = _findnext(handle, &fd);
	}

	_findclose(handle);
	FMOD_System_Update(m_pSystem);
}
