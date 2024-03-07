#include "stdafx.h"
#include "Obj.h"


CObj::CObj()
	:m_bDead(false),m_pTarget(nullptr),m_pFrameKey(nullptr),m_bDeath(false),m_fAreaX(0.f), m_fAreaY(0.f)
{
	ZeroMemory(&m_tRect, sizeof(RECT));
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tImageRect, sizeof(RECT));
	ZeroMemory(&m_tImageInfo, sizeof(INFO));
	ZeroMemory(&m_tFrame, sizeof(m_tFrame));
}


CObj::~CObj()
{
}

void	CObj::Update_Rect()
{
	m_tRect.left = (float)(m_tInfo.fX - m_tInfo.fCX*0.5f);
	m_tRect.right = (float)(m_tInfo.fX + m_tInfo.fCX*0.5f);
	m_tRect.top = (float)(m_tInfo.fY - m_tInfo.fCY*0.5f);
	m_tRect.bottom = (float)(m_tInfo.fY + m_tInfo.fCY*0.5f);

	m_tImageRect.left = (float)(m_tInfo.fX - m_tImageInfo.fCX*0.5f);
	m_tImageRect.right = (float)(m_tInfo.fX + m_tImageInfo.fCX*0.5f);
	m_tImageRect.top = (float)(m_tInfo.fY - m_tImageInfo.fCY*0.5f);
	m_tImageRect.bottom = (float)(m_tInfo.fY + m_tImageInfo.fCY*0.5f);
}

void CObj::Move_Frame()
{
	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;
		m_tFrame.dwFrameTime = GetTickCount();

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			m_tFrame.iFrameStart = 0;
	}
}
