#pragma once
#include "Obj.h"
class CBoss :
	public CObj
{public:
	enum STATE { ST_IDLE, ST_JUMP, ST_ATTACK, ST_JUMPATTACK, ST_DEAD, ST_END };

public:
	CBoss();
	virtual ~CBoss();

public:
	virtual void	Initialize();
	virtual void	Render(HDC hdc);
	virtual void	Late_Update();
	virtual void	Release();
	virtual int		Update();
	virtual void	Collision();
	virtual void	Collision(CObj* Obj);
	virtual	void    Motion_Change();


private:
	HDC		hMemDC;

	STATE	m_eCurState;
	STATE   m_ePreState;

private:
	int		m_iHit;


	bool	m_bAttackMotion;

	bool	m_bJump;
	bool	m_bJumpAttack;
	bool	m_bStopFrame;


	bool	m_bLand;

	bool	m_bHit;

	int		m_iTime;


	int		m_iDeathTime;
	bool	m_bDeathFrame;

	bool m_bFreeze;
	int m_iFreeze_Time;

};

