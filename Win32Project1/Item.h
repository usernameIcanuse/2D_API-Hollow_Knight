#pragma once
#include "Obj.h"

class CItem :
	public CObj
{
public:
	CItem();
	~CItem();


public:
	virtual void Initialize();
	virtual void Render(HDC hdc);
	virtual void Late_Update();
	virtual void Release();
	virtual int  Update();
	virtual void	Collision();
	virtual void	Collision(CObj* Obj);
	virtual void	Motion_Change() {}

private:
	bool m_bLand;
	int  m_iBounce;
};

