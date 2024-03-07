#include "stdafx.h"
#include "Player.h"
#include "Sword.h"
#include "KeyMgr.h"
#include"AbstractFactory.h"
#include "ScrollMgr.h"
#include"LineMgr.h"
#include"ObjMgr.h"
#include"BmpMgr.h"
#include "SceneMgr.h"
#include "Hp.h"
#include "HpBar.h"
#include "Heal.h"
#include "Item.h"
#include "SoundMgr.h"
#include "Number.h"
#include "Dash.h"
#include "Damaged.h"


float		g_fSound = 0.5f;
CPlayer::CPlayer():m_pHeal(nullptr)
{
}


CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	CObjMgr::Get_Instance()->AddObject(OBJ_SWORD, CAbstractFactory<CSword>::Create());
	CObjMgr::Get_Instance()->Get_List(OBJ_SWORD)->front()->Set_Target(this);
	CObjMgr::Get_Instance()->AddObject(OBJ_HPBAR, CAbstractFactory<CHpBar>::Create());
	CObjMgr::Get_Instance()->AddObject(OBJ_HP, CAbstractFactory<CHp>::Create(150.f, 60.f));
	CObjMgr::Get_Instance()->AddObject(OBJ_HP, CAbstractFactory<CHp>::Create(190.f, 60.f));
	CObjMgr::Get_Instance()->AddObject(OBJ_HP, CAbstractFactory<CHp>::Create(230.f, 60.f));
	CObjMgr::Get_Instance()->AddObject(OBJ_HP, CAbstractFactory<CHp>::Create(270.f, 60.f));
	CObjMgr::Get_Instance()->AddObject(OBJ_HP, CAbstractFactory<CHp>::Create(310.f, 60.f));

	
	CObjMgr::Get_Instance()->AddObject(OBJ_NUMBER, CAbstractFactory<CNumber>::Create(170.f, 100.f));
	CObjMgr::Get_Instance()->AddObject(OBJ_NUMBER, CAbstractFactory<CNumber>::Create(180.f, 100.f));
	CObjMgr::Get_Instance()->AddObject(OBJ_NUMBER, CAbstractFactory<CNumber>::Create(190.f, 100.f));

	static_cast<CNumber*>(CObjMgr::Get_Instance()->Get_List(OBJ_NUMBER)->front())->Change_Num(0);
	
	m_iCoin = 0;

	m_pHeal = new CHeal;
	m_pHeal->Initialize();



	m_tInfo.fCX = 35.f;
	m_tInfo.fCY = 75;

	m_tImageInfo.fCX = 105.f;
	m_tImageInfo.fCY = 105.f;

	m_fSpeed.fX = 0.f;
	m_fSpeed.fY = 0.f;

	m_fSpeed.fCY = 0.65f;
	m_fSpeed.fCX = 0.0f;
	m_bJump = false;
	m_bJumpMotion = false;
	m_iJumpcount = 0;

	m_bDashMotion = false;


	m_bAttackMotion = false;

	m_bLand = false;
	m_bLandMotion = false;
	eID = OBJ_PLAYER;

	m_iCoin = 0;
	eDir = RIGHT;

	CScrollMgr::Get_Instance()->Set_Target(this);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_Left.bmp", L"Player_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_Right.bmp", L"Player_Right");
	
	m_eCurState = ST_IDLE;
	m_ePreState = ST_END;
	m_pFrameKey = L"Player_Right";

	m_tFrame.iFrameMotion = 0;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 7;
	m_tFrame.dwFrameSpeed = 70;
	m_tFrame.dwFrameTime = GetTickCount();

	m_iHP = 5;
	m_bFreeze = false;
	m_bFreezeTime = 0;
}

void CPlayer::Render(HDC hdc)
{
	
	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);



	GdiTransparentBlt(hdc,
		(int)m_tImageRect.left + CScrollMgr::Get_Instance()->Get_ScrollX(),
		(int)m_tImageRect.top + CScrollMgr::Get_Instance()->Get_ScrollY(),
		(int)m_tImageInfo.fCX,
		(int)m_tImageInfo.fCY,
		hMemDC,
		m_tFrame.iFrameMotion *(int)m_tImageInfo.fCX,
		m_tFrame.iFrameStart*(int)m_tImageInfo.fCY,
		(int)m_tImageInfo.fCX,
		(int)m_tImageInfo.fCY,
		RGB(62, 62, 62));

	m_pHeal->Render(hdc);

}

