#pragma once
#include "Obj.h"
class CHp :
	public CObj
{

public:
	enum STATE { ST_ON, ST_IDLE,ST_OFF, ST_END};
public:
	CHp();
	virtual ~CHp();

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
	void		Set_Off()
	{
		m_eCurState = ST_OFF;
	}

	void		Set_On()
	{
		m_eCurState = ST_ON;
	};

private:
	HDC		hMemDC;

	STATE	m_eCurState;
	STATE   m_ePreState;
	int		m_tTime;
};

