#include "stdafx.h"
#include "Boss.h"
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
#include "BossEffect.h"

CBoss::CBoss()
{
	
}

CBoss::~CBoss()
{
	Release();
}

void CBoss::Initialize()
{

	m_pTarget = CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER)->front();
	m_bHit = false;
	eID = OBJ_MONSTER;
	m_tInfo.fCX = 140.f;
	m_tInfo.fCY = 250.f;

	m_fSpeed.fX = 1.f;
	m_fSpeed.fY = m_fSpeed.fCX = 0.f;
	m_fSpeed.fCY = 0.8f;
	

	m_tImageInfo.fCX = 600.f;
	m_tImageInfo.fCY = 600.f;



	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Boss_Right.bmp", L"Boss_Right");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Boss_Left.bmp", L"Boss_Left");

	m_eCurState = ST_IDLE;
	m_ePreState = ST_END;
	m_pFrameKey = L"Boss_Right";

	m_tFrame.iFrameMotion = 0;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 5;
	m_tFrame.dwFrameSpeed = 50;
	m_tFrame.dwFrameTime = GetTickCount();

	m_bAttackMotion = false;

	m_bJump = false;
	m_bJumpAttack = false;
	
	m_bLand = false;
	m_bStopFrame = false;

	m_bDeathFrame = false;
	m_bDeath = false;

	m_bFreeze = false;
	m_iFreeze_Time = 0;

	m_iTime = 0;


	m_iDeathTime = 0;

	m_iHit = 30;

}

void CBoss::Render(HDC hdc)
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
}

void CBoss::Late_Update()
{
	float fY = 0.f;
	bool bCollision = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &fY, m_tInfo.fY);

	if (bCollision && fY <= m_tRect.bottom)
	{
		m_tInfo.fY = fY - m_tInfo.fCY * 0.5f;
		m_fSpeed.fY = 0.f;


		m_bLand = true;
	}

	if (!m_bDeath && !m_bJump && !m_bJumpAttack && !m_bAttackMotion)
	{
		if (m_pTarget->Get_Info().fX < m_tInfo.fX)
		{
			m_pFrameKey = L"Boss_Left";
			m_fSpeed.fX = -5.f;
		}

		else if (m_pTarget->Get_Info().fX > m_tInfo.fX)
		{
			m_pFrameKey = L"Boss_Right";
			m_fSpeed.fX = 5.f;
		}
	}

	if (m_iHit == 0 && !m_bDeath)
	{
		m_bDeath = true;

		m_eCurState = ST_DEAD;
		CSoundMgr::Get_Instance()->PlaySound(L"false_knight_damage_armour_final.wav", SOUND_MONSTER_DEAD, g_fSound);
		CSoundMgr::Get_Instance()->PlaySound(L"Ruins_Sentry_death_02.wav", SOUND_SEMIBOSS_SOUND1, 0.4f);

		
	}

}

void CBoss::Release()
{
}

