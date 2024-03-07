#include "stdafx.h"
#include "Damaged.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "SoundMgr.h"

CDamaged::CDamaged() :m_bFlag(true)
{
}

CDamaged::~CDamaged()
{
}

void CDamaged::Initialize()
{

	m_tImageInfo.fCX = 700.f;
	m_tImageInfo.fCY = 360.f;

	m_tInfo.fCX = m_tInfo.fCY = 0.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/DamagedEffect1.bmp", L"DamagedEffect1");
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/DashEffect_Right.bmp", L"DashEffect_Right");

	m_eCurState = ST_ON;
	m_ePreState = ST_END;
	m_pFrameKey = L"DamagedEffect1";

}

void CDamaged::Render(HDC hdc)
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
		RGB(193, 193, 194));



	if (!m_bFlag)
	{
		m_tImageRect.bottom = m_tImageRect.left = m_tImageRect.right = m_tImageRect.top = -1000.f;
	}
}

void CDamaged::Late_Update()
{


}

void CDamaged::Release()
{
}

int CDamaged::Update()
{
	if (!m_bFlag)
		return OBJ_DEAD;

	Motion_Change();

	m_tInfo.fX = m_pTarget->Get_Info().fX;
	m_tInfo.fY = m_pTarget->Get_Info().fY;

	if (2 == m_tFrame.iFrameStart)
	{
	
		
		CSoundMgr::Get_Instance()->PlaySound(L"hero_damage.wav", SOUND_PLAYER_DAMAGED, g_fSound);
		g_bStopFrame = true;
	}

	if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
	{
		m_bFlag = false;
		CSoundMgr::Get_Instance()->StopSound( SOUND_PLAYER_DAMAGED);
	}
	Move_Frame();

	Update_Rect();

	return OBJ_NOEVENT;
}

void	CDamaged::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case ST_ON:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.dwFrameSpeed = 10;
			m_tFrame.dwFrameTime = GetTickCount();

		}
		m_ePreState = m_eCurState;
	}
}

void CDamaged::Collision()
{
}

void CDamaged::Collision(CObj * Obj)
{
}