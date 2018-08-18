#pragma once
class CSoundMgr
{
	DECLARE_SINGLETON(CSoundMgr)

public:
	enum CHANNEL { BGM, PLAYER, MONSTER, EFFECT, END };

private:
	CSoundMgr();
	~CSoundMgr();

public:
	void Initialize();
	void UpdateSound();
	void PlaySound(const TCHAR* pSoundKey, CHANNEL eID);
	void PlayBGM(const TCHAR* pSoundKey);
	void StopSound(CHANNEL eID);
	void StopAll();
	void Release();

private:
	void LoadSoundFile();


private:
	FMOD_SYSTEM*					m_pSystem;	// FMOD_SYSTEM: 사운드 재생을 총괄하는 장치.
	FMOD_CHANNEL*					m_pChannel[END]; // FMOD_CHANNEL: 사운드 재생을 관리하는 객체.
	map<const TCHAR*, FMOD_SOUND*>	m_MapSound; // FMOD_SOUND: 사운드 리소스 정보를 갖는 객체.
};