int  CPlayer::Update()
{
	
		if (m_bDashMotion)
		{
			m_eCurState = ST_DASH;
			
			m_tInfo.fX += m_fSpeed.fX;
			m_fSpeed.fX += m_fSpeed.fCX;


			if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
			{			
				m_eCurState = ST_IDLE;
				m_bDashMotion = false;
			}
		}
		else if (m_bAttackMotion)
		{
			if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
			{
				m_eCurState = ST_IDLE;
				m_bAttackMotion = false;
			}
		}
		else if (m_bLandMotion || m_bJumpMotion)
		{
			if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
			{
				m_eCurState = ST_IDLE;
				m_bLandMotion = false;
				m_bJumpMotion = false;
			}
		}
	
	if(m_bFreeze)
	{
		++m_bFreezeTime;
		m_tInfo.fX += m_fSpeed.fX;
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
		{
			if (!m_bLand)
			{
				m_eCurState = ST_JUMP_FALL;
			}
			m_fSpeed.fX = 0;
			
		}
		
		if (120 < m_bFreezeTime)
		{
			m_bFreeze = false;
			m_bFreezeTime = 0;
		}
	}
	
		if (!m_bDashMotion )
		{
			if(ST_ATTACKED != m_eCurState)
				Key_Input();
			jumping();
		}

	if(ST_ATTACKED !=m_eCurState)
		Motion_Change();
	
	Move_Frame();
	Update_Rect();

	m_pHeal->Update();


	return OBJ_NOEVENT;
}



void CPlayer::jumping()
{
	if (m_bJump || !m_bLand )
	{
		m_tInfo.fY += m_fSpeed.fY;
		if(15.f > m_fSpeed.fY)
			m_fSpeed.fY += m_fSpeed.fCY;	
		if (!m_bFreeze && !m_bAttackMotion)
		{
			if (m_fSpeed.fY < -3.f)
				m_eCurState = ST_JUMP_START;

			else if (-3.f <= m_fSpeed.fY && 3.f > m_fSpeed.fY)
			{
				m_eCurState = ST_JUMP_HIGHEST;
				m_bJumpMotion = true;
			}
			else if (m_fSpeed.fY > 3.f)
			{
				m_eCurState = ST_JUMP_FALL;
			
			}
		}
		CSoundMgr::Get_Instance()->StopSound(SOUND_PLAYER_WALK);
	}
}

void	CPlayer::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case ST_IDLE:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.dwFrameSpeed = 90;
			m_tFrame.dwFrameTime = GetTickCount();
			CSoundMgr::Get_Instance()->StopSound(SOUND_PLAYER_WALK);
			break;

		case ST_WALK:
			m_tFrame.iFrameMotion = 1;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.dwFrameSpeed = 90;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ST_ATTACK:
			m_tFrame.iFrameMotion = 2;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.dwFrameSpeed = 70;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ST_ATTACK_UP:
			m_tFrame.iFrameMotion = 4;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.dwFrameSpeed = 70;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ST_ATTACK_DOWN:
			m_tFrame.iFrameMotion = 3;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.dwFrameSpeed = 70;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ST_JUMP_START:
			m_tFrame.iFrameMotion = 6;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.dwFrameSpeed = 70;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ST_JUMP_HIGHEST:
			m_tFrame.iFrameMotion = 7;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.dwFrameSpeed = 300;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ST_JUMP_FALL:
			m_tFrame.iFrameMotion = 8;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.dwFrameSpeed = 70;
			m_tFrame.dwFrameTime = GetTickCount();
		
			break;

		case ST_JUMP_LAND:
			m_tFrame.iFrameMotion = 9;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.dwFrameSpeed = 70;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ST_ATTACKED:
			m_tFrame.iFrameMotion = 5;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ST_DASH:
			m_tFrame.iFrameMotion = 10;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.dwFrameSpeed = 80;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CPlayer::Collision()
{

}

