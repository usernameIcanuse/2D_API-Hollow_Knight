#pragma once
#include"Obj.h"

template<typename T>
class CAbstractFactory
{
public:
	static CObj* Create()
	{
		CObj*	temp = new T;
		temp->Initialize();

		return temp;
	}

	/*static CObj* Create(float _fX, float _fY, float _fCX,float _fCY)
	{
		CObj*	temp = new T;
		temp->Initialize();
		
		temp->Set_Pos(_fX, _fY);
		temp->Set_Size(_fCX,_fCY);
		

		return temp;
	}*/

	static CObj* Create(float _fX, float _fY)
	{
		CObj*	temp = new T;
		temp->Set_Pos(_fX, _fY);
		temp->Initialize();

		return temp;
	}


	static CObj* Create(float _fX, float _fY,float _AreaX, float _AreaY)
	{
		CObj*	temp = new T;
		temp->Set_Pos(_fX, _fY);
		temp->Set_Area(_AreaX, _AreaY);
		temp->Initialize();

		return temp;
	}


	static CObj* Create(INFO&	m_tInfo)
	{
		CObj*	temp = new T;
		
		temp->Set_Pos(m_tInfo.fX, m_tInfo.fY);
		temp->Set_Size(m_tInfo.fCX, m_tInfo.fCY);
		temp->Initialize();


		return temp;
	}

};

