#include "stdafx.h"
#include "Heal.h"
#include "BmpMgr.h"
#include"ScrollMgr.h"
#include "ObjMgr.h"
#include "Hp.h"
#include "SoundMgr.h"

CHeal::CHeal() :m_bFlag(false)
{
}

CHeal::~CHeal()
{
}

void CHeal::Initialize()
{
	m_iIndex = 0;
	m_tImageInfo.fCX = 140.f;
	m_tImageInfo.fCY = 140.f;

	m_tInfo.fCX = m_tInfo.fCY = 0.f;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/HP/HPHealEffect.bmp", L"Heal");

	m_eCurState = ST_CHARGE;
	m_ePreState = ST_END;
	m_pFrameKey = L"Heal";


	m_tFrame.iFrameMotion = 0;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 13;
	m_tFrame.dwFrameSpeed = 70;
	m_tFrame.dwFrameTime = GetTickCount();
}

void CHeal::Render(HDC hdc)
{
	
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

		GdiTransparentBlt(hdc,
			(int)m_tImageRect.left+ CScrollMgr::Get_Instance()->Get_ScrollX(),
			(int)m_tImageRect.top+ CScrollMgr::Get_Instance()->Get_ScrollY(),
			(int)m_tImageInfo.fCX,
			(int)m_tImageInfo.fCY,
			hMemDC,
			m_tFrame.iFrameMotion *(int)m_tImageInfo.fCX,
			m_tFrame.iFrameStart*(int)m_tImageInfo.fCY,
			(int)m_tImageInfo.fCX,
			(int)m_tImageInfo.fCY,
			RGB(192, 192, 192));
	


	if (!m_bFlag)
	{
		m_tImageRect.bottom = m_tImageRect.left = m_tImageRect.right = m_tImageRect.top = -1000.f;
	}
}

void CHeal::Late_Update()
{
	
	if (m_bFlag && ST_HEAL == m_eCurState)
	{
		if (0 == m_tFrame.iFrameStart )
		{
			auto&iter = CObjMgr::Get_Instance()->Get_List(OBJ_HP)->begin();
			for (int i = 0; i < m_iIndex; ++i)
				++iter;
			static_cast<CHp*>(*iter)->Set_On();
		}
	}
}

void CHeal::Release()
{
}

int CHeal::Update()
{
	if (m_bFlag)
	{
		Motion_Change();

		if (ST_CHARGE == m_eCurState)
		{
			if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
			{
				m_eCurState = ST_HEAL;
				CSoundMgr::Get_Instance()->StopSound(SOUND_PLAYER_HEALING);
			}
		}

		else if (ST_HEAL == m_eCurState)
		{
			if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
			{
				m_eCurState = ST_CHARGE;
				m_bFlag = false;
			}
		}

		Move_Frame();

		Update_Rect();
	}
	return OBJ_NOEVENT;
}

void	CHeal::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case ST_CHARGE:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 13;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			CSoundMgr::Get_Instance()->PlaySoundW(L"focus_health_charging.wav", SOUND_PLAYER_HEALING, 0.9f);
			break;
		case ST_HEAL:
			m_tFrame.iFrameMotion = 1;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.dwFrameSpeed = 40;
			m_tFrame.dwFrameTime = GetTickCount();
			CSoundMgr::Get_Instance()->PlaySoundW(L"focus_health_heal.wav", SOUND_PLAYER_HEALING, 0.6f);
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CHeal::Collision()
{
}

void CHeal::Collision(CObj * Obj)
{
}
