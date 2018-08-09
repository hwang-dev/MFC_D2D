#include "stdafx.h"
#include "CollisionMgr.h"
#include "Obj.h"

CCollisionMgr::CCollisionMgr() {}


CCollisionMgr::~CCollisionMgr() {}

void CCollisionMgr::CollisionRect(OBJLIST & dstLst, OBJLIST & srcLst)
{
	for (CObj*& pDst : dstLst) {
		for (CObj*& pSrc : srcLst) {
			
			RECT rc = {};
			const RECT& dstRect = pDst->GetRect();
			const RECT& srcRect = pSrc->GetRect();

			if (IntersectRect(&rc, &dstRect, &srcRect)) {

			}
		}
	}
}

void CCollisionMgr::CollisionRectEX(OBJLIST & dstLst, OBJLIST & srcLst)
{
	// 밀려날 거리
	float fMoveX = 0.f, fMoveY = 0.f;

	for (CObj*& pDst : dstLst) {
		for (CObj*& pSrc : srcLst) {
			if (CheckRect(pDst, pSrc, &fMoveX, &fMoveY)) {
				if (fMoveX > fMoveY) {
					float fX = pSrc->GetInfo().vPos.x;
					float fY = pSrc->GetInfo().vPos.y;

					if (pDst->GetInfo().vPos.y > fY) {
						fMoveY *= -1.f;
					}
					pSrc->SetPos(D3DXVECTOR3(fX, fY + fMoveY, 0.f));
				}
				else {
					float fX = pSrc->GetInfo().vPos.x;
					float fY = pSrc->GetInfo().vPos.y;

					if (pDst->GetInfo().vPos.x > fX) {
						fMoveX *= -1.f;
					}
					pSrc->SetPos(D3DXVECTOR3(fX + fMoveX, fY, 0.f));
				}
			}
		}
	}
}

void CCollisionMgr::CollisionSphere(OBJLIST & dstLst, OBJLIST & srcLst)
{
	for (CObj*& pDst : dstLst) {
		for (CObj*& pSrc : srcLst) {

		}
	}
}

void CCollisionMgr::CollisionTile(CObj * pPlayer, vector<TILE*> dstLst)
{
	float fMoveX = 0.f, fMoveY = 0.f;

	for (auto& pTile : dstLst) {
		if (pTile->GetTileOption() == 1) {
			if (CheckTile(pPlayer, pTile, &fMoveX, &fMoveY)) {
				/* 깊이가 짧은 쪽으로 밀어냄 */
				if (fMoveX > fMoveY) {
					float fX = pPlayer->GetInfo().vPos.y;
					float fY = pPlayer->GetInfo().vPos.y;
					if (pTile->GetTilePos().y> fY) {
						fMoveY *= -1.f;
					}
					pPlayer->SetPos(D3DXVECTOR3(fX + CScrollMgr::GetScroll().x,
						(fY + fMoveY) + CScrollMgr::GetScroll().y,
						0.f));
				}
				else {
					float fX = pPlayer->GetInfo().vPos.x;
					float fY = pPlayer->GetInfo().vPos.x;

					if (pTile->GetTilePos().x > fX) {
						fMoveX *= -1.f;
					}
					pPlayer->SetPos(D3DXVECTOR3((fX + fMoveX) + CScrollMgr::GetScroll().x,
						fY + CScrollMgr::GetScroll().y,
						0.f));
				}
			}
		}
	}
}

bool CCollisionMgr::CheckTile(CObj * pPlayer, TILE * pTile, float * pMoveX, float * pMoveY)
{
	float fSumSizeX = (pPlayer->GetInfo().vSize.x + pTile->GetTileSize().x) * 0.5f;
	float fSumSizeY = (pPlayer->GetInfo().vSize.y + pTile->GetTileSize().y) * 0.5f;

	float fDistX = fabs(pPlayer->GetInfo().vPos.x - pTile->GetTilePos().x);
	float fDistY = fabs(pPlayer->GetInfo().vPos.y - pTile->GetTilePos().y);

	if (fSumSizeX > fDistX && fSumSizeY > fDistY) {
		*pMoveX = fSumSizeX - fDistX;
		*pMoveY = fSumSizeY - fDistY;

		return true;
	}

	return false;
}

bool CCollisionMgr::CheckRect(CObj * pDst, CObj * pSrc, float * pMoveX, float * pMoveY)
{
	float fSumSizeX = (pDst->GetInfo().vSize.x + pSrc->GetInfo().vSize.x) * 0.5f;
	float fSumSizeY = (pDst->GetInfo().vSize.y + pSrc->GetInfo().vSize.y) * 0.5f;

	float fDistX = fabs(pDst->GetInfo().vPos.x - pSrc->GetInfo().vPos.x);
	float fDistY = fabs(pDst->GetInfo().vPos.y - pSrc->GetInfo().vPos.y);

	if (fSumSizeX > fDistX && fSumSizeY > fDistY) {
		*pMoveX = fSumSizeX - fDistX;
		*pMoveY = fSumSizeY - fDistY;

		return true;
	}

	return false;
}

bool CCollisionMgr::CheckSphere(CObj * pDst, CObj * pSrc)
{
	// 반지름의 합
	float fSumRad = (pDst->GetInfo().vSize.x + pSrc->GetInfo().vSize.x) * 0.5f;

	// 두 원의 거리
	float fDist = D3DXVec3Length(&(pDst->GetInfo().vPos - pSrc->GetInfo().vPos));

	return (fSumRad >= fDist);
}
