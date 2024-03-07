#pragma once
#include "Obj.h"
class CThorn :
	public CObj
{
public:
	CThorn();
	~CThorn();
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

