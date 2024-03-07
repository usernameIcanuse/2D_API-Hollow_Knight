#include "stdafx.h"
#include "Stage4.h"
#include "LineMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "Player.h"
#include "Boss.h"


CStage4::CStage4()
{
}

CStage4::~CStage4()
{
	Release();
}

void CStage4::Initialize()
{
	//1470,3790

	//CObjMgr::Get_Instance()->AddObject(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create(100.f, 850.f));
	CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER, CAbstractFactory<CBoss>::Create(1000.f,1000.f));

	//CScrollMgr::Get_Instance()->Set_Target(CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER)->front());

	CLineMgr::Get_Instance()->Load_Data4();
	//CObjMgr::Get_Instance()->Load_Data4(OBJ_WALL);
	//CObjMgr::Get_Instance()->Load_Data3(OBJ_THORN);

}

void CStage4::Update()
{
	CLineMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();
}

void CStage4::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
	CScrollMgr::Get_Instance()->Late_Update();
	CScrollMgr::Get_Instance()->Scroll_Lock(3022, 1215);
}

void CStage4::Render(HDC hdc)
{


	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Stage4_Back");

	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	BitBlt(hdc, iScrollX, iScrollY, 3022,1215, hMemDC, 0, 0, SRCCOPY);



	//CLineMgr::Get_Instance()->Render(hdc);
	CObjMgr::Get_Instance()->Render(hdc);
}

void CStage4::Release(void)
{
	CObjMgr::Get_Instance()->Delete_OBJ(OBJ_WALL);
	CObjMgr::Get_Instance()->Delete_OBJ(OBJ_MONSTER);
	CLineMgr::Get_Instance()->Release();
}
