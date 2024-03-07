#include "stdafx.h"
#include "ScrollMgr.h"
#include"KeyMgr.h"


CScrollMgr*		CScrollMgr::m_pInstance = nullptr;

CScrollMgr::CScrollMgr()
{
}


CScrollMgr::~CScrollMgr()
{
}

void CScrollMgr::Late_Update()
{
	if (m_pTarget)
	{
		POINTPOS	tPos = { m_pTarget->Get_Info().fX, m_pTarget->Get_Info().fY };

		ScrollX = -(tPos.fX - WINCX*0.5);
		ScrollY = -(tPos.fY - WINCY*0.5);
	}
}

void CScrollMgr::Scroll_Lock(float fX, float fY)
{
	if (0.f < ScrollX)
		ScrollX = 0.f;
	if (0.f < ScrollY)
		ScrollY = 0.f;

	if (WINCX - fX > ScrollX)
		ScrollX = WINCX - fX;

	if (WINCY - fY > ScrollY)
		ScrollY = WINCY - fY;
}





