#pragma once
#include"Include.h"
class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	void	Set_Area(float _fX, float _fY)
	{
		m_fAreaX = _fX;
		m_fAreaY = _fY;
	}
	void	Set_Pos(float _fX, float _fY)
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
	}

	void    Set_SpeedX(float _fX)
	{
		m_fSpeed.fX = _fX;
	}

	void	Set_Size(float _fCX, float _fCY)
	{
		m_tInfo.fCX = _fCX;
		m_tInfo.fCY = _fCY;
	}

	void	Set_ID(OBJID ID)
	{
		eID = ID;
	}

	void Set_Target(const CObj* _Obj) { m_pTarget = _Obj; }
	void Set_Dead() { m_bDead = true; }
	bool Get_Dead() { return m_bDead; }
	bool Get_Death() { return m_bDeath; }
	const INFO& Get_Info() const { return m_tInfo; }
	const RECT& Get_Rect()const { return m_tRect; }
	const OBJID Get_OBJID()const { return eID; }


public:
	virtual void	Initialize()	PURE;
	virtual void	Render(HDC hdc)		PURE;
	virtual void	Late_Update()  PURE;
	virtual void	Release()		PURE;
	virtual int		Update()		PURE;
	virtual void	Collision()		PURE;
	virtual void	Collision(CObj* Obj) PURE;
	virtual	void	 Motion_Change() PURE;

protected:
	void	Update_Rect();
	void	Move_Frame();
protected:
	OBJID	eID;
	INFO	m_tInfo;
	RECT	m_tRect;
	INFO	m_tImageInfo;
	RECT	m_tImageRect;

	float m_fAreaX;
	float m_fAreaY;

	FRAME	m_tFrame;
	TCHAR*	m_pFrameKey;


	const CObj*  m_pTarget;

	INFO m_fSpeed;

	bool m_bDead;
	bool m_bDeath;
};

