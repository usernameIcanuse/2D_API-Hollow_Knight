#pragma once
#include "Obj.h"
class CSemiBoss :
	public CObj
{
public:
	enum STATE { ST_STANDBY, ST_WAKEUP, ST_WALK, ST_ATTACK, ST_DASH, ST_DEAD, ST_END };

public:
	CSemiBoss();
	virtual ~CSemiBoss();

public:
	virtual void	Initialize();
	virtual void	Render(HDC hdc);
	virtual void	Late_Update();
	virtual void	Release();
	virtual int		Update();
	virtual void	Collision();
	virtual void	Collision(CObj* Obj);
	virtual	void    Motion_Change();

public:
	void		Update_Area();

private:
	HDC		hMemDC;

	STATE	m_eCurState;
	STATE   m_ePreState;

private:
	int		m_iHit;


	INFO	m_t_Near_Info;
	RECT	m_t_Near_Rect;
	
	bool	m_bNearArea;
	
	bool	m_bAttackMotion;

	bool	m_bWakeUp;
	bool	m_bWalk;
	bool	m_bSwitch;

	int		m_iTime;
	int		m_iButtTime;

	int		m_iDeathTime;
	bool	m_bDeathFrame;

	bool m_bFreeze;
	int m_iFreeze_Time;

	bool m_bAttack;
};
