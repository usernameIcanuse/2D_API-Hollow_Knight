#include "stdafx.h"
#include "Goal.h"
#include "ScrollMgr.h"
#include "SceneMgr.h"

#include "BmpMgr.h"

CGoal::CGoal()
{
}

CGoal::~CGoal()
{
}

void CGoal::Initialize()
{
	eID = OBJ_GOAL;
}

void CGoal::Render(HDC hdc)
{
	
}

void CGoal::Late_Update()
{
}

void CGoal::Release()
{
}

int CGoal::Update()
{
	Update_Rect();

	return OBJ_NOEVENT;
}

void CGoal::Collision()
{
}

void CGoal::Collision(CObj* Obj)
{
	if (OBJ_PLAYER == Obj->Get_OBJID())
	{
		if (m_tRect.left < Obj->Get_Info().fX)
		{
			if (SC_STAGE4 == CSceneMgr::Get_Instance()->Get_Scene())
				CSceneMgr::Get_Instance()->Scene_Change(SC_LOGO);
			else
				CSceneMgr::Get_Instance()->Scene_Change(SCENEID((int)(CSceneMgr::Get_Instance()->Get_Scene()) + 1));

		}
	}
}