int CBoss::Update()
{


	if (m_bDead)
		return OBJ_DEAD;

	if (!m_bDeath)
	{

		++m_iTime;

		if (80 == m_iTime)
		{
			srand(unsigned(time(NULL)));

			int tmp = rand() % 3;

			if (0 == tmp)
			{
				m_bJump = true;
				m_eCurState = ST_JUMP;
			}
			else if (1 == tmp)
			{
				m_bJump = true;
				m_bJumpAttack = true;
				m_eCurState = ST_JUMP;
			}
			else
			{
				m_bAttackMotion = true;
				m_eCurState = ST_ATTACK;
			}
			
		}
		
		

		if ( !m_bJumpAttack &&m_bJump)
		{
			

			if (3 == m_tFrame.iFrameStart)
			{
				m_fSpeed.fY = -20.f;
				CSoundMgr::Get_Instance()->PlaySound(L"false_knight_jump.wav", SOUND_SEMIBOSS_JUMP, 0.4f);
				m_bLand = false;

			}

			else if (!m_bLand && 6 == m_tFrame.iFrameStart)
			{
				m_bStopFrame = true;
			}
			else if (m_bLand && 3<m_tFrame.iFrameStart)
			{
				m_bStopFrame = false;
			}


			if ( 7 == m_tFrame.iFrameStart)
			{
				CSoundMgr::Get_Instance()->PlaySound(L"false_knight_land.wav", SOUND_SEMIBOSS_SOUND1, 0.6f);

			}

			if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
			{
				m_eCurState = ST_IDLE;
				m_bJump = false;
				m_iTime = 0;
			}
			

		}

		else if (m_bJumpAttack && m_bJump)
		{
			if (ST_JUMP == m_eCurState && 3 == m_tFrame.iFrameStart)
			{
				m_fSpeed.fY = -20.f;
				CSoundMgr::Get_Instance()->PlaySound(L"false_knight_jump.wav", SOUND_SEMIBOSS_JUMP, 0.4f);
				m_eCurState = ST_JUMPATTACK;
				m_bLand = false;

			}
			else if (!m_bLand && 4 == m_tFrame.iFrameStart)
			{
				m_bStopFrame = true;
				CSoundMgr::Get_Instance()->PlaySound(L"false_knight_swing.wav", SOUND_SEMIBOSS_SOUND2, 0.7f);
			}

			else if (m_bLand && ST_JUMPATTACK == m_eCurState)
			{
				m_bStopFrame = false;
			}

		
			if (8 == m_tFrame.iFrameStart)
			{
				
				if (!m_bHit)
				{

					CObj*	temp = new CBossEffect;
				
					float dx = 0.f;
					if (0==lstrcmp(L"Boss_Right", m_pFrameKey))
						dx = 200.f;
					else
						dx = -200.f;

					temp->Set_Pos(m_tInfo.fX + dx, m_tRect.bottom);
					temp->Initialize();
					CObjMgr::Get_Instance()->AddObject(OBJ_EFFECT, temp);
					m_bHit = true;

					CSoundMgr::Get_Instance()->StopSound(SOUND_SEMIBOSS_SOUND1);
				}
				CSoundMgr::Get_Instance()->PlaySound(L"false_knight_strike_ground.wav", SOUND_SEMIBOSS_SOUND3, 0.7f);
			}

			if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
			{
				m_eCurState = ST_IDLE;
				m_bJump = false;
				m_bJumpAttack = false;
				m_iTime = 0;
				m_bHit = false;
			}

		}

		else if (m_bAttackMotion)
		{
			if (5 == m_tFrame.iFrameStart)
			{

				CSoundMgr::Get_Instance()->PlaySound(L"false_knight_swing.wav", SOUND_SEMIBOSS_SOUND2, 0.7f);

			}

			if (7 == m_tFrame.iFrameStart)
			{
				
				
				if (!m_bHit)
				{			
					CObj* temp = new CAttack;
					
					

					float dx = 0.f;
					if (0 == lstrcmp(L"Boss_Right", m_pFrameKey))
					{
						dx = 200.f;
						temp->Set_Pos(m_tInfo.fX + dx, m_tInfo.fY);
						temp->Initialize();
						static_cast<CAttack*>(temp)->Set_Speed();
					
					}
					else
					{
						dx = -200.f;
						temp->Set_Pos(m_tInfo.fX + dx, m_tInfo.fY);
						temp->Initialize();
					}

					
				
					CObjMgr::Get_Instance()->AddObject(OBJ_ATTACK, temp);


					temp = new CBossEffect;
					temp->Set_Pos(m_tInfo.fX +dx, m_tRect.bottom);
					temp->Initialize();
					CObjMgr::Get_Instance()->AddObject(OBJ_EFFECT, temp);

					

					m_bHit= true;
					CSoundMgr::Get_Instance()->StopSound( SOUND_SEMIBOSS_SOUND1);
				}
				CSoundMgr::Get_Instance()->PlaySound(L"false_knight_strike_ground.wav", SOUND_SEMIBOSS_SOUND1, 0.7f);
			}
			if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
			{
				m_eCurState = ST_IDLE;
				m_bAttackMotion = false;
				m_iTime = 0;
				m_bHit = false;
			}
		}		

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
	else
	{
		++m_iDeathTime;
		if (600 == m_iDeathTime)
			m_bDead = true;

		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
			m_bDeathFrame = true;
	}

	if (!m_bLand)
	{
		m_tInfo.fY += m_fSpeed.fY;
		m_fSpeed.fY += m_fSpeed.fCY;
		m_tInfo.fX += m_fSpeed.fX;
	}

	Motion_Change();

	if (!m_bDeathFrame && !m_bStopFrame)
		Move_Frame();

	Update_Rect();

	return OBJ_NOEVENT;
}

void CBoss::Collision()
{
}

void CBoss::Collision(CObj * Obj)
{
	if (m_bDeath) return;
	if (OBJ_SWORD == Obj->Get_OBJID())
	{
		if (!m_bFreeze)
		{
			CSoundMgr::Get_Instance()->PlaySound(L"false_knight_damage_armour.wav", SOUND_MONSTER_ATTACKED, g_fSound);
			--m_iHit;
			m_bFreeze = true;

			DIR Obj_Dir = static_cast<CSword*>(Obj)->Get_Dir();

			RECT rc{};
			IntersectRect(&rc, &m_tRect, &Obj->Get_Rect());

			CObj*	temp = new CEffect;
			static_cast<CEffect*>(temp)->Set_Dir(Obj_Dir);
			temp->Set_Pos((rc.left + rc.right)*0.5f, (rc.top + rc.bottom)*0.5f);
			temp->Initialize();
			CObjMgr::Get_Instance()->AddObject(OBJ_EFFECT, temp);
		}
	}


}

void CBoss::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case ST_IDLE:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ST_JUMP:
			CSoundMgr::Get_Instance()->PlaySound(L"False_Knight_Attack_New_02.wav", SOUND_SEMIBOSS, 0.4f);
			m_tFrame.iFrameMotion = 1;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.dwFrameSpeed = 150;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		
		case ST_ATTACK:
			CSoundMgr::Get_Instance()->PlaySound(L"False_Knight_Attack_New_01.wav", SOUND_SEMIBOSS, 0.4f);
			m_tFrame.iFrameMotion = 2;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 12;
			m_tFrame.dwFrameSpeed = 80;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ST_JUMPATTACK:
			CSoundMgr::Get_Instance()->PlaySound(L"False_Knight_Attack_New_05.wav", SOUND_SEMIBOSS, 0.4f);
			m_tFrame.iFrameMotion = 3;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 10;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ST_DEAD:
			m_tFrame.iFrameMotion = 4;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}

}