void CPlayer::Collision(CObj* Obj)
{
	if (OBJ_WALL == Obj->Get_OBJID())
	{
		if (m_tInfo.fX < Obj->Get_Rect().left)//왼쪽 충돌
		{

			float dx = m_tRect.right - Obj->Get_Rect().left;
			m_tInfo.fX -= dx;

		}
		else if (m_tInfo.fX > Obj->Get_Rect().right)//오른쪽 충돌
		{

			float dx = Obj->Get_Rect().right - m_tRect.left;
			m_tInfo.fX += dx;

		}
		else
		{
			if (m_tInfo.fY > Obj->Get_Rect().bottom)//아래 충돌
			{
			
				if (m_tRect.top < Obj->Get_Rect().bottom)
				{
					float dy = Obj->Get_Rect().bottom - m_tRect.top;
					m_tInfo.fY += dy;
				}
			}
			
		}
	}

	else if (OBJ_MONSTER == Obj->Get_OBJID() || OBJ_ATTACK == Obj->Get_OBJID())
	{
		if (!m_bFreeze&& !m_bDashMotion&&!Obj->Get_Death())
		{
			if (0 < m_iHP)
			{
				--m_iHP;
				auto&iter = CObjMgr::Get_Instance()->Get_List(OBJ_HP)->begin();
				for (int i = 0; i < m_iHP; ++i)
					++iter;
				static_cast<CHp*>(*iter)->Set_Off();
			}
				m_bFreeze = true;

				m_eCurState = ST_ATTACKED;
	
				Motion_Change();
				
				m_bLand = false;

				CObj*	temp = new CDamaged;
				temp->Set_Target(this);
				temp->Initialize();
				CObjMgr::Get_Instance()->AddObject(OBJ_EFFECT, temp);

			

			if (m_tInfo.fX < Obj->Get_Info().fX)//왼쪽 충돌
			{
				m_pFrameKey = L"Player_Right";
				m_fSpeed.fX = -7.f;m_fSpeed.fY = -10.f;
				m_tInfo.fY += m_fSpeed.fY;
			}
			else if (m_tInfo.fX > Obj->Get_Info().fX)//오른쪽 충돌
			{
				m_pFrameKey = L"Player_Left";
				m_fSpeed.fX = 7.f; m_fSpeed.fY = -10.f;
				m_tInfo.fY += m_fSpeed.fY;
			}
			else
			{
				
				if(m_tInfo.fX > Obj->Get_Info().fX)
					m_fSpeed.fY *= -0.8f;
				
			}

		}
	}
	else if (OBJ_THORN == Obj->Get_OBJID())
	{
		if (!m_bFreeze && !Obj->Get_Death())
		{
			if (0 < m_iHP)
			{

				--m_iHP;
				auto&iter = CObjMgr::Get_Instance()->Get_List(OBJ_HP)->begin();
				for (int i = 0; i < m_iHP; ++i)
					++iter;
				static_cast<CHp*>(*iter)->Set_Off();
				m_bFreeze = true;

				m_eCurState = ST_ATTACKED;

				m_bJump = true;
				m_bLand = false;
			}

			if (m_tInfo.fX < Obj->Get_Info().fX)//왼쪽 충돌
			{
				m_pFrameKey = L"Player_Right";
				m_fSpeed.fX = -7.f; m_fSpeed.fY = -10.f;
			}
			else if (m_tInfo.fX > Obj->Get_Info().fX)//오른쪽 충돌
			{
				m_pFrameKey = L"Player_Left";
				m_fSpeed.fX = 7.f; m_fSpeed.fY = -10.f;
			}
			else
			{
				if (m_tInfo.fX < Obj->Get_Info().fY)//위 충돌
				{
					m_fSpeed.fY = -10.f;
				}
				else
					m_fSpeed.fY *= -0.8f;

			}

		}
	}

	if (OBJ_ITEM == Obj->Get_OBJID())
	{
		++m_iCoin;
		auto& iter = CObjMgr::Get_Instance()->Get_List(OBJ_NUMBER)->begin();

		if (m_iCoin < 10)
		{
			static_cast<CNumber*>(*iter)->Change_Num(m_iCoin);
		}

		else if (m_iCoin < 100)
		{
			static_cast<CNumber*>(*iter)->Change_Num(m_iCoin/10);
			++iter;
			static_cast<CNumber*>(*iter)->Change_Num(m_iCoin % 10);
		}
		else if (m_iCoin < 1000)
		{
			static_cast<CNumber*>(*iter)->Change_Num(m_iCoin / 100);
			++iter;
			static_cast<CNumber*>(*iter)->Change_Num(m_iCoin / 10);
			++iter;
			static_cast<CNumber*>(*iter)->Change_Num(m_iCoin % 10);
		}
		

		
	}

}



