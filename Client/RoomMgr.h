#pragma once
class CRoomMgr
{
	DECLARE_SINGLETON(CRoomMgr)

private:
	CRoomMgr();
	~CRoomMgr();

public:
	void Initialize();
	void Update();

private:
	BYTE	m_byPlayerRoomNumber = 0;

	bool	m_bEnterRoom1 = false;
	bool	m_bEnterRoom2 = false;
	bool	m_bEnterRoom3 = false;
};

