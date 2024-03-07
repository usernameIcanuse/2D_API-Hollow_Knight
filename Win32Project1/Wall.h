#pragma once
#include "Obj.h"
class CWall :
	public CObj
{
public:
	CWall();
	~CWall();
public:
	virtual void Initialize();
	virtual void Render(HDC hdc);
	virtual void Late_Update();
	virtual void Release();
	virtual int  Update();
	virtual void	Collision();
	virtual void	Collision(CObj* Obj);
	virtual void	Motion_Change() {}

};

