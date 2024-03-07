#include "stdafx.h"
#include "Number.h"
#include "Include.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "LineMgr.h"


CNumber::CNumber()
{
}


CNumber::~CNumber()
{
}

void CNumber::Change_Num(int i)
{
	switch (i)
	{
	case 0:
		m_pFrameKey = L"0";
		break;

	case 1:
		m_pFrameKey = L"1";
		break;

	case 2:
		m_pFrameKey = L"2";
		break;

	case 3:
		m_pFrameKey = L"3";
		break;

	case 4:
		m_pFrameKey = L"4";
		break;

	case 5:
		m_pFrameKey = L"5";
		break;

	case 6:
		m_pFrameKey = L"6";
		break;

	case 7:
		m_pFrameKey = L"7";
		break;

	case 8:
		m_pFrameKey = L"8";
		break;

	case 9:
		m_pFrameKey = L"9";
		break;
	}
}


void CNumber::Initialize()
{
	m_tInfo.fCX = 15.f;
	m_tInfo.fCY = 20.f;


	m_pFrameKey = L"NULL";

}

void CNumber::Render(HDC hdc)
{

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);


	GdiTransparentBlt(hdc,
		(int)m_tRect.left, 
		(int)m_tRect.top ,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMemDC,
		0, 0,
		m_tInfo.fCX,
		m_tInfo.fCY,
		RGB(62, 62, 62));

}


int CNumber::Update()
{

	Update_Rect();

	return OBJ_NOEVENT;
}

void CNumber::Late_Update()
{
	
}

void	CNumber::Collision(CObj* Obj)
{

}

void CNumber::Collision()
{

}



void CNumber::Release()
{
}