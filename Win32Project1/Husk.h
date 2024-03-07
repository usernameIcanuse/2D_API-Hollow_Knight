#pragma once
#include "Obj.h"
class CHusk :
	public CObj
{
public:
	enum STATE { ST_IDLE, ST_WALK, ST_ATTACK, ST_DEAD, ST_END};

public:
	CHusk();
	~CHusk();

public:
	virtual void	Initialize();
	virtual void	Render(HDC hdc);
	virtual void	Late_Update();
	virtual void	Release();
	virtual int		Update();
	virtual void	Collision();
	virtual void	Collision(CObj* Obj);
	virtual	void	Motion_Change();

public:
	void	Update_Area();

private:
	HDC		hMemDC;

	STATE	m_eCurState;
	STATE   m_ePreState;

	int		m_iTime;

	bool	m_bFreeze;
	int		m_iFreeze_Time;

private:
	int		m_iHit;

	INFO	m_tArea_Info;
	RECT	m_tArea_Rect;
	
	
	bool	m_bAttackMotion;
	//인식 범위 어디에서 리스트를 만들어 줘야 하는지 고민


	bool	m_bLand;
	bool	m_bDeathFrame;

	int		m_iDeathTime;
};

