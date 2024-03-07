#include "stdafx.h"
#include "ThornEffect.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "SoundMgr.h"


CThornEffect::CThornEffect()
{
}

CThornEffect::~CThornEffect()
{
	Release();
}

void CThornEffect::Initialize()
{
	m_tImageInfo.fCX = 200.f;
	m_tImageInfo.fCY = 130.f;

	m_tInfo.fCX = m_tInfo.fCY = 0.f;

	m_bFlag = true;
	m_eCurState = ST_ON;
	m_ePreState = ST_END;



	m_pFrameKey = L"ThornEffect";

	m_tFrame.iFrameMotion = 0;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.dwFrameSpeed = 40;
	m_tFrame.dwFrameTime = GetTickCount();
}

void CThornEffect::Render(HDC hdc)
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


void CThornEffect::Late_Update()
{

}

void CThornEffect::Release()
{
}

int CThornEffect::Update()
{
	if (!m_bFlag)
		return OBJ_DEAD;

	if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
		m_bFlag = false;


	Move_Frame();

	Update_Rect();


	return OBJ_NOEVENT;
}

void CThornEffect::Collision()
{
}

void CThornEffect::Motion_Change()
{
	if (m_eCurState != m_ePreState)
	{
		switch (m_eCurState)
		{
		case ST_ON:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		}
		m_ePreState = m_eCurState;
	}
}

