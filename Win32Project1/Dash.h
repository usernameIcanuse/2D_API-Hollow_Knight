#pragma once
#include "Obj.h"
class CDash :
	public CObj
{
public:
	enum STATE{ST_ON,ST_END};

public:
	CDash();
	~CDash();

public:

	void	Set_Dir(DIR eDir)
	{
		switch (eDir)
		{
		case LEFT:
			m_pFrameKey = L"DashEffect_Left";
			break;

		case RIGHT:
			m_pFrameKey = L"DashEffect_Right";
			break;
		}
	}
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

	bool  m_bFlag;
};

