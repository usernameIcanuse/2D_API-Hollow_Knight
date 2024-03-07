#pragma once
#include "Obj.h"
class CNumber :
	public CObj
{

public:
	CNumber();
	~CNumber();
public:
	void	Change_Num(int i);

public:
	virtual void Initialize();
	virtual void Render(HDC hdc);
	virtual void Late_Update();
	virtual void Release();
	virtual int  Update();
	virtual void	Collision();
	virtual void	Collision(CObj* Obj);
	virtual void	Motion_Change() {};

private:
	HDC		hMemDC;


};

