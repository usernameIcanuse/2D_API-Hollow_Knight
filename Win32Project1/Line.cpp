#include "stdafx.h"
#include "Line.h"
#include "ScrollMgr.h"
CLine::CLine()
	:m_tInfo()
{
}
CLine::CLine(LINEINFO tInfo)
	:m_tInfo(tInfo)
{

}

CLine::CLine(POINTPOS& tLeft, POINTPOS& tRight)
	:m_tInfo(tLeft,tRight)
{

}

CLine::~CLine()
{
}

void CLine::Render(HDC hdc)
{
	MoveToEx(hdc, (int)m_tInfo.tLeftPoint.fX + CScrollMgr::Get_Instance()->Get_ScrollX(), (int)m_tInfo.tLeftPoint.fY + CScrollMgr::Get_Instance()->Get_ScrollY(), nullptr);
	LineTo(hdc, (int)m_tInfo.tRightPoint.fX + CScrollMgr::Get_Instance()->Get_ScrollX(), (int)m_tInfo.tRightPoint.fY + CScrollMgr::Get_Instance()->Get_ScrollY());
}

void CLine::Update()
{
	
}
