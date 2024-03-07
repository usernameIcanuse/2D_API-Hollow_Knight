#include "stdafx.h"
#include "Item.h"
#include "Include.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "LineMgr.h"


CItem::CItem()
{
}


CItem::~CItem()
{
}


void CItem::Initialize()
{
	m_tInfo.fCX = m_tInfo.fCY = 30.f;
	eID = OBJ_ITEM;

	m_fSpeed.fCY = 0.98f;

	m_fSpeed.fY = -5.f;


	m_bLand = false;
	m_iBounce = 0;
	
}

void CItem::Render(HDC hdc)
{
	
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Coin");


	GdiTransparentBlt(hdc,
		(int)m_tRect.left +CScrollMgr::Get_Instance()->Get_ScrollX(),
		(int)m_tRect.top + CScrollMgr::Get_Instance()->Get_ScrollY(),
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMemDC,
		0, 0,
		m_tInfo.fCX,
		m_tInfo.fCY,
		RGB(192, 192, 192));

}

int CItem::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if (!m_bLand)
	{
		m_tInfo.fY += m_fSpeed.fY;
		m_tInfo.fX += m_fSpeed.fX;

		if(m_fSpeed.fY<15.f)
			m_fSpeed.fY += m_fSpeed.fCY;
	}

	Update_Rect();

	return OBJ_NOEVENT;
}

void CItem::Late_Update()
{
	float fY = 0.f;
	bool bCollision = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &fY, m_tInfo.fY);

	if (bCollision && fY <= m_tRect.bottom)
	{	
		m_tInfo.fY = fY - m_tInfo.fCY * 0.5f;
		
		if (m_iBounce < 3)
		{	
		
			m_fSpeed.fY *= -0.4f;
			++m_iBounce;
		
		}
		else
		{
			m_bLand = true;
			m_fSpeed.fY= m_fSpeed.fX = 0.f;
			
		}	
		
	}

	else if (bCollision)
	{
		m_bLand = false;
	}

}

void	CItem::Collision(CObj* Obj)
{
	if (OBJ_WALL == Obj->Get_OBJID())
	{
		if (m_tInfo.fX < Obj->Get_Rect().left)//왼쪽 충돌
		{

			float dx = m_tRect.right - Obj->Get_Rect().left;
			m_tInfo.fX -= dx;

		}
		else if (m_tInfo.fX > Obj->Get_Rect().right)//오른쪽 충돌
		{

			float dx = Obj->Get_Rect().right - m_tRect.left;
			m_tInfo.fX += dx;

		}
		else
		{
			if (m_tInfo.fY > Obj->Get_Rect().bottom)//아래 충돌
			{

				if (m_tRect.top < Obj->Get_Rect().bottom)
				{
					float dy = Obj->Get_Rect().bottom - m_tRect.top;
					m_tInfo.fY += dy;
				}
			}

		}
	}
	if(OBJ_PLAYER == Obj->Get_OBJID())
		Set_Dead();
}

void CItem::Collision()
{
	
}



void CItem::Release()
{
}


