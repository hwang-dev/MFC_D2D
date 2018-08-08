#pragma once
#include "Obj.h"

/* Player √ﬂªÛ√˛ */
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

public:
	PLAYER_DIR GetPlayerDir() { return m_ePlayerDir; }
	PLAYER_STANCE GetPlayerStance() { return m_eCurStance; }
	CObj*& GetCurGun() { return m_pCurGun; }

private:
	void PlayerMove();
	void IsOffSet();
	void StanceChange();
	void PlayAnimation();
	void PlayerDodge();
	void MakeBullet();
	void ChangeWeapon();

private:
	PLAYER_DIR		m_ePlayerDir;
	PLAYER_STANCE	m_eCurStance;
	PLAYER_STANCE	m_ePreStance;
	
	float			m_fAnimSpeed;
	float			m_fDodgePow;
	bool			m_bIsDodge;
	float			m_fDodgeTime;
	CObj*			m_pCurGun;
	int				m_iHp;
};

