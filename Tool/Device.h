#pragma once
class CDevice
{
	DECLARE_SINGLETON(CDevice)
private:
	CDevice();
	~CDevice();

public:
	HRESULT InitDevice();
	void Render_Begin();
	void Render_End(HWND hWnd = nullptr);
	void Release();

public:
	LPDIRECT3DDEVICE9 GetDevice() { return m_pDevice; }
	LPD3DXSPRITE GetSprite() { return m_pSprite; }
	LPD3DXFONT GetFont() { return m_pFont; }

private:
	void SetParemeters(D3DPRESENT_PARAMETERS& d3dpp);

private:
	// IDirect3D9: 여러 장치를 제어하기 위해 기능들이 구현되어있는 객체포인터(LPDIRECT3D9).
	// I (Interface)
	LPDIRECT3D9			m_p3D;

	// IDirect3DDevice9: 그래픽 장치를 통해 렌더링을 제어하는 객체포인터(LPDIRECT3DDEVICE9)
	// I (Interface)
	LPDIRECT3DDEVICE9	m_pDevice;

	// LPD3DXSPRITE: DirectX에서 2D 이미지를 렌더링하고 제어하는 Com객체.
	LPD3DXSPRITE		m_pSprite;

	// LPD3DXFONT: 폰트를 출력하는 Com객체
	LPD3DXFONT			m_pFont;
	LPD3DXFONT			m_pMyFont;

	// I로 시작하는 인터페이스들을 COM객체라 부른다.
	// COM(Component Object Model)
	// 개발 환경에 상관없이 호환이 가능한 컴포넌트(부품)의 사용을 위해 
	// 마이크로 소프트가 규정한 표준화된 방법이 바로 COM이다.
};

