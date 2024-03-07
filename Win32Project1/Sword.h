#pragma once
#include"Obj.h"

class CSword : public CObj
{
public:
	enum STATE
	{
		ST_LEFT,
		ST_RIGHT,
		ST_UP_LEFT,
		ST_UP_RIGHT,
		ST_DOWN_LEFT,
		ST_DOWN_RIGHT
	};

public:
	CSword();
	virtual ~CSword();

public:
	void Set_Dir(DIR eDir, DIR eBase);
	void Set_True() { m_bFlag = true; dwTime = GetTickCount(); }
	bool Get_True() { return m_bFlag; }
	DIR	 Get_Dir() { return eEffectDir; }

public:
	virtual void Initialize()	;
	virtual void Render(HDC hdc);
	virtual void Late_Update()  ;
	virtual void Release()		;
	virtual int  Update()		;
	virtual void	Collision()	;
	virtual void	Collision(CObj* Obj);
	virtual void	Motion_Change();

private:
	
	HDC		hMemDC;


	STATE	m_eCurState;
	STATE   m_ePreState;

	float   m_fDirX;
	float	m_fDirY;

	bool	m_bFlag;
	

	DWORD   dwTime;

	bool	m_bThorn;

	DIR		eEffectDir;
};

