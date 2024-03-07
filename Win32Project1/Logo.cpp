#include "stdafx.h"
#include "Logo.h"

#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"

CLogo::CLogo()
{
}


CLogo::~CLogo()
{
	Release();
}

void CLogo::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/CurSur.bmp", L"Cursor");

	m_tMouse.fCX = m_tMouse.fCY = 30.f;
}

void CLogo::Update()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	m_tMouse.fX = pt.x;
	m_tMouse.fY = pt.y;

	m_tMouseRect.left = (float)(m_tMouse.fX - m_tMouse.fCX*0.5f);
	m_tMouseRect.right = (float)(m_tMouse.fX + m_tMouse.fCX*0.5f);
	m_tMouseRect.top = (float)(m_tMouse.fY - m_tMouse.fCY*0.5f);
	m_tMouseRect.bottom = (float)(m_tMouse.fY + m_tMouse.fCY*0.5f);


}

void CLogo::Late_Update()
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE1);
		return;
	}
}

void CLogo::Render(HDC hdc)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Logo");
	HDC		hMouseDC = CBmpMgr::Get_Instance()->Find_Image(L"Cursor");
	BitBlt(hdc, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	GdiTransparentBlt(hdc,
		(int)m_tMouseRect.left,
		(int)m_tMouseRect.top, 
		(int)m_tMouse.fCX,
		(int)m_tMouse.fCY,
		hMouseDC,
		0, 0,
		m_tMouse.fCX,
		m_tMouse.fCY,
		RGB(193, 193, 194));
	
}

void CLogo::Release(void)
{
}
