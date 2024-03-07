#include "stdafx.h"
#include "HpBar.h"
#include "BmpMgr.h"
#include "AbstractFactory.h"
#include "Hp.h"


CHpBar::CHpBar()
{
	
}

CHpBar::~CHpBar()
{
	Release();
}

void CHpBar::Initialize()
{

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/HP/HP_Guage.bmp", L"Player_HP_Guage");
	


}

void CHpBar::Render(HDC hdc)
{
	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Player_HP_Guage");

	GdiTransparentBlt(hdc,
		10,
		20,
		180,
		117,
		hMemDC,
		0,
		0,
		180,
		117,
		RGB(193, 193, 194));




}

void CHpBar::Late_Update()
{
}

void CHpBar::Release()
{
	
}

int CHpBar::Update()
{
	return OBJ_NOEVENT;
}

void CHpBar::Collision()
{
}
