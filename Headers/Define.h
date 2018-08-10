#pragma once

#define WINCX 1280
#define WINCY 720

#define TILEX	70
#define TILEY	70

#define TILECX	36
#define TILECY	36

#define MIN_STR 64
#define MID_STR 128
#define MAX_STR 256

#define NO_EVENT 0
#define DEAD_OBJ 1

#define NULL_CHECK(ptr) if(nullptr == (ptr)) return;

#define ERR_MSG(message)	\
	MessageBox(g_hWnd, message, L"Error!", MB_OK)

#define NO_COPY(ClassName)					\
private:									\
	ClassName(ClassName& _obj);				\
	ClassName& operator=(ClassName& _obj);

#define DECLARE_SINGLETON(ClassName)		\
		NO_COPY(ClassName)					\
public:										\
	static ClassName* GetInstance()			\
	{										\
		if (nullptr == m_pInstance)			\
			m_pInstance = new ClassName;	\
		return m_pInstance;					\
	}										\
	void DestroyInstance()					\
	{										\
		if (m_pInstance)					\
		{									\
			delete m_pInstance;				\
			m_pInstance = nullptr;			\
		}									\
	}										\
private:									\
	static ClassName*	m_pInstance;

#define IMPLEMENT_SINGLETON(ClassName)		\
	ClassName*	ClassName::m_pInstance = nullptr;

