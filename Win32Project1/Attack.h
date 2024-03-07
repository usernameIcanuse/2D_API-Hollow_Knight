#pragma once
#include "Obj.h"
class CAttack :
	public CObj
{
public:
	enum STATE { ST_STANDBY,ST_MOVE,ST_END};

public:
	CAttack();
	virtual ~CAttack();

public:
	virtual void	Initialize();
	virtual void	Render(HDC hdc);
	virtual void	Late_Update();
	virtual void	Release();
	virtual int		Update();
	virtual void	Collision();
	virtual void	Collision(CObj* Obj) {}
	virtual void	Motion_Change();

public:
	void	Set_Speed() { m_fSpeed.fCX *= -1.f; }

private:
	HDC		hMemDC;

	float m_PreInfoX;

	STATE	m_eCurState;
	STATE   m_ePreState;
};

