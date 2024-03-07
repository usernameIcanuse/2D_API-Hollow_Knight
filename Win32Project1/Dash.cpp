#include "stdafx.h"
#include "Dash.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "SoundMgr.h"

CDash::CDash() :m_bFlag(true)
{
}

CDash::~CDash()
{
}

void CDash::Initialize()
{

	m_tImageInfo.fCX = 340.f;
	m_tImageInfo.fCY = 160.f;

	m_tInfo.fCX = m_tInfo.fCY = 0.f;
	
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/DashEffect_Left.bmp", L"DashEffect_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/DashEffect_Right.bmp", L"DashEffect_Right");

	m_eCurState = ST_ON;
	m_ePreState = ST_END;
	
}

void CDash::Render(HDC hdc)
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

void CDash::Late_Update()
{


}

void CDash::Release()
{
}

int CDash::Update()
{
	if (!m_bFlag)
		return OBJ_DEAD;

		Motion_Change();

		m_tInfo.fX = m_pTarget->Get_Info().fX;
		m_tInfo.fY = m_pTarget->Get_Info().fY;
		
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
		{
			m_bFlag = false;
		}
		Move_Frame();

		Update_Rect();
	
	return OBJ_NOEVENT;
}

void	CDash::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case ST_ON:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.dwFrameSpeed = 40;
			m_tFrame.dwFrameTime = GetTickCount();
			
		}
		m_ePreState = m_eCurState;
	}
}

void CDash::Collision()
{
}

void CDash::Collision(CObj * Obj)
{
}