#include "stdafx.h"
#include "Stage1.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "AbstractFactory.h"
#include "SceneMgr.h"
#include "ScrollMgr.h"
#include "Player.h"
#include "Fly.h"
#include "Goal.h"
#include "Husk.h"
#include"HuskHusband.h"

CStage1::CStage1()
{
}


CStage1::~CStage1()
{
	Release();
}

void CStage1::Initialize()
{


	CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER, CAbstractFactory<CFly>::Create(100.f, 500.f, 3625, 1000));
	CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER, CAbstractFactory<CFly>::Create(50.f, 600.f, 3625, 1000));
	CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER, CAbstractFactory<CFly>::Create(3000.f, 700.f, 3625, 1000));
	CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER, CAbstractFactory<CFly>::Create(2700.f, 750.f, 3625, 1000));
	CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER, CAbstractFactory<CFly>::Create(70.f, 700.f, 3625, 1000));
	//CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER, CAbstractFactory<CFly>::Create(350.f, 500.f, 3625, 1000));
	//CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER, CAbstractFactory<CFly>::Create(3500.f, 500.f, 3625, 1000));
	CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER, CAbstractFactory<CFly>::Create(2600.f, 600.f, 3625, 1000));

	CObjMgr::Get_Instance()->AddObject(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create(2200,100.f));
	//CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER, CAbstractFactory<CFly>::Create(3000.f,500.f));
	/*

	CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER, CAbstractFactory<CBug>::Create(1600.f, 1290.f));

	
	CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER, CAbstractFactory<CFly>::Create(2500.f, 1000.f));
	CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER, CAbstractFactory<CFly>::Create(3000.f, 700.f));
	CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER, CAbstractFactory<CFly>::Create(3300.f, 900.f));*/


	CLineMgr::Get_Instance()->Load_Data1();
	CScrollMgr::Get_Instance()->Set_Target(CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER)->front());
	CObjMgr::Get_Instance()->Load_Data1(OBJ_WALL);
	
}

void CStage1::Update()
{
	
	CLineMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();
}

void CStage1::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
	CScrollMgr::Get_Instance()->Late_Update();
	CScrollMgr::Get_Instance()->Scroll_Lock(3625, 1000);

	if (1000.f < CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER)->front()->Get_Info().fY)
	{		
		CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER)->front()->Set_Pos(1950.f, 100.f);
		CObjMgr::Get_Instance()->Delete_OBJ(OBJ_WALL);
		CObjMgr::Get_Instance()->Delete_OBJ(OBJ_MONSTER);
		CLineMgr::Get_Instance()->Release();
		CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE2);


	}
	
}

void CStage1::Render(HDC hdc)
{
	
	
	
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Stage1_Back");

	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	BitBlt(hdc, iScrollX, iScrollY, 3625, 1000 ,hMemDC, 0, 0, SRCCOPY);

	

	//CLineMgr::Get_Instance()->Render(hdc);
	CObjMgr::Get_Instance()->Render(hdc);
	
	
}

void CStage1::Release(void)
{
	CObjMgr::Get_Instance()->Delete_OBJ(OBJ_WALL);
	CObjMgr::Get_Instance()->Delete_OBJ(OBJ_MONSTER);
	CLineMgr::Get_Instance()->Release();
}
