#include "stdafx.h"
#include "Husk.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "LineMgr.h"
#include "Sword.h"
#include "Item.h"
#include"ObjMgr.h"
#include "Player.h"
#include"SoundMgr.h"
#include "CEffect.h"

CHusk::CHusk()
	:m_iHit(0)
{
	ZeroMemory(&m_tArea_Info, sizeof(m_tArea_Info));
	ZeroMemory(&m_tArea_Rect, sizeof(m_tArea_Rect));
	
}

CHusk::~CHusk()
{
}

void CHusk::Initialize()
{
	eID = OBJ_MONSTER;
	m_tInfo.fCX = 60.f;
	m_tInfo.fCY = 70.f;

	m_tImageInfo.fCX = 110.f;
	m_tImageInfo.fCY = 110.f;

	m_tArea_Info.fCX = 360.f;
	m_tArea_Info.fCY = 70.f;
	m_bAttackMotion = false;

	m_bLand = false;

	m_fSpeed.fX = -0.5f;
	m_fSpeed.fY = 0.f;
	m_fSpeed.fCY = 0.65f;

	m_bFreeze = false;
	m_iFreeze_Time = 0;

	

	m_eCurState = ST_IDLE;
	m_ePreState = ST_END;
	m_pFrameKey = L"Husk_Left";

	m_tFrame.iFrameMotion = 0;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 4;
	m_tFrame.dwFrameSpeed = 70;
	m_tFrame.dwFrameTime = GetTickCount();

	m_iTime = 0;

	m_iHit = 3;

	m_bDeath = false;
	m_bDeathFrame = false;
	m_iDeathTime = 0;
}

void CHusk::Render(HDC hdc)
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

void CHusk::Late_Update()
{
	
		float fY = 0.f;
		bool bCollision = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &fY, m_tInfo.fY);

		if (bCollision && fY < m_tRect.bottom)
		{
			m_tInfo.fY = fY - m_tInfo.fCY * 0.5f;
			m_bLand = true;
			m_fSpeed.fY = 0.f;

		}

		else if (bCollision)
		{
			m_bLand = false;
		}
		
		if (m_iHit == 0&&!m_bDeath)
		{
			m_bDeath = true;
			/*m_fSpeed.fY = 0.f;
			m_fSpeed.fCY = 0.65f;*/
			m_eCurState = ST_DEAD;
			CSoundMgr::Get_Instance()->PlaySound(L"enemy_death_sword.wav", SOUND_MONSTER_DEAD, g_fSound);
			CObj*	Temp = new CItem;
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
		if (0 > m_tRect.left || m_fAreaX < m_tRect.right)
			m_fSpeed.fX *= -1.f;
		if (0> m_tRect.top || m_fAreaY < m_tRect.bottom)
			m_fSpeed.fY *= -1.f;
	
}

void CHusk::Release()
{
}

int CHusk::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if (!m_bDeath)
	{
		if (!m_bFreeze)
		{
			if (!m_bAttackMotion)
			{
				if (300 >= m_iTime)
					m_eCurState = ST_IDLE;
				else if (600 >= m_iTime)
				{
					m_eCurState = ST_WALK;
					m_tInfo.fX += m_fSpeed.fX;
				}
				else
					m_iTime = 0;

				++m_iTime;
			}
			else
			{
				if (5 < m_tFrame.iFrameStart)
				{
					m_tInfo.fX += m_fSpeed.fX;
				}

				if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
				{
					m_tFrame.iFrameStart = 6;
				}
			}
		}

	}

	else
	{
		++m_iDeathTime;
		if (600 == m_iDeathTime)
			m_bDead = true;

		if(m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
		{
			m_bDeathFrame = true;
		}
	}

	if(m_bFreeze)
	{
		++m_iFreeze_Time;
		m_tInfo.fX += m_fSpeed.fX;

		if (20 == m_iFreeze_Time)
		{
			m_bFreeze = false;
			m_iFreeze_Time = 0;
			m_fSpeed.fX = 0.5f;
		}
	}

	if (!m_bLand)
	{
		m_tInfo.fY += m_fSpeed.fY;
		m_fSpeed.fY += m_fSpeed.fCY;
	}
	
	Motion_Change();

	if(!m_bDeathFrame)
		Move_Frame();

	Update_Rect();

	Update_Area();

	return OBJ_NOEVENT;
}

