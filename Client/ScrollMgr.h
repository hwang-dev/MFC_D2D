#pragma once
class CScrollMgr
{
public:
	CScrollMgr();
	~CScrollMgr();

public:
	static const D3DXVECTOR3& GetScroll() { return m_vScroll; }

public:
	static void SetScroll(float x, float y);
	static void ScrollLock();

private:
	static D3DXVECTOR3 m_vScroll;
};

