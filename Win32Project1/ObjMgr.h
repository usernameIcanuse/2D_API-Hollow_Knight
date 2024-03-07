#pragma once
#include"Obj.h"
class CObjMgr
{
private:
	CObjMgr();
	~CObjMgr();

public:
	CObj*		Get_Target(OBJID eID, CObj* pObj);
	list<CObj*>*  Get_List(OBJID eID) 
	{ 
		if (eID >= OBJ_END) return nullptr;
		
		return &m_ObjList[eID]; 
	}
	

public:
	void AddObject(OBJID eID, CObj* pObj);
	int Update();
	void Late_Update();
	void Render(HDC hdc);
	void Delete_OBJ(OBJID eID);
	void Release();
	void	Load_Data1(OBJID eID);
	void	Load_Data2(OBJID eID);
	void	Load_Data3(OBJID eID);
	void	Load_Data4(OBJID eID);

	
private:
	list<CObj*>		m_ObjList[OBJ_END];

public:
	static CObjMgr*		Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CObjMgr;

		return m_pInstance;
	}

	static void		Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CObjMgr*		m_pInstance;
};

