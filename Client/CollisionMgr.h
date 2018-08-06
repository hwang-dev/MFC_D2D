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

private:
	static bool CheckRect(CObj* pDst, CObj* pSrc, float* pMoveX, float* pMoveY);
};

