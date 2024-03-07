#pragma once
#include"Obj.h"

class CCollisionMgr
{
public:
	static void	Collision_Rect(list<CObj*>	Player, list<CObj*>	Wall);
//	static void Collision_Sphere(list<CObj*> Dest, list<CObj*> Sour);
	//static	bool Check_Sphere(CObj*	pDest, CObj* pSour);
};

