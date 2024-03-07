#include "stdafx.h"
#include "SemiBoss.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "LineMgr.h"
#include "Attack.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Item.h"
#include "SoundMgr.h"
#include "CEffect.h"
#include "Sword.h"

CSemiBoss::CSemiBoss()
{
	ZeroMemory(&m_t_Near_Rect, sizeof(m_t_Near_Rect));
	ZeroMemory(&m_t_Near_Info, sizeof(m_t_Near_Info));
}

CSemiBoss::~CSemiBoss()
{
	Release();
}

void CSemiBoss::Initialize()
{
	
	
	eID = OBJ_MONSTER;
	m_tInfo.fCX = 170.f;
	m_tInfo.fCY = 220.f;

	m_fSpeed.fX = 0.5;

	m_tImageInfo.fCX = 500.f;
	m_tImageInfo.fCY = 500.f;


	m_t_Near_Info.fCX = 700.f;
	m_t_Near_Info.fCY = 220.f;
	m_bNearArea = false;

	m_eCurState = ST_STANDBY;
	m_ePreState = ST_END;
	m_pFrameKey = L"SemiBoss_Left";

	m_tFrame.iFrameMotion = 0;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.dwFrameSpeed = 50;
	m_tFrame.dwFrameTime = GetTickCount();

	m_bAttackMotion = false;
	
	
	m_bWakeUp = false;
	m_bWalk = false;
	m_bSwitch = false;
	m_bDeathFrame = false;
	m_bDeath = false;

	m_bFreeze = false;
	m_iFreeze_Time = 0;

	m_iTime = 0;
	m_iButtTime = 0;

	m_iDeathTime = 0;

	m_iHit = 20;
	m_bAttack = false;
}

void CSemiBoss::Render(HDC hdc)
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
		RGB(192, 192, 192));
}

void CSemiBoss::Late_Update()
{
	float fY = 0.f;
	bool bCollision = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &fY, m_tInfo.fY);

	if (bCollision && fY <= m_tRect.bottom)
	{
		m_tInfo.fY = fY - m_tInfo.fCY * 0.5f;
	}

	
	if (m_iHit == 0&&!m_bDeath)
	{
		m_bDeath = true;

		m_eCurState = ST_DEAD;
		CSoundMgr::Get_Instance()->PlaySound(L"enemy_death_sword.wav", SOUND_MONSTER_DEAD, g_fSound);
		CSoundMgr::Get_Instance()->PlaySound(L"Ruins_Sentry_death_02.wav", SOUND_SEMIBOSS_SOUND1, 0.4f);
		CObj*	Temp = new CItem;
		Temp->Set_Pos(m_tInfo.fX, m_tInfo.fY);
		Temp->Initialize();
		CObjMgr::Get_Instance()->AddObject(OBJ_ITEM, Temp);

		Temp = new CItem;
		Temp->Set_Pos(m_tInfo.fX, m_tInfo.fY);
		Temp->Initialize();
		Temp->Set_SpeedX(rand() % 5);
		CObjMgr::Get_Instance()->AddObject(OBJ_ITEM, Temp);


		Temp = new CItem;
		Temp->Set_Pos(m_tInfo.fX, m_tInfo.fY);
		Temp->Initialize();
		Temp->Set_SpeedX(rand() % 5 * -1.f);
		CObjMgr::Get_Instance()->AddObject(OBJ_ITEM, Temp);


		Temp = new CItem;
		Temp->Set_Pos(m_tInfo.fX, m_tInfo.fY);
		Temp->Initialize();
		Temp->Set_SpeedX(rand() % 5);
		CObjMgr::Get_Instance()->AddObject(OBJ_ITEM, Temp);
		Temp = new CItem;
		Temp->Set_Pos(m_tInfo.fX, m_tInfo.fY);
		Temp->Initialize();
		Temp->Set_SpeedX(rand() % 5);
		CObjMgr::Get_Instance()->AddObject(OBJ_ITEM, Temp);


		Temp = new CItem;
		Temp->Set_Pos(m_tInfo.fX, m_tInfo.fY);
		Temp->Initialize();
		Temp->Set_SpeedX(rand() % 5 * -1.f);
		CObjMgr::Get_Instance()->AddObject(OBJ_ITEM, Temp);


		Temp = new CItem;
		Temp->Set_Pos(m_tInfo.fX, m_tInfo.fY);
		Temp->Initialize();
		Temp->Set_SpeedX(rand() % 5);
		CObjMgr::Get_Instance()->AddObject(OBJ_ITEM, Temp);
		Temp = new CItem;
		Temp->Set_Pos(m_tInfo.fX, m_tInfo.fY);
		Temp->Initialize();
		Temp->Set_SpeedX(rand() % 5);
		CObjMgr::Get_Instance()->AddObject(OBJ_ITEM, Temp);


		Temp = new CItem;
		Temp->Set_Pos(m_tInfo.fX, m_tInfo.fY);
		Temp->Initialize();
		Temp->Set_SpeedX(rand() % 5 * -1.f);
		CObjMgr::Get_Instance()->AddObject(OBJ_ITEM, Temp);


		Temp = new CItem;
		Temp->Set_Pos(m_tInfo.fX, m_tInfo.fY);
		Temp->Initialize();
		Temp->Set_SpeedX(rand() % 5);
		CObjMgr::Get_Instance()->AddObject(OBJ_ITEM, Temp);
	}
	
}

void CSemiBoss::Release()
{
}

