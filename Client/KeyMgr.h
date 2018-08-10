#pragma once
class CKeyMgr
{
	DECLARE_SINGLETON(CKeyMgr)

private:
	CKeyMgr();
	~CKeyMgr();

public:
	void KeyCheck();
	bool KeyUp(DWORD dwKey);
	bool KeyDown(DWORD dwKey);
	bool KeyPressing(DWORD dwKey);
	bool KeyCombine(DWORD dwFirstKey, DWORD dwSecondKey);
	bool KeyCombinePressing(DWORD dwFirstKey, DWORD dwSecondKey);

private:
	DWORD m_dwKey;
	DWORD m_dwKeyPressed;
	DWORD m_dwKeyDown;
};