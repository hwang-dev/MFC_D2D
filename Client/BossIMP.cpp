#include "stdafx.h"
#include "BossIMP.h"


BossIMP::BossIMP()
{
}


BossIMP::~BossIMP()
{
}

void BossIMP::LateInit()
{
	if (m_bIsInit == false) {
		this->LateInit();
		m_bIsInit = true;
	}
}
