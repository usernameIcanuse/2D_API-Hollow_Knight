#include "stdafx.h"
#include "Wall.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"

CWall::CWall()
{
}


CWall::~CWall()
{
}

void CWall::Initialize()
{

	eID = OBJ_WALL;
}

void CWall::Render(HDC hdc)
{
	
}

void CWall::Late_Update()
{
}

void CWall::Release()
{
}

int CWall::Update()
{
	Update_Rect();
	return OBJ_NOEVENT;
}

void CWall::Collision()
{
}

void CWall::Collision(CObj * Obj)
{
}
