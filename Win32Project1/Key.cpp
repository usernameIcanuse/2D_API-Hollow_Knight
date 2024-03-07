#include "stdafx.h"
#include "Key.h"
#include "stdafx.h"
#include "Item.h"
#include "Include.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "LineMgr.h"


CKey::CKey()
{
}


CKey::~CKey()
{
}


void CKey::Initialize()
{
	m_tInfo.fCX = 300.f;
	m_tInfo.fCY = 150.f;
	m_tImageInfo.fCX = 300.f;
	m_tImageInfo.fCY = 150.f;
	
	eID = OBJ_ITEM;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Coin/º¸½º·ëÅ°.bmp",L"Key");

}

void CKey::Render(HDC hdc)
{

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Key");


	GdiTransparentBlt(hdc,
		(int)m_tRect.left + CScrollMgr::Get_Instance()->Get_ScrollX(),
		(int)m_tRect.top + CScrollMgr::Get_Instance()->Get_ScrollY(),
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMemDC,
		0, 0,
		m_tInfo.fCX,
		m_tInfo.fCY,
		RGB(192, 192, 192));

}

int CKey::Update()
{
	if (m_bDead)
		return OBJ_DEAD;



	Update_Rect();

	return OBJ_NOEVENT;
}

void CKey::Late_Update()
{
	
}

void	CKey::Collision(CObj* Obj)
{
	
	if (OBJ_PLAYER == Obj->Get_OBJID())
		Set_Dead();
}

void CKey::Collision()
{

}



void CKey::Release()
{
}