void CPlayer::Late_Update()
{
	m_pHeal->Late_Update();

	if (ST_ATTACKED == m_eCurState) return;

	float fY = 0.f;
	bool bCollision = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &fY, m_tInfo.fY);

	if (bCollision && fY <= m_tRect.bottom)
	{
		m_tInfo.fY = fY - m_tInfo.fCY * 0.5f;
		m_fSpeed.fY = 0.f;

		if (!m_bLand || m_bJump)
		{
			m_eCurState = ST_JUMP_LAND;
			Motion_Change();
			
			CSoundMgr::Get_Instance()->PlaySound(L"hero_land_soft.wav", SOUND_PLAYER_LAND, g_fSound);
			m_bLandMotion = true;
		}
		m_bJump = false;
		m_bLand = true;
		m_iJumpcount = 0;

	}

	else if (bCollision)
	{
		if (!m_bJump &&  m_bLand)//자유 낙하
		{
			m_bLand = false;
		}

	}
}


void CPlayer::Key_Input()
{
	if (!m_bLandMotion && !m_bAttackMotion &&ST_JUMP_FALL!= m_eCurState)
	{
		m_eCurState = ST_IDLE;
		//CSoundMgr::Get_Instance()->StopSound(SOUND_PLAYER_WALK);
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
	{

		m_tInfo.fX -= 5.f;

		eDir = LEFT;

		m_pFrameKey = L"Player_Left";

		if (!m_bLandMotion && !m_bAttackMotion)
		{
			if (!m_bJump && m_bLand)
			{
				m_eCurState = ST_WALK;
				CSoundMgr::Get_Instance()->PlaySound(L"hero_run_footsteps_stone.wav", SOUND_PLAYER_WALK, g_fSound);
			}
		}

	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
	{

		m_tInfo.fX += 5.f;

		eDir = RIGHT;

		m_pFrameKey = L"Player_Right";


		if (!m_bLandMotion && !m_bAttackMotion)
		{
			if (!m_bJump && m_bLand)
			{
				m_eCurState = ST_WALK;
				CSoundMgr::Get_Instance()->PlaySound(L"hero_run_footsteps_stone.wav", SOUND_PLAYER_WALK, g_fSound);
			}
		}

	}


	if (CKeyMgr::Get_Instance()->Key_Down(VK_CONTROL))
	{
		if (!m_bJump)
		{
			m_fSpeed.fY = -13.f;
			m_bLand = false;
			m_bJump = true;
			++m_iJumpcount;
		}

		else if (m_iJumpcount < 2)
		{
			++m_iJumpcount;
			m_fSpeed.fY = -13.f;
		}

		m_eCurState = ST_JUMP_START;
		
		CSoundMgr::Get_Instance()->PlaySound(L"hero_jump.wav", SOUND_PLAYER_JUMP, g_fSound);

	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
	{
		if (CKeyMgr::Get_Instance()->Key_Down('Z'))
		{
			if (!m_bAttackMotion)
			{
				
				eDir = UP;
				DIR		eBase;
				if (!lstrcmp(m_pFrameKey, L"Player_Left"))
					eBase = LEFT;
				else if (!lstrcmp(m_pFrameKey, L"Player_Right"))
					eBase = RIGHT;

				static_cast<CSword*>(CObjMgr::Get_Instance()->Get_List(OBJ_SWORD)->front())->Set_Dir(eDir,eBase);
				static_cast<CSword*>(CObjMgr::Get_Instance()->Get_List(OBJ_SWORD)->front())->Set_True();
				m_eCurState = ST_ATTACK_UP;
				m_bAttackMotion = true;
				srand(unsigned(time(NULL)));
				if(rand()%2==1)
					CSoundMgr::Get_Instance()->PlaySound(L"sword_1.wav", SOUND_SWORD_EFFECT1, 0.4f);
				else
					CSoundMgr::Get_Instance()->PlaySound(L"sword_4.wav", SOUND_SWORD_EFFECT1, 0.4f);
			}
		}
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
	{
		
		if (!m_bLand)
		{
			
			if (CKeyMgr::Get_Instance()->Key_Down('Z'))
			{
				if (!m_bAttackMotion)
				{	
					eDir = DOWN;

					DIR		eBase;
					if (!lstrcmp(m_pFrameKey, L"Player_Left"))
						eBase = LEFT;
					else if (!lstrcmp(m_pFrameKey, L"Player_Right"))
						eBase = RIGHT;

					static_cast<CSword*>(CObjMgr::Get_Instance()->Get_List(OBJ_SWORD)->front())->Set_Dir(eDir,eBase);
					static_cast<CSword*>(CObjMgr::Get_Instance()->Get_List(OBJ_SWORD)->front())->Set_True();
					m_eCurState = ST_ATTACK_DOWN;
					m_bAttackMotion = true;
					srand(unsigned(time(NULL)));
					if (rand() % 2 == 1)
						CSoundMgr::Get_Instance()->PlaySound(L"sword_1.wav", SOUND_SWORD_EFFECT1, 0.4f);
					else
						CSoundMgr::Get_Instance()->PlaySound(L"sword_4.wav", SOUND_SWORD_EFFECT1, 0.4f);
				
				}
			}
		}

	}

	else if (CKeyMgr::Get_Instance()->Key_Down('Z'))
	{
		if (!m_bAttackMotion)
		{	
			static_cast<CSword*>(CObjMgr::Get_Instance()->Get_List(OBJ_SWORD)->front())->Set_Dir(eDir,eDir);
			static_cast<CSword*>(CObjMgr::Get_Instance()->Get_List(OBJ_SWORD)->front())->Set_True();
			m_eCurState = ST_ATTACK;
			m_bAttackMotion = true;
			srand(unsigned(time(NULL)));
			if (rand() % 2 == 1)
				CSoundMgr::Get_Instance()->PlaySound(L"sword_1.wav", SOUND_SWORD_EFFECT1, 0.4f);
			else
				CSoundMgr::Get_Instance()->PlaySound(L"sword_4.wav", SOUND_SWORD_EFFECT1, 0.4f);
		
		}
	}

	if (CKeyMgr::Get_Instance()->Key_Down('X'))
	{
		if (5>m_iHP)
		{
			m_pHeal->Set_Pos(m_tInfo.fX, m_tInfo.fY);
			static_cast<CHeal*>(m_pHeal)->Set_On();
			static_cast<CHeal*>(m_pHeal)->Get_HPIndex(m_iHP);
			++m_iHP;
		}
	}
	if (CKeyMgr::Get_Instance()->Key_Down('C'))
	{
		CSoundMgr::Get_Instance()->PlaySound(L"hero_dash.wav", SOUND_PLAYER_DASH, g_fSound);
		m_bDashMotion = true;

		m_pDashEffect = new CDash;
		m_pDashEffect->Initialize();
		m_pDashEffect->Set_Target(this);


		if (!lstrcmp(m_pFrameKey, L"Player_Left"))
		{
			m_fSpeed.fX = -1.f;
			m_fSpeed.fCX = -3.f;
			static_cast<CDash*>(m_pDashEffect)->Set_Dir(LEFT);
		}
		else
		{
			m_fSpeed.fX = 1.f;
			m_fSpeed.fCX = 3.f;
			static_cast<CDash*>(m_pDashEffect)->Set_Dir(RIGHT);
		}
		CObjMgr::Get_Instance()->AddObject(OBJ_EFFECT, m_pDashEffect);
	}


}



void CPlayer::Release()
{
	SAFE_DELETE(m_pHeal);
	//SAFE_DELETE(m_pDashEffect);
}

