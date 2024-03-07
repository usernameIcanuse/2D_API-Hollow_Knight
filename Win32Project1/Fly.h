#pragma once
#include "Obj.h"
class CFly :
	public CObj
{
private:
	enum STATE { ST_MOVE,ST_DEAD,ST_END};

public:
	CFly();
	virtual	~CFly();

public:
	virtual void	Initialize();
	virtual void	Render(HDC hdc);
	virtual void	Late_Update();
	virtual void	Release();
	virtual int		Update();
	virtual void	Collision();
	virtual void	Collision(CObj* Obj);
	virtual	void	Motion_Change();



private:
	HDC		hMemDC;

	STATE	m_eCurState;
	STATE   m_ePreState;

	bool	m_bFreeze;
	int		m_iFreeze_Time;

private:
	int		m_iHit;

	bool	m_bLand;
	bool	m_bDeathFrame;

	int		m_iTime;


};

