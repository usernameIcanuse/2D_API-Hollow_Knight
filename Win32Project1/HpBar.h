#pragma once
#include "Obj.h"
class CHpBar :
	public CObj
{
public:
public:
	CHpBar();
	virtual ~CHpBar();

public:
	virtual void	Initialize();
	virtual void	Render(HDC hdc);
	virtual void	Late_Update();
	virtual void	Release();
	virtual int		Update();
	virtual void	Collision();
	virtual void	Collision(CObj* Obj) {};
	virtual void	Motion_Change() {};

private:
	HDC		hMemDC;
	
};

