#pragma once
#include "Obj.h"
class CGoal :
	public CObj
{
public:
	CGoal();
	~CGoal();

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

