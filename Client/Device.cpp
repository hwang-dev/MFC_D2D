#include "stdafx.h"
#include "Device.h"

IMPLEMENT_SINGLETON(CDevice)

CDevice::CDevice()
	: m_p3D(nullptr), m_pDevice(nullptr), m_pSprite(nullptr), m_pFont(nullptr)
{
}


CDevice::~CDevice()
{
	Release();
}

HRESULT CDevice::InitDevice()
{
	// 장치 초기화 과정
	// 1.	LPDIRECT3D9 객체 생성
	m_p3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (nullptr == m_p3D)
		return E_FAIL;

	// 2. 장치 조사(성능, 버텍스 프로세싱 유무)
	// 버텍스(정점) 프로세싱: 정점 처리 + 조명 처리. ex) 정점이 많을수록 더욱 더 실사에 가깝게 사물을 묘사.
	// 버텍스 프로세싱이 하드웨어에서 지원하는지를 조사해야한다.

	// HAL(Hardware Abstraction Layer, 하드웨어 추상 계층)
	// 제조사가 다를지라도 특정 플랫폼에 대해 동일하게 동작하기 위해서는
	// 각 제조사마다 하드웨어들에 필요한 데이터 정보들을 추상화할 필요가 있다.

	// 2-1.HAL을 통하여 현재 장치에 대한 정보를 얻은 뒤 D3DCAPS9 구조체에 기록해야함.
	D3DCAPS9 DeviceCaps;
	ZeroMemory(&DeviceCaps, sizeof(D3DCAPS9));

	// GetDeviceCaps: 장치에 대한 정보(HAL)을 얻어오는 함수.
	if (FAILED(m_p3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &DeviceCaps)))
	{
		ERR_MSG(L"GetDeviceCaps Failed!!!");
		return E_FAIL;
	}

	// 2-2. 버텍스 프로세싱 유무 조사
	DWORD vp;

	// HAL을 통해 조사한 장치가 하드웨어 버텍스 프로세싱을 지원하는지 조사.
	if (DeviceCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;	// 하드웨어 버텍스 프로세싱을 사용.
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;


	// 3. LPDIRECT3DDEVICE9 객체 생성

	// 3-1. 
	// D3DPRESENT_PARAMETERS: 우리가 생성하고자 하는 LPDIRECT3DDEVICE9의 성격을 결정 짓는 구조체.
	D3DPRESENT_PARAMETERS	d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));	

	SetParemeters(d3dpp);

	// 3-2. LPDIRECT3DDEVICE9 객체 생성
	if (FAILED(m_p3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd, vp, &d3dpp, &m_pDevice)))
	{
		ERR_MSG(L"Device Create Failed!!");
		return E_FAIL;
	}

	// 스프라이트 Com객체 생성
	if (FAILED(D3DXCreateSprite(m_pDevice, &m_pSprite)))
	{
		ERR_MSG(L"Sprite Create Failed!!");
		return E_FAIL;
	}

	// 폰트 Com객체 생성
	// D3DXFONT_DESCW: 출력할 폰트의 속성을 설정.
	D3DXFONT_DESCW	tFontInfo;
	
	tFontInfo.Height = 15;	// 높이
	tFontInfo.Width = 5;	// 너비
	tFontInfo.Weight = FW_HEAVY; // 두께
	tFontInfo.CharSet = HANGEUL_CHARSET; // 한글
	lstrcpy(tFontInfo.FaceName, L"Consolas"); // 글씨체

	// D3DXFONT_DESCW 속성을 바탕으로 폰트 Com객체를 생성하고 있다.
	// LPD3DXFONT는 폰트 텍스쳐(이미지)를 일일히 생성하여 출력하므로 느리다는 단점이 존재한다.
	if (FAILED(D3DXCreateFontIndirect(m_pDevice, &tFontInfo, &m_pFont)))
	{
		ERR_MSG(L"Font Create Failed!!");
		return E_FAIL;
	}

	AddFontResourceEx(L"../Font/digital-7.ttf", FR_PRIVATE, 0);
	tFontInfo.Height = 16;	// 높이
	tFontInfo.Width = 8;	// 너비
	tFontInfo.Weight = FW_HEAVY; // 두께
	tFontInfo.Italic = FALSE;
	tFontInfo.CharSet = DEFAULT_CHARSET; // 한글
	lstrcpy(tFontInfo.FaceName, L"Digital-7"); // 글씨체

	if (FAILED(D3DXCreateFontIndirect(m_pDevice, &tFontInfo, &m_pMyFont)))
	{
		ERR_MSG(L"Font Create Failed!!");
		return E_FAIL;
	}

	if (FAILED(D3DXCreateLine(m_pDevice, &m_pLine)))
	{
		ERR_MSG(L"Line Create Failed!!");
		return E_FAIL;
	}

	return S_OK; // 성공했을 때	
	// 실패했을때 E_FAIL을 리턴.
}

