#pragma once
#include "Obj.h"
class CEffect :
	public CObj
{
public:
	enum STATE
	{
		ST_LEFT,
		ST_RIGHT,
		ST_END
	};
public:
	CEffect();
	virtual ~CEffect();

public:
	virtual void Initialize();
	virtual void Render(HDC hdc);
	virtual void Late_Update();
	virtual void Release();
	virtual int  Update();
	virtual void	Collision();
	virtual void	Collision(CObj* Obj) {}
	virtual void	Motion_Change();

public:
	void	Set_Dir(DIR eDir);

private:
	HDC		hMemDC;

	STATE	m_eCurState;
	STATE   m_ePreState;

	bool	m_bFlag;
};

