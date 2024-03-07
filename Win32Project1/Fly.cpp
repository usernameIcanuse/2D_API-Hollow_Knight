#include "stdafx.h"
#include "Fly.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "LineMgr.h" 
#include "Sword.h"
#include "Item.h"
#include "ObjMgr.h"
#include "SoundMgr.h"
#include "Player.h"
#include "CEffect.h"


CFly::CFly()
{
}

CFly::~CFly()
{
}

void CFly::Initialize()
{
	eID = OBJ_MONSTER;
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 40.f;

	m_tImageInfo.fCX = 90.f;
	m_tImageInfo.fCY = 90.f;

	m_fSpeed.fX = 2.f;
	m_fSpeed.fY = 3.f;

	m_bFreeze = false;
	m_bDeath = false;
	m_iFreeze_Time = 0;


	m_eCurState = ST_MOVE;
	m_ePreState = ST_END;
	m_pFrameKey = L"Fly_Right";

	m_tFrame.iFrameMotion = 0;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();

	m_iHit = 3;
	m_iTime = 0;
	m_bLand = false;
	m_bDeathFrame = false;
}

void CFly::Render(HDC hdc)
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

int CFly::Update()
{

	if (m_bDead)
		return OBJ_DEAD;
	if (!m_bDeath)
	{
		if (!m_bFreeze)
		{
			m_tInfo.fX += m_fSpeed.fX;
			m_tInfo.fY += m_fSpeed.fY;
		}

	}

	else
	{
		if (!m_bLand)
		{
			m_tInfo.fY += m_fSpeed.fY;
			m_fSpeed.fY += m_fSpeed.fCY;
		}

		++m_iTime;
		if (600 == m_iTime)
			m_bDead = true;
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
		{
			m_bDeathFrame = true;
		}
	}

	if(m_bFreeze)
	{
		++m_iFreeze_Time;
		m_tInfo.fX += m_fSpeed.fX;
		m_tInfo.fY += m_fSpeed.fY;
		if (20 == m_iFreeze_Time)
		{
			m_bFreeze = false;
			m_iFreeze_Time = 0;
			m_fSpeed.fX = 2.f;
			m_fSpeed.fY = 3.f;
		}
	}

	Motion_Change();

	if (!m_bDeathFrame)
		Move_Frame();
	Update_Rect();

	return OBJ_NOEVENT;
}

void	CFly::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case ST_MOVE:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			CSoundMgr::Get_Instance()->PlaySound(L"fly_flying.wav", SOUND_MONSTER_FLY,0.6f);
			break;

		case ST_DEAD:
			m_tFrame.iFrameMotion = 1;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();

		
		}
		m_ePreState = m_eCurState;
	}
}


void CFly::Late_Update()
{
	if (m_bDeath)
	{
		float fY = 0.f;
		bool bCollision = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &fY, m_tInfo.fY);

		if (bCollision && fY <= m_tRect.bottom)
		{
			m_tInfo.fY = fY - m_tInfo.fCY * 0.5f;
			m_fSpeed.fY = 0.f;
			m_bLand = true;
		}
	}
	else
	{

		if (m_iHit == 0)
		{
			m_bDeath = true;
			m_fSpeed.fY = 0.f;
			m_fSpeed.fCY = 0.65f;
			m_eCurState = ST_DEAD;
			CSoundMgr::Get_Instance()->StopSound(SOUND_MONSTER_FLY);
			CSoundMgr::Get_Instance()->PlaySound(L"enemy_death_sword.wav", SOUND_MONSTER_DEAD, g_fSound);
			CObj*	Temp = new CItem;
			Temp->Set_Pos(m_tInfo.fX, m_tInfo.fY);
			Temp->Initialize();
			Temp->Set_SpeedX(rand() % 5 + 2);
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
			if (0 > m_fSpeed.fX)
				m_pFrameKey = L"Fly_Left";

			else
				m_pFrameKey = L"Fly_Right";

		
	}


	if (0 > m_tRect.left || m_fAreaX < m_tRect.right)
		m_fSpeed.fX *= -1.f;

	if(0 > m_tRect.top|| m_fAreaY < m_tRect.bottom)
		m_fSpeed.fY *= -1.f;

}

void CFly::Release()
{
}



void CFly::Collision()
{
}

void CFly::Collision(CObj * Obj)
{
	if (m_bDeath)
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
		}
		return;
	}
	if (OBJ_WALL == Obj->Get_OBJID())
	{
		if (m_tInfo.fX < Obj->Get_Rect().left)//왼쪽 충돌
		{

			float dx = m_tRect.right - Obj->Get_Rect().left;
			m_tInfo.fX -= dx;
			m_fSpeed.fX *= -1.f;
		}
		else if (m_tInfo.fX > Obj->Get_Rect().right)//오른쪽 충돌
		{

			float dx = Obj->Get_Rect().right - m_tRect.left;
			m_tInfo.fX += dx;
			m_fSpeed.fX *= -1.f;
		}
		else
		{
			if (m_tInfo.fY > Obj->Get_Rect().bottom)//아래 충돌
			{

				if (m_tRect.top < Obj->Get_Rect().bottom)
				{
					float dy = Obj->Get_Rect().bottom - m_tRect.top;
					m_tInfo.fY += dy;
					m_fSpeed.fY *= -1.f;
				}
			}
			else
			{
				if (m_tRect.bottom > Obj->Get_Rect().top)
				{
					float dy =  m_tRect.bottom - Obj->Get_Rect().top;
					m_tInfo.fY -= dy;
					if (!m_bDeath)
						m_fSpeed.fY *= -1.f;
				}
			}

		}
	}

	if (OBJ_SWORD == Obj->Get_OBJID())
	{
		if (!m_bFreeze)
		{
			CSoundMgr::Get_Instance()->PlaySound(L"enemy_damage.wav", SOUND_MONSTER_ATTACKED, g_fSound);
			m_bFreeze = true;
			--m_iHit;

			DIR Obj_Dir = static_cast<CSword*>(Obj)->Get_Dir();

			if (LEFT == Obj_Dir)
				m_fSpeed.fX = -5.f;
			if (RIGHT == Obj_Dir)
				m_fSpeed.fX = 5.f;
			if (UP == Obj_Dir)
				m_fSpeed.fY = -5.f;
			if (DOWN == Obj_Dir)
			{
				m_fSpeed.fY = 5.f;
				if (Obj->Get_Info().fY < m_tInfo.fY)
					static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER)->front())->Reflect();
			}

			RECT rc{};

			IntersectRect(&rc, &m_tRect, &Obj->Get_Rect());

			if (UP == Obj_Dir) Obj_Dir = LEFT;
			else if (DOWN == Obj_Dir) Obj_Dir = RIGHT;

			CObj*	temp = new CEffect;
			static_cast<CEffect*>(temp)->Set_Dir(Obj_Dir);
			
			temp->Set_Pos((rc.left + rc.right)*0.5f, (rc.top + rc.bottom)*0.5f);
			temp->Initialize();
			CObjMgr::Get_Instance()->AddObject(OBJ_EFFECT, temp);

		}
	}
}
