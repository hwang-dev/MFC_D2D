#include "stdafx.h"
#include "UIObserver.h"


CUIObserver::CUIObserver()
{
}


CUIObserver::~CUIObserver()
{
}

void CUIObserver::Update(int iMessage, void * pData)
{
	list<void*>* pDataLst = CDataSubejct::GetInstance()->GetDataLst(iMessage);

	if (pDataLst != nullptr) {
		auto& iter_find = find(pDataLst->begin(), pDataLst->end(), pData);

		if (iter_find == pDataLst->end()) {
			return;
		}

		switch (iMessage) {
		case PLAYER_DATA:
			m_tData = *reinterpret_cast<DATA*>(*iter_find);
			break;
		default:
			break;
		}
	}
}
