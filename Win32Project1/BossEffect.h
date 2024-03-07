#pragma once
#include "Obj.h"
class CBossEffect :
	public CObj
{
public:
	enum STATE
	{
		ST_ON,
		ST_END
	};
public:
	CBossEffect();
	virtual ~CBossEffect();

public:
	virtual void Initialize();
	virtual void Render(HDC hdc);
	virtual void Late_Update();
	virtual void Release();
	virtual int  Update();
	virtual void	Collision();
	virtual void	Collision(CObj* Obj) {}
	virtual void	Motion_Change();


private:
	HDC		hMemDC;

	STATE	m_eCurState;
	STATE   m_ePreState;

	bool	m_bFlag;

};

