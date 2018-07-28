#pragma once
class CScrollMgr
{
public:
	CScrollMgr();
	~CScrollMgr();

public:
	static const float& GetScrollX() { return m_fScrollX; }
	static const float& GetScrollY() { return m_fScrollY; }

public:
	static void SetScroll(float x, float y);

private:
	static float m_fScrollX;
	static float m_fScrollY;
};

