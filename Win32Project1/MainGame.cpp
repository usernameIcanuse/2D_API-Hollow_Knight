#include "stdafx.h"
#include "MainGame.h"
#include"ObjMgr.h"
#include"Player.h"
#include"Sword.h"
#include "Item.h"
#include"AbstractFactory.h"
#include "KeyMgr.h"
#include"CollisionMgr.h"
#include"SoundMgr.h"
#include"ScrollMgr.h"
#include"LineMgr.h"
#include "Goal.h"
#include "BmpMgr.h"
#include "SceneMgr.h"
#include "KeyMgr.h"

bool		g_bStopFrame = false;


CMainGame::CMainGame():m_iTime(0)
{
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_DC = GetDC(g_hWnd);


	m_dwTime = GetTickCount();

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Stage/Stage1/Stage1.bmp", L"Stage1_Back");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Stage/Stage2/Stage2.bmp", L"Stage2_Back");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Stage/Stage3/Stage3.bmp", L"Stage3_Back");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Stage/Stage4/Stage4.bmp", L"Stage4_Back");


	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BackGround.bmp", L"BackGround");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/MainMenu.bmp", L"Logo");
	
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Fly_Right.bmp", L"Fly_Right");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Fly_Left.bmp", L"Fly_Left");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Husk_Left.bmp", L"Husk_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Husk_Right.bmp", L"Husk_Right");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/SemiBoss_Left.bmp", L"SemiBoss_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/SemiBoss_Right.bmp", L"SemiBoss_Right");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/HuskHusband_Left.bmp", L"HuskHusband_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/HuskHusband_Right.bmp", L"HuskHusband_Right");
	
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Effect.bmp", L"Attack_Effect");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Effect_Up.bmp", L"Attack_Up");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Effect_Down.bmp", L"Attack_Down");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/Monster/Effect1_Left.bmp", L"Effect1Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/Monster/Effect1_Right.bmp", L"Effect1Right");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/Monster/Effect2_Left.bmp", L"Effect2Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/Monster/Effect2_Right.bmp", L"Effect2Right");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/Monster/Boss_Effect.bmp", L"BossEffect");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/ThornEffect.bmp", L"ThornEffect");
	
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/HP/HP_Effect.bmp", L"Hp");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/HP/HP_Guage.bmp", L"Player_HP_Guage");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Coin/0.bmp", L"0");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Coin/1.bmp", L"1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Coin/2.bmp", L"2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Coin/3.bmp", L"3");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Coin/4.bmp", L"4");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Coin/5.bmp", L"5");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Coin/6.bmp", L"6");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Coin/7.bmp", L"7");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Coin/8.bmp", L"8");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Coin/9.bmp", L"9");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Coin/NULL_NUM.bmp", L"NULL");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/HP/HPHealEffect.bmp", L"Heal");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Coin/Coin.bmp", L"Coin");

	CKeyMgr::Get_Instance()->Initialize();
	CSceneMgr::Get_Instance()->Initialize();
	CSoundMgr::Get_Instance()->Initialize();
	CSceneMgr::Get_Instance()->Scene_Change(SC_LOGO);
	CScrollMgr::Get_Instance()->Initialize();

}

void CMainGame::Update()
{


	if (!g_bStopFrame)
	{
		CKeyMgr::Get_Instance()->Update();
		CSceneMgr::Get_Instance()->Update();
	}
	
	if (g_bStopFrame)
		++m_iTime;

}


void CMainGame::Late_Update()
{
	if(!g_bStopFrame)
		CSceneMgr::Get_Instance()->Late_Update();

}


void CMainGame::Render()
{
	ShowCursor(false);
	++m_iFPS;

	if (m_dwTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);

		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwTime = GetTickCount();
	}

	HDC	hBackDC = CBmpMgr::Get_Instance()->Find_Image(L"BackGround");
	

	BitBlt(m_DC,0, 0, WINCX, WINCY, hBackDC, 0, 0, SRCCOPY);

	if (!g_bStopFrame)
	{
		CSceneMgr::Get_Instance()->Render(hBackDC);
	}
	if (10 < m_iTime)
	{
		g_bStopFrame = false;
		m_iTime = 0;
	}
}

void CMainGame::Release()
{
	CSoundMgr::Get_Instance()->Destroy_Instance();
	CLineMgr::Get_Instance()->Destroy_Instance();
	CBmpMgr::Get_Instance()->Destroy_Instance();
	CKeyMgr::Get_Instance()->Destroy_Instance();
	CScrollMgr::Get_Instance()->Destroy_Instance();
	CSceneMgr::Get_Instance()->Destroy_Instance();

	ReleaseDC(g_hWnd, m_DC);
}