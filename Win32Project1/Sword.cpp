#include "stdafx.h"
#include "Sword.h"
#include "ScrollMgr.h"
#include"BmpMgr.h"
#include "CEffect.h"
#include"Player.h"
#include "SoundMgr.h"
#include "ThornEffect.h"
#include "ObjMgr.h"

CSword::CSword():m_bThorn(false)
{
}
CSword::~CSword()
{
	Release();
}
void CSword::Set_Dir(DIR eDir, DIR eBase)
{
	eEffectDir = eDir;
	switch (eDir)
	{
	case LEFT:
		m_eCurState = ST_LEFT;

		m_tImageInfo.fCX = 280.f;
		m_tImageInfo.fCY = 70.f;
		m_tInfo.fCX = 100.f;;
		m_tInfo.fCY = 80.f;
		m_fDirX = -1.f;
		m_fDirY = 0.f;
		break;
		
	case RIGHT:
		m_eCurState = ST_RIGHT;

		m_tImageInfo.fCX = 280.f;
		m_tImageInfo.fCY = 70.f;
		m_tInfo.fCX = 100.f;
		m_tInfo.fCY = 80.f;
		m_fDirX = 1.f;
		m_fDirY = 0.f;
		break;

	case UP:
		if (RIGHT == eBase)
		{
			m_eCurState = ST_UP_RIGHT;
		}

		else if (LEFT == eBase)
		{
			m_eCurState = ST_UP_LEFT;
		}
		m_tInfo.fCX = 120.f;
		m_tInfo.fCY = 180.f;
		m_tImageInfo.fCX = 120.f;
		m_tImageInfo.fCY = 180.f;
		m_fDirY = -1.f;
		m_fDirX = 0.f;
		break;

	case DOWN:
		if (RIGHT == eBase)
		{
			m_eCurState = ST_DOWN_RIGHT;
		}

		else if (LEFT == eBase)
		{
			m_eCurState = ST_DOWN_LEFT;
		}

		m_tImageInfo.fCX = 120.f;
		m_tImageInfo.fCY = 180.f;
		m_tInfo.fCX = 120.f;
		m_tInfo.fCY = 180.f;
		m_fDirY = 1.f;
		m_fDirX = 0.f;
		break;
	}

}

void CSword::Initialize()
{
	

	eID = OBJ_SWORD;
}

void CSword::Render(HDC hdc)
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
	

	
	if(!m_bFlag)
		m_tImageRect.bottom = m_tImageRect.left = m_tImageRect.right = m_tImageRect.top = -1000.f;

}

int CSword::Update()
{
	if (m_bFlag)
	{
		

		Motion_Change();

		m_tInfo.fX = m_pTarget->Get_Info().fX + m_tInfo.fCX*0.5f * m_fDirX;
		m_tInfo.fY = m_pTarget->Get_Info().fY + m_tInfo.fCY*0.5f * m_fDirY;
		
		Move_Frame();
		Update_Rect();
		
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
		{
			CSoundMgr::Get_Instance()->StopSound(SOUND_SWORD_EFFECT1);
			m_bFlag = false;	
			m_bThorn = false;
		}
		m_tRect.left += 50.f*m_fDirX;
		m_tRect.right += 50.f*m_fDirX;

	}
	
	return OBJ_NOEVENT;
}

void CSword::Late_Update()
{

	m_tRect.bottom = m_tRect.left = m_tRect.right = m_tRect.top = 0.f;

}

void CSword::Release()
{
	
}

void CSword::Collision()
{
}

void CSword::Collision(CObj * Obj)
{
	if (OBJ_THORN == Obj->Get_OBJID())
	{
		if (!m_bThorn)
		{
			RECT rc{};

			IntersectRect(&rc, &m_tRect, &Obj->Get_Rect());

			CObj*	temp = new CThornEffect;
			temp->Initialize();
			temp->Set_Pos((rc.left + rc.right)*0.5f, (rc.top + rc.bottom)*0.5f);

			CObjMgr::Get_Instance()->AddObject(OBJ_EFFECT, temp);
			m_bThorn = true;
		}
	}
}

void CSword::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case ST_LEFT:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.dwFrameSpeed = 70;
			m_tFrame.dwFrameTime = GetTickCount();
			m_pFrameKey = L"Attack_Effect";
			break;

		case ST_RIGHT:
			m_tFrame.iFrameMotion = 1;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.dwFrameSpeed = 70;
			m_tFrame.dwFrameTime = GetTickCount();
			m_pFrameKey = L"Attack_Effect";
			break;

		case ST_UP_LEFT:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.dwFrameSpeed = 70;
			m_tFrame.dwFrameTime = GetTickCount();
			m_pFrameKey = L"Attack_Up";
			break;

		case ST_UP_RIGHT:
			m_tFrame.iFrameMotion = 1;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.dwFrameSpeed = 70;
			m_tFrame.dwFrameTime = GetTickCount();
			m_pFrameKey = L"Attack_Up";
			break;

		case ST_DOWN_LEFT:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.dwFrameSpeed = 70;
			m_tFrame.dwFrameTime = GetTickCount();
			m_pFrameKey = L"Attack_Down";
			break;

		case ST_DOWN_RIGHT:
			m_tFrame.iFrameMotion = 1;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.dwFrameSpeed = 70;
			m_tFrame.dwFrameTime = GetTickCount();
			m_pFrameKey = L"Attack_Down";
			break;

		}
		m_ePreState = m_eCurState;
	}
}
