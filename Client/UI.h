#pragma once
#include "UserInterface.h"
class CUI :
	public CUserInterface
{
public:
	CUI();
	virtual ~CUI();

	// CUserInterface을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	int		m_iHp = 0;
};

