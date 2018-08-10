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

	/* 타일 <> 오브젝트 충돌 */
	static void CollisionTile(vector<TILE*>& dstLst, OBJLIST& srcLst);
	static void CollisionTile(vector<TILE*> dstLst, CObj* pPlayer);

private:
	static bool CheckTile(CObj* pPlayer, TILE* pTile, float* pMoveX, float* pMoveY);
	static bool CheckRect(CObj* pDst, CObj* pSrc, float* pMoveX, float* pMoveY);
	static bool CheckSphere(CObj* pDst, CObj* pSrc);
};

