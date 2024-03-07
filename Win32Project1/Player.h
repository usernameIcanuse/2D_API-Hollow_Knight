#pragma once
#include "Obj.h"


class CPlayer :
	public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	enum STATE { ST_IDLE,
		ST_WALK,
		ST_ATTACK,
		ST_ATTACK_DOWN,
		ST_ATTACK_UP,
		ST_JUMP_START,
		ST_JUMP_HIGHEST,
		ST_JUMP_FALL,
		ST_JUMP_LAND,
		ST_ATTACKED,
		ST_DASH,
		ST_END };


public:
	void Key_Input();
	void Get_Coin() { ++m_iCoin; }
	int Coin() { return m_iCoin; }
	void jumping();
	void Reflect() { m_fSpeed.fY *= -1.f; }
	void Reflect(float _fY) { m_fSpeed.fY = _fY; }
	


public:
	virtual void	Initialize();
	virtual void	Render(HDC hdc);
	virtual void	Late_Update();
	virtual void	Release();
	virtual int		Update();
	virtual void	Collision();
	virtual void	Collision(CObj* Obj);
	virtual void	Motion_Change();
private:
	
	DIR		eDir;
	
	bool	m_bJump;
	int     m_iJumpcount;
	
	int		m_iCoin;

	bool	m_bWall;


	bool	m_bLand;//땅에 있을 때 확인
	bool	m_bLandMotion;//착지 모션 위한 bool
	bool	m_bJumpMotion;//점프 방향 바뀔 때 자세 바꾸는 모션 위한 bool
	bool	m_bAttackMotion;

	bool	m_bDashMotion;

	HDC		hMemDC;
	

	STATE	m_eCurState;
	STATE   m_ePreState;


private:
	int		m_iHP;
	bool	m_bFreeze;
	int		m_bFreezeTime;


	CObj*	m_pHeal;
	CObj*	m_pDashEffect;

};



