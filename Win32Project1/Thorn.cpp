#include "stdafx.h"
#include "Thorn.h"
#include "stdafx.h"
#include "ScrollMgr.h"
#include "Player.h"
#include "ObjMgr.h"
#include "SoundMgr.h"


CThorn::CThorn()
{
}


CThorn::~CThorn()
{
}

void CThorn::Initialize()
{

	eID = OBJ_THORN;
	m_bDeath = false;
}

void CThorn::Render(HDC hdc)
{



}

void CThorn::Late_Update()
{
}

void CThorn::Release()
{
}

int CThorn::Update()
{
	Update_Rect();
	return OBJ_NOEVENT;
}

void CThorn::Collision()
{
}

void CThorn::Collision(CObj * Obj)
{
	if (OBJ_SWORD == Obj->Get_OBJID())
	{

		srand(unsigned(time(NULL)));
		if(rand()%2 == 1)
			CSoundMgr::Get_Instance()->PlaySound(L"breakable_pole_hit_1.wav", THORN1, 0.7f);
		else
			CSoundMgr::Get_Instance()->PlaySound(L"breakable_pole_hit_2.wav", THORN1, 0.7f);

		static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER)->front())->Reflect(-13.f);

	}
}
