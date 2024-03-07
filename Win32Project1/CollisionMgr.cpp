#include "stdafx.h"
#include "CollisionMgr.h"


void CCollisionMgr::Collision_Rect(list<CObj*> Player, list<CObj*> Wall)
{
	RECT	rc;

	for (auto& DestIter : Player)
	{
		for (auto& SourIter : Wall)
		{
			if (IntersectRect(&rc, &DestIter->Get_Rect(), &SourIter->Get_Rect()))
			{
					
					DestIter->Collision(SourIter);
					SourIter->Collision(DestIter);
				
				
			}
			else
			{//범위안에 들어오는지 확인
				if (OBJ_MONSTER == SourIter->Get_OBJID() && OBJ_PLAYER == DestIter->Get_OBJID())
				{
					SourIter->Collision(DestIter);
				}
			}
		
		}
	}
}

//void CCollisionMgr::Collision_Sphere(list<CObj*> Dest, list<CObj*> Sour)
//{
//	for (auto& DestIter : Dest)
//	{
//		for (auto& SourIter : Sour)
//		{
//			if (Check_Sphere(DestIter, SourIter))
//			{
//				DestIter->Collision();
//				SourIter->Collision();
//			}
//		}
//	}
//}
//
//
//bool CCollisionMgr::Check_Sphere(CObj*	pDest, CObj* pSour)
//{
//	float fWidth = fabs(pDest->Get_Info().fX - pSour->Get_Info().fX);
//	float fHeight = fabs(pDest->Get_Info().fY - pSour->Get_Info().fY);
//
//	float fDiagonal = sqrtf(fWidth*fWidth + fHeight * fHeight);
//
//	float fRadius = (pDest->Get_Info().fCX + pSour->Get_Info().fCX)*0.5f;
//
//	return fRadius > fDiagonal;
//}
