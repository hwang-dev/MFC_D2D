#include "stdafx.h"
#include "BossIMP.h"


CBossIMP::CBossIMP()
{
}


CBossIMP::~CBossIMP()
{
}

void CBossIMP::LateInit()
{
	if (m_bIsInit == false) {
		this->LateInit();
		m_bIsInit = true;
	}
}
