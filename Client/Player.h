#pragma once
#include "Obj.h"

/* Player √ﬂªÛ√˛ */
class CPlayerIMP;
class CPlayer :
	public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();


public:
	// CObj¿ª(∏¶) ≈Î«ÿ ªÛº”µ 
	virtual HRESULT Initialize() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	void PlayerMove();
	void IsOffSet();
	void StanceChange();
	void PlayAnimation();
	void PlayerDodge();

private:
	PLAYER_DIR		m_ePlayerDir;
	PLAYER_STANCE	m_eCurStance;
	PLAYER_STANCE	m_ePreStance;
	wstring			m_wstrStateKey;
	float			m_fAnimSpeed;
	float			m_fDodgePow;
	bool			m_bIsDodge;
};

