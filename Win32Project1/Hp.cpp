#include "stdafx.h"
#include "Hp.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CHp::CHp()
{
}

CHp::~CHp()
{
	Release();
}

void CHp::Initialize()
{
	
	m_tImageInfo.fCX = 60.f;
	m_tImageInfo.fCY = 120.f;

	m_tTime = 0;

	m_eCurState = ST_ON;
	m_ePreState = ST_END;
	m_pFrameKey = L"Hp";


	m_tFrame.iFrameMotion = 0;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 5;
	m_tFrame.dwFrameSpeed = 70;
	m_tFrame.dwFrameTime = GetTickCount();

}

void CHp::Render(HDC hdc)
{
	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hdc,
		(int)m_tImageRect.left,
		(int)m_tImageRect.top,
		(int)m_tImageInfo.fCX,
		(int)m_tImageInfo.fCY,
		hMemDC,
		m_tFrame.iFrameMotion *(int)m_tImageInfo.fCX,
		m_tFrame.iFrameStart*(int)m_tImageInfo.fCY,
		(int)m_tImageInfo.fCX,
		(int)m_tImageInfo.fCY,
		RGB(192, 192, 192));

}

void	CHp::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case ST_ON:
			m_tFrame.iFrameMotion = 1;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case ST_IDLE:
			m_tFrame.iFrameMotion = 2;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.dwFrameSpeed = 40;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ST_OFF:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		}
		m_ePreState = m_eCurState;
	}
}

void CHp::Late_Update()
{
	Motion_Change();
}

void CHp::Release()
{
}

int CHp::Update()
{
	Motion_Change();
	if (ST_OFF == m_eCurState)
	{
		if (m_tFrame.iFrameStart < m_tFrame.iFrameEnd)
			Move_Frame();
	}
	else if (ST_IDLE == m_eCurState)
	{
		++m_tTime;
		if (100 < m_tTime)
		{
			Move_Frame();
			if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
			{
				m_tTime = 0;
				m_tFrame.iFrameStart = 0;
			}
		}
	}
	else if (ST_ON == m_eCurState)
	{
		Move_Frame();
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
		{
			m_eCurState = ST_IDLE;
			Motion_Change();
		}
	}
	
	
	Update_Rect();
	return OBJ_NOEVENT;
}

void CHp::Collision()
{
}