int CSemiBoss::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if (!m_bDeath)
	{
		if (m_bWakeUp)
		{
			if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
			{

				m_bWalk = true;
				m_eCurState = ST_WALK;
				m_bWakeUp = false;

			}
		}

		else if (m_bWalk)
		{
			
			if (m_bSwitch)
			{
				if (60 == m_iTime)
				{
					m_bAttackMotion = true;
					m_iTime = 0;
				}

				++m_iTime;
			}

			if (m_iButtTime == 6)
			{
				m_eCurState = ST_DASH;
				if (6 == m_tFrame.iFrameStart)
				{
					if (!m_bAttack)
					{
						CObjMgr::Get_Instance()->AddObject(OBJ_ATTACK, CAbstractFactory<CAttack>::Create(m_tInfo.fX,m_tInfo.fY));
						m_bAttack = true;
					}
				}
				else if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
				{
					m_eCurState = ST_WALK;
					m_iButtTime = 0;
					m_iTime = 0;
					m_bAttack = false;
				}
			}
			else if (m_bAttackMotion)
			{
				m_eCurState = ST_ATTACK;

				if (6 == m_tFrame.iFrameStart)
				{
					CSoundMgr::Get_Instance()->PlaySound(L"false_knight_land.wav", SOUND_SEMIBOSS_ATTACK, 0.4f);
				}

				if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
				{
					m_bAttackMotion = false;
					m_eCurState = ST_WALK;
					++m_iButtTime;
				}
			}

			else
				m_tInfo.fX += m_fSpeed.fX;

			if (m_bFreeze)
			{
				++m_iFreeze_Time;

				if (20 == m_iFreeze_Time)
				{
					m_bFreeze = false;
					m_iFreeze_Time = 0;
				}
			}

			
		}
	}
	else
	{
		++m_iDeathTime;
		if (600 == m_iDeathTime)
			m_bDead = true;

		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
			m_bDeathFrame = true;
	}
	

	Motion_Change();

	if (!m_bDeathFrame)
		Move_Frame();

	Update_Rect();
	Update_Area();

	return OBJ_NOEVENT;
}

void CSemiBoss::Collision()
{
}

void CSemiBoss::Collision(CObj * Obj)
{
	if (m_bDeath) return;
	if (OBJ_SWORD == Obj->Get_OBJID())
	{
		if (!m_bFreeze)
		{
			CSoundMgr::Get_Instance()->PlaySound(L"enemy_damage.wav", SOUND_MONSTER_ATTACKED, g_fSound);
			--m_iHit;
			m_bFreeze = true;

			RECT rc{};

			IntersectRect(&rc, &m_tRect, &Obj->Get_Rect());

			DIR Obj_Dir = static_cast<CSword*>(Obj)->Get_Dir();

			CObj*	temp = new CEffect;
			static_cast<CEffect*>(temp)->Set_Dir(Obj_Dir);
			temp->Set_Pos((rc.left + rc.right)*0.5f, (rc.top + rc.bottom)*0.5f);
			temp->Initialize();
			CObjMgr::Get_Instance()->AddObject(OBJ_EFFECT, temp);

		}
	}

	else if (OBJ_PLAYER == Obj->Get_OBJID())
	{
	
			RECT rc{};

			if (IntersectRect(&rc, &m_t_Near_Rect, &Obj->Get_Rect()))
			{

				if (ST_STANDBY == m_eCurState)
				{
					m_bWakeUp = true;
					m_eCurState = ST_WAKEUP;
					Motion_Change();
				}

				else 	m_bSwitch = true;


				if (Obj->Get_Info().fX < m_tInfo.fX)
				{
					m_fSpeed.fX = -0.5f;
					m_pFrameKey = L"SemiBoss_Left";
				}
				else if (Obj->Get_Info().fX > m_tInfo.fX)
				{
					m_fSpeed.fX = 0.5f;
					m_pFrameKey = L"SemiBoss_Right";
				}

			}


			else
			{
				m_bSwitch = false;
			}
		
	}
}

void CSemiBoss::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case ST_STANDBY:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ST_WAKEUP:
			CSoundMgr::Get_Instance()-> PlaySound(L"Ruins_Great_Shield_Sentry_attack_03.wav", SOUND_SEMIBOSS_SOUND1, 0.4f);
			m_tFrame.iFrameMotion = 1;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ST_WALK:
			m_tFrame.iFrameMotion = 2;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ST_ATTACK:
			CSoundMgr::Get_Instance()->PlaySound(L"Ruins_Sentry_Fat_attack_02.wav", SOUND_SEMIBOSS_SOUND1, 0.4f);
			m_tFrame.iFrameMotion = 3;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 11;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ST_DASH:
			CSoundMgr::Get_Instance()->PlaySound(L"Ruins_Great_Shield_Sentry_attack_02.wav", SOUND_SEMIBOSS_SOUND1, 0.4f);
			m_tFrame.iFrameMotion = 4;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 14;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ST_DEAD:
			m_tFrame.iFrameMotion = 5;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.dwFrameSpeed = 70;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}

}

void CSemiBoss::Update_Area()
{
	
	m_t_Near_Rect.left = (float)(m_tInfo.fX -  m_t_Near_Info.fCX*0.5f);
	m_t_Near_Rect.top = m_tRect.top;
	m_t_Near_Rect.right = (float)(m_tInfo.fX +  m_t_Near_Info.fCX*0.5f);
	m_t_Near_Rect.bottom = m_tRect.bottom;

}
