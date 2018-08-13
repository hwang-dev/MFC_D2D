#pragma once
class CScrollMgr
{
public:
	CScrollMgr();
	~CScrollMgr();

public:
	static const D3DXVECTOR3& GetScroll() { return m_vScroll; }
	static const D3DXVECTOR3& GetCamera() { return m_vCamera; }
	
public:
	static void SetScroll(float x, float y);
	static void ScrollLock();
	static void ScrollLock2();
	static void SetCamera(float x, float y);
	static void AddScroll(D3DXVECTOR3& vPos);
public:
	static void CameraShakeNormal();

private:
	static D3DXVECTOR3 m_vScroll;
	static D3DXVECTOR3 m_vCamera;

	static float m_fShakeTime;

	static int	m_iRandom;
	static bool m_bIsShaking;
};

