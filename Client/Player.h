#pragma once
#include "Obj.h"

/* Player Ãß»óÃþ */
class CPlayer :
	public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();


public:
	// CObjÀ»(¸¦) ÅëÇØ »ó¼ÓµÊ
	virtual HRESULT Initialize() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	void SetRoomNumber(BYTE& byRoom) { m_tInfo.byRoomNum = byRoom; }
	PLAYER_DIR GetPlayerDir() { return m_ePlayerDir; }
	PLAYER_STANCE GetPlayerStance() { return m_eCurStance; }
	CObj*& GetCurGun() { return m_pCurGun; }
	void SetPlayerHp() 
	{ 
		m_tData.iHp--; 
		CDataSubejct::GetInstance()->Notify(PLAYER_DATA, &m_tData);
	}

private:
	void PlayerMove();
	void IsOffSet();
	void StanceChange();
	void PlayAnimation();
	void PlayerDodge();
	void MakeBullet();
	void ChangeWeapon();
	void MakeStep();

private:
	PLAYER_DIR		m_ePlayerDir;
	PLAYER_STANCE	m_eCurStance;
	PLAYER_STANCE	m_ePreStance;
	
	float			m_fAnimSpeed;
	float			m_fDodgePow;
	bool			m_bIsDodge;
	float			m_fDodgeTime;
	CObj*			m_pCurGun;

	DATA			m_tData;
	float			m_fStepTime = 0.f;
	bool			m_bIsMove = false;

};

