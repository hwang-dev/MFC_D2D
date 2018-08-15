#pragma once
#include "UserInterface.h"
class CMoneyUI :
	public CUserInterface
{
public:
	CMoneyUI();
	virtual ~CMoneyUI();

	// CUserInterface을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	int		m_iMoney = 0;
};

