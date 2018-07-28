#include "stdafx.h"
#include "TimeMgr.h"

IMPLEMENT_SINGLETON(CTimeMgr)

CTimeMgr::CTimeMgr()
	: m_fTime(0.f)
{
	ZeroMemory(&m_CurTime, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_OldTime1, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_OldTime2, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_CpuTick, sizeof(LARGE_INTEGER));
}


CTimeMgr::~CTimeMgr()
{
}

// 최초 한번 초기화.
void CTimeMgr::InitTime()
{
	// QueryPerformanceCounter: 
	// 메인보드가 가지고 있는 고해상도 타이머의 현재 누적 시간을 얻어온다.
	// 1 / 10000 초 단위로 얻어온다.
	QueryPerformanceCounter(&m_CurTime);
	QueryPerformanceCounter(&m_OldTime1);
	QueryPerformanceCounter(&m_OldTime2);

	// QueryPerformanceFrequency: CPU의 진동 주기를 얻어오는 함수. 1초에 몇번 진동하는가!
	QueryPerformanceFrequency(&m_CpuTick);
}

// 매 프레임마다 시간 갱신.
void CTimeMgr::UpdateTime()
{
	// 매 프레임마다 현재 시간을 갱신.
	QueryPerformanceCounter(&m_CurTime);

	// 현재 시간과 과거 시간의 갭이 m_CpuTick을 넘을 경우 보정.
	if (m_CurTime.QuadPart - m_OldTime2.QuadPart > m_CpuTick.QuadPart)
	{
		// 현재 CPU 진동수를 새로 얻어온다.
		QueryPerformanceFrequency(&m_CpuTick);
		m_OldTime2 = m_CurTime;
	}

	m_fTime = float(m_CurTime.QuadPart - m_OldTime1.QuadPart) / m_CpuTick.QuadPart;
	m_OldTime1 = m_CurTime;
}
