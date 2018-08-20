#pragma once
#include "BossIMP.h"
class CBossHalfIMP :
	public CBossIMP
{
public:
	CBossHalfIMP();
	virtual ~CBossHalfIMP();

	// CBossIMP을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	bool m_bPattern1 = false;
	bool m_bPattern2 = false;
};

