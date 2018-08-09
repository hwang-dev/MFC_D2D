#pragma once

class CObj;
class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

public:
	static void CollisionRect(OBJLIST& dstLst, OBJLIST& srcLst);
	static void CollisionRectEX(OBJLIST& dstLst, OBJLIST& srcLst);
	static void CollisionSphere(OBJLIST& dstLst, OBJLIST& srcLst);
	static void CollisionTile(CObj* pPlayer, vector<TILE*> dstLst);

private:
	static bool CheckRect(CObj* pDst, CObj* pSrc, float* pMoveX, float* pMoveY);
	static bool CheckSphere(CObj* pDst, CObj* pSrc);
};