void	CHusk::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case ST_IDLE:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.dwFrameSpeed = 70;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ST_WALK:
			m_tFrame.iFrameMotion = 1;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.dwFrameSpeed = 70;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ST_ATTACK:
			m_tFrame.iFrameMotion = 2;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 10;
			m_tFrame.dwFrameSpeed = 70;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ST_DEAD:
			m_tFrame.iFrameMotion = 3;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 8;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();


		}
		m_ePreState = m_eCurState;
	}
}

void CHusk::Update_Area()
{
	m_tArea_Rect.left = (float)(m_tInfo.fX - 0.5f*m_tArea_Info.fCX);
	m_tArea_Rect.top = m_tRect.top;
	m_tArea_Rect.right = (float)(m_tInfo.fX + 0.5f*m_tArea_Info.fCX);
	m_tArea_Rect.bottom = m_tRect.bottom;

	

}

void CHusk::Collision()
{
}

void CHusk::Collision(CObj * Obj)
{
		if (OBJ_WALL == Obj->Get_OBJID())
		{
			if (m_tInfo.fX < Obj->Get_Rect().left)//왼쪽 충돌
			{

				float dx = m_tRect.right - Obj->Get_Rect().left;
				m_tInfo.fX -= dx;
				m_fSpeed.fX *= -1.f;
				if (0 == lstrcmp(m_pFrameKey, L"Husk_Left"))
					m_pFrameKey = L"Husk_Right";
				else
					m_pFrameKey = L"Husk_Left";
			}
			else if (m_tInfo.fX > Obj->Get_Rect().right)//오른쪽 충돌
			{

				float dx = Obj->Get_Rect().right - m_tRect.left;
				m_tInfo.fX += dx;
				m_fSpeed.fX *= -1.f;
				if (0 == lstrcmp(m_pFrameKey, L"Husk_Left"))
					m_pFrameKey = L"Husk_Right";
				else
					m_pFrameKey = L"Husk_Left";
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

	
	if (!m_bFreeze&&!m_bDeath)
	{
		if (OBJ_SWORD == Obj->Get_OBJID())
		{
			CSoundMgr::Get_Instance()->PlaySound(L"enemy_damage.wav", SOUND_MONSTER_ATTACKED, g_fSound);
			m_bFreeze = true;
			--m_iHit;

			DIR Obj_Dir = static_cast<CSword*>(Obj)->Get_Dir();

			if (LEFT == Obj_Dir)
				m_fSpeed.fX = -5.f;
			if (RIGHT == Obj_Dir)
				m_fSpeed.fX = 5.f;



			if(Obj->Get_Info().fY <m_tInfo.fY)
				static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER)->front())->Reflect();

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

		if (OBJ_PLAYER == Obj->Get_OBJID())
		{
			RECT rc{};

			if (IntersectRect(&rc, &m_tArea_Rect, &Obj->Get_Rect()))
			{
				m_bAttackMotion = true;
				m_eCurState = ST_ATTACK;
				
				if (Obj->Get_Info().fX < m_tInfo.fX)
				{
					m_fSpeed.fX = -3.f;
					m_pFrameKey = L"Husk_Left";
				}
				else if (Obj->Get_Info().fX > m_tInfo.fX)
				{
					m_fSpeed.fX = 3.f;
					m_pFrameKey = L"Husk_Right";
				}
			}
			
			else
			{
				m_bAttackMotion = false;
				if (0 == lstrcmp(m_pFrameKey, L"Husk_Left"))
					m_fSpeed.fX = -0.5f;

				else if (0 == lstrcmp(m_pFrameKey, L"Husk_Right"))
					m_fSpeed.fX = 0.5f;
			}
		}
	}

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
	
}
