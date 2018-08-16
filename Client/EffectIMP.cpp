#include "stdafx.h"
#include "EffectIMP.h"


CEffectIMP::CEffectIMP()
{
}


CEffectIMP::~CEffectIMP()
{
}

void CEffectIMP::LateInit()
{
	if (!m_bIsInit) {
		this->LateInit();
		m_bIsInit = true;
	}
}
