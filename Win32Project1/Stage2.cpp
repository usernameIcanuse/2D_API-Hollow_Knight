#include "stdafx.h"
#include "Stage2.h"
#include "LineMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "Player.h"
#include "SceneMgr.h"
#include "Husk.h"
#include "HuskHusband.h"
#include"Fly.h"

CStage2::CStage2():m_bFirst(true)
{
}

CStage2::~CStage2()
{
	Release();
}

void CStage2::Initialize()
{
	//1470,3790
	if (m_bFirst)
	{
		m_pMonster.push_back(CAbstractFactory<CHusk>::Create(700.f, 790.f, 5219, 1000));
		m_pMonster.push_back(CAbstractFactory<CFly>::Create(700.f, 800.f, 5219, 1000));
		m_pMonster.push_back(CAbstractFactory<CHusk>::Create(900.f, 790.f, 5219, 1000));
		m_pMonster.push_back(CAbstractFactory<CFly>::Create(750.f, 665.f, 5219, 1000));
		m_pMonster.push_back(CAbstractFactory<CHuskHusband>::Create(800.f, 780.f, 5219, 1000));
		m_pMonster.push_back(CAbstractFactory<CFly>::Create(790.f, 800.f, 5219, 1000));

		m_pMonster.push_back(CAbstractFactory<CHuskHusband>::Create(4570.f, 780.f, 5219, 1000));
		m_pMonster.push_back(CAbstractFactory<CHuskHusband>::Create(4970.f, 780.f, 5219, 1000));

		m_bFirst = false;
	}
		int len = m_pMonster.size();
		for (int i = 0; i < len; ++i)
		{
			CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER, m_pMonster.front());
			m_pMonster.pop_front();
		}
		m_pMonster.clear();
	
	//CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER, CAbstractFactory<CSemiBoss>::Create(3790.f,1380.f));

	//CScrollMgr::Get_Instance()->Set_Target(CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER)->front());

	CLineMgr::Get_Instance()->Load_Data2();
	CObjMgr::Get_Instance()->Load_Data2(OBJ_WALL); 
	CObjMgr::Get_Instance()->Load_Data2(OBJ_THORN);

}

void CStage2::Update()
{
	CLineMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();
}

void CStage2::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
	CScrollMgr::Get_Instance()->Late_Update();
	CScrollMgr::Get_Instance()->Scroll_Lock(5219, 1000);

	if (5219.f < CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER)->front()->Get_Info().fX)
	{
		CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER)->front()->Set_Pos(30.f, 1280.f);

		auto& iter = CObjMgr::Get_Instance()->Get_List(OBJ_MONSTER)->begin();
		auto& iterEnd = CObjMgr::Get_Instance()->Get_List(OBJ_MONSTER)->end();
		for (; iter != iterEnd; ++iter)
		{
			m_pMonster.push_back(*iter);
		}
		CObjMgr::Get_Instance()->Get_List(OBJ_MONSTER)->clear();


		CObjMgr::Get_Instance()->Delete_OBJ(OBJ_WALL);
		CObjMgr::Get_Instance()->Delete_OBJ(OBJ_THORN);
	
		CLineMgr::Get_Instance()->Release();
		CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE3);
	}

	else if (0.f > CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER)->front()->Get_Info().fX)
	{
		CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER)->front()->Set_Pos(2340.f, 1070.f);


		CObjMgr::Get_Instance()->Delete_OBJ(OBJ_WALL);
		CObjMgr::Get_Instance()->Delete_OBJ(OBJ_THORN);
		CObjMgr::Get_Instance()->Delete_OBJ(OBJ_MONSTER);
		CLineMgr::Get_Instance()->Release();
		CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE4);
	}
}

void CStage2::Render(HDC hdc)
{


	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Stage2_Back");

	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	BitBlt(hdc, iScrollX, iScrollY, 5219, 1000, hMemDC, 0, 0, SRCCOPY);



	//CLineMgr::Get_Instance()->Render(hdc);
	CObjMgr::Get_Instance()->Render(hdc);
}

void CStage2::Release(void)
{
	auto& iter = m_pMonster.begin();

	for (; iter != m_pMonster.end();)
	{
		SAFE_DELETE(*iter);
		iter = m_pMonster.erase(iter);
	}

	CObjMgr::Get_Instance()->Delete_OBJ(OBJ_WALL);
	CObjMgr::Get_Instance()->Delete_OBJ(OBJ_THORN);
	CObjMgr::Get_Instance()->Delete_OBJ(OBJ_MONSTER);
	CLineMgr::Get_Instance()->Release();
}
