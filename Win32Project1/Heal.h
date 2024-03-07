#pragma once
#include "Obj.h"
class CHeal :
	public CObj
{
public:
	enum STATE{ST_CHARGE,ST_HEAL,ST_END};
public:
	CHeal();
	~CHeal();

public:
	void	Set_On() { m_bFlag = true; }
	void	Get_HPIndex(int iHP) { m_iIndex = iHP; }
public:
	virtual void Initialize();
	virtual void Render(HDC hdc);
	virtual void Late_Update();
	virtual void Release();
	virtual int  Update();
	virtual void	Collision();
	virtual void	Collision(CObj* Obj);
	virtual void	Motion_Change();

private:
	HDC		hMemDC;

	STATE	m_eCurState;
	STATE   m_ePreState;

	bool	m_bFlag;
	int		m_iIndex;

};

