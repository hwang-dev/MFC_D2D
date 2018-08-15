#pragma once

class CObj;
class CObjMgr
{
	DECLARE_SINGLETON(CObjMgr)

private:
	CObjMgr();
	~CObjMgr();

public:
	void AddObject(CObj* pObject, OBJID eID);
	void Update();
	void LateUpdate();
	void Render();
	void Release();

	CObj* GetPlayer() { return m_ObjLst[OBJ_PLAYER].front(); }
	OBJLIST& GetBulletList() { return m_ObjLst[OBJ_MOSTERBULLET]; }
private:
	OBJLIST	m_ObjLst[OBJ_END];
};

