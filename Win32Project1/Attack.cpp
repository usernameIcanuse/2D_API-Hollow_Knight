#include "stdafx.h"
#include "Attack.h"
#include "ScrollMgr.h"
#include "LineMgr.h"
#include "BmpMgr.h"
#include "ObjMgr.h"

CAttack::CAttack()
{
}

CAttack::~CAttack()
{
	Release();
}

void CAttack::Initialize()
{
	eID = OBJ_ATTACK;
	m_tImageInfo.fCX = 230.f;
	m_tImageInfo.fCY = 220.f;

	
	m_tInfo.fCX = 180.f;
	m_tInfo.fCY = 60.f;
	m_PreInfoX = m_tInfo.fX;

	float fY = 0.f;
	bool bCollision = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &fY, m_tInfo.fY);

	m_tInfo.fY = fY - m_tInfo.fCY * 0.5f;

	m_fSpeed.fX = m_fSpeed.fY=0.f;
	m_fSpeed.fCY = 0.f;
	m_fSpeed.fCX = -0.5f;//¿ÞÂÊ °ø°Ý

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/Monster/SemiBoss_Attack.bmp", L"SemiBoss_Attack");


	m_eCurState = ST_STANDBY;
	m_ePreState = ST_END;
	m_pFrameKey = L"SemiBoss_Attack";

	m_tFrame.iFrameMotion = 0;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.dwFrameSpeed = 40;
	m_tFrame.dwFrameTime = GetTickCount();

}

void CAttack::Render(HDC hdc)
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
	//Rectangle(hdc, m_tImageRect.left, m_tImageRect.top, m_tImageRect.right, m_tImageRect.bottom);
}

void CAttack::Late_Update()
{
	
	/*float  fY = m_tImageRect.bottom - m_tRect.bottom;
	m_tImageRect.bottom -= fY;
	m_tImageRect.top -= fY;
	*/


	float fY = 0.f;
	bool bCollision = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &fY,m_tInfo.fY);

	m_tInfo.fY = fY - m_tInfo.fCY * 0.5f - 50.f;


	if (500 <= abs(m_tInfo.fX - m_PreInfoX))
		m_bDead = true;
	
}

void CAttack::Release()
{
}

int CAttack::Update()
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}

	m_tInfo.fX += m_fSpeed.fX;
	m_fSpeed.fX += m_fSpeed.fCX;
	
	if (ST_STANDBY == m_eCurState)
	{
		
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
		{
			m_eCurState = ST_MOVE;
		}
	}

	else if (ST_MOVE== m_eCurState)
	{
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
		{
			m_tFrame.iFrameStart = 0;
		}
	}

	
	Motion_Change();

	Move_Frame();

	Update_Rect();

	return OBJ_NOEVENT;
}

void CAttack::Collision()
{
}

void CAttack::Motion_Change()
{
	if (m_eCurState != m_ePreState)
	{
		switch (m_eCurState)
		{
		case ST_STANDBY:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.dwFrameSpeed = 40;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ST_MOVE:
			m_tFrame.iFrameMotion = 1;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.dwFrameSpeed = 20;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}

		m_ePreState = m_eCurState;
	}
}