void CDevice::Render_Begin()
{
	// 렌더링 과정: 후면버퍼를 비운다. -> 후면버퍼에 그린다. -> 후면버퍼를 전면버퍼로 교체한 후 화면에 출력한다.

	// 1. 후면 버퍼를 비운다.
	m_pDevice->Clear(0, nullptr, D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER | D3DCLEAR_TARGET,
		D3DCOLOR_ARGB(255, 0, 0, 0), 1.f, 0);

	// 2. 후면버퍼에 그린다
	// 여기서부터 출력할 씬(장면)의 시작 점이다.
	m_pDevice->BeginScene();

	// 2D 이미지를 렌더링 할 수 있도록 장치를 준비.
	// D3DXSPRITE_ALPHABLEND: 알파 테스트가 유효한 상태에서 알파 블렌딩을 사용한다.
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void CDevice::Render_End(HWND hWnd/* = nullptr*/)
{
	// 2D 이미지를 그리고나서 장치를 복원.
	m_pSprite->End();

	// 여기까지가 출력할 씬의 끝점이다.
	m_pDevice->EndScene();

	// 3.후면버퍼를 전면버퍼로 교체한 후 화면에 출력한다.
	m_pDevice->Present(nullptr, nullptr, hWnd, nullptr);
}

void CDevice::Release()
{
	// 순서 주의. m_p3D를 먼저 해제할 경우 m_pDevice는 소실된다.
	if (m_pLine)
		m_pLine->Release();

	if (m_pMyFont)
		m_pMyFont->Release();

	if (m_pFont)
		m_pFont->Release();

	if (m_pSprite)
		m_pSprite->Release();

	if (m_pDevice)
		m_pDevice->Release();

	if (m_p3D)
		m_p3D->Release();
}


void CDevice::SetParemeters(D3DPRESENT_PARAMETERS & d3dpp)
{
	// 후면 버퍼의 가로, 세로 크기 지정.
	d3dpp.BackBufferWidth = WINCX;
	d3dpp.BackBufferHeight = WINCY;

	// 후면버퍼 픽셀 포맷 설정. 32비트 포맷.
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;

	// 후면버퍼 개수.
	d3dpp.BackBufferCount = 1;

	// 후면버퍼에서 사용할 멀티 샘플링 타입.
	// 현재는 사용하지 않는다. 사용하게되면 퍼포먼스 저하.
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	
	// 멀티 샘플링 품질
	d3dpp.MultiSampleQuality = 0;

	// 스왑체인 방식 결정.
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

	// 장치를 사용한 윈도우 설정.
	d3dpp.hDeviceWindow = g_hWnd;

	d3dpp.Windowed = TRUE; // 창모드

	// Direct가 깊이/스텐실 버퍼를 만들고 자동으로 관리하길 원하다면 TRUE
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

	d3dpp.Flags = 0;

	// 전체화면 시 모니터 주사율(재생률) 지정.
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;

	// 모니터 주사율과 FPS의 간격.
	// D3DPRESENT_INTERVAL_IMMEDIATE: 현재 프로그램 FPS에 따라 즉시 시연.
	// D3DPRESENT_INTERVAL_DEFAULT: 적절한 간격을 Directx가 알아서 결정. 보통 재생률을 따라감.
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
}
