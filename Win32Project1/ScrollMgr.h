#pragma once

#include"Include.h"
#include "Obj.h"
class CScrollMgr
{
private:
	CScrollMgr();
	~CScrollMgr();

public:
	float	Get_ScrollX() { return ScrollX; }
	float	Get_ScrollY() { return ScrollY; }

	void	Set_ScrollX(float _fX) { ScrollX += _fX; }
	void	Set_ScrollY(float _fY) { ScrollY += _fY; }

public:
	//void	Key_Input(float fX,float fY);
	void		Initialize() { ScrollX = 0.f; ScrollY = 0.f; }

	void		Set_Target(CObj*	_pTarget) { m_pTarget = _pTarget; }
	void		Late_Update();
	void		Scroll_Lock(float fX, float fY);

public:
	static CScrollMgr*		Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CScrollMgr;
		}

		return m_pInstance;
	}

	static void		Destroy_Instance()
	{
		if(m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;		
		}
	}

private:
	static CScrollMgr*		m_pInstance;
	
	float	ScrollX;
	float	ScrollY;

	CObj*		m_pTarget;

};

