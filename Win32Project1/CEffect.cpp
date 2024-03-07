#include "stdafx.h"
#include "CEffect.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "SoundMgr.h"


CEffect::CEffect()
{
}

CEffect::~CEffect()
{
	Release();
}

void CEffect::Initialize()
{


	m_tInfo.fCX = m_tInfo.fCY = 0.f;

	m_bFlag = true;
	m_eCurState = ST_LEFT;
	m_ePreState = ST_END;

}

void CEffect::Render(HDC hdc)
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
		RGB(194, 194, 195));
	
	if (!m_bFlag)
	{
		m_tImageRect.bottom = m_tImageRect.left = m_tImageRect.right = m_tImageRect.top = -1000.f;
	}
}
	

void CEffect::Late_Update()
{
	
}

void CEffect::Release()
{
}

int CEffect::Update()
{
	if (!m_bFlag)
		return OBJ_DEAD;
	
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
			m_bFlag = false;
	

		Move_Frame();

		Update_Rect();

	
	return OBJ_NOEVENT;
}

void CEffect::Collision()
{
}

void CEffect::Motion_Change()
{
	if (m_eCurState != m_ePreState)
	{
		switch (m_eCurState)
		{
		case ST_LEFT:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.dwFrameSpeed = 40;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ST_RIGHT:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.dwFrameSpeed = 40;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CEffect::Set_Dir(DIR eDir)
{
	srand(unsigned(time(NULL)));

	switch (eDir)
	{
	case ST_LEFT:
		if (rand() % 2 == 1)
		{
			m_pFrameKey = L"Effect1Left";
			m_tImageInfo.fCX = 780.f;
			m_tImageInfo.fCY = 190.f;
		}
		else
		{
			m_pFrameKey = L"Effect2Left";
			m_tImageInfo.fCX = 400.f;
			m_tImageInfo.fCY = 280.f;
		}
		m_eCurState = ST_LEFT;
		Motion_Change();
		break;

	case ST_RIGHT:
		if (rand() % 2 == 1)
		{
			m_pFrameKey = L"Effect1Right";
			m_tImageInfo.fCX = 780.f;
			m_tImageInfo.fCY = 190.f;
		}
		else
		{
			m_pFrameKey = L"Effect2Right";
			m_tImageInfo.fCX = 400.f;
			m_tImageInfo.fCY = 280.f;
		}
		m_eCurState = ST_RIGHT;
		Motion_Change();
		break;
	}
}
