#include "stdafx.h"
#include "Stage3.h"
#include "LineMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "Player.h"
#include "SceneMgr.h"
#include "SoundMgr.h"
#include "SemiBoss.h"
#include "Key.h"


CStage3::CStage3()
{
}

CStage3::~CStage3()
{
	Release();
}

void CStage3::Initialize()
{
	//1470,3790

	//CObjMgr::Get_Instance()->AddObject(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create(100.f, 850.f));
	CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER, CAbstractFactory<CSemiBoss>::Create(2100.f,1140.f));
	CObjMgr::Get_Instance()->AddObject(OBJ_ITEM, CAbstractFactory<CKey>::Create(1400.f, 300.f));

	//CScrollMgr::Get_Instance()->Set_Target(CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER)->front());
	//CSoundMgr::Get_Instance()->PlaySound(L"dirtmouth_wind_loop_a.wav",SOUND_WIND,0.3f);
	CLineMgr::Get_Instance()->Load_Data3();
	CObjMgr::Get_Instance()->Load_Data3(OBJ_WALL);
	CObjMgr::Get_Instance()->Load_Data3(OBJ_THORN);

}

void CStage3::Update()
{
	CLineMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();
	CSoundMgr::Get_Instance()->PlaySound(L"dirtmouth_wind_loop_a.wav", SOUND_WIND, 0.5f);
}

void CStage3::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
	CScrollMgr::Get_Instance()->Late_Update();
	CScrollMgr::Get_Instance()->Scroll_Lock(2721, 1600);

	if (0.f > CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER)->front()->Get_Info().fX)
	{
		CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER)->front()->Set_Pos(5200.f,400.f);
		CObjMgr::Get_Instance()->Delete_OBJ(OBJ_WALL);
		CObjMgr::Get_Instance()->Delete_OBJ(OBJ_THORN);
		CObjMgr::Get_Instance()->Delete_OBJ(OBJ_MONSTER);
		CLineMgr::Get_Instance()->Release();
		CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE2);
	}
}

void CStage3::Render(HDC hdc)
{


	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Stage3_Back");

	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	BitBlt(hdc, iScrollX, iScrollY, 2721, 1600, hMemDC, 0, 0, SRCCOPY);



	//CLineMgr::Get_Instance()->Render(hdc);
	CObjMgr::Get_Instance()->Render(hdc);
}

void CStage3::Release(void)
{
	CObjMgr::Get_Instance()->Delete_OBJ(OBJ_WALL);
	CObjMgr::Get_Instance()->Delete_OBJ(OBJ_THORN);
	CObjMgr::Get_Instance()->Delete_OBJ(OBJ_MONSTER);
	CLineMgr::Get_Instance()->Release();
}
