#include "stdafx.h"
#include "ObjMgr.h"
#include"CollisionMgr.h"
#include "AbstractFactory.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"
#include"Goal.h"
#include "Item.h"
#include "Wall.h"
#include "Thorn.h"
CObjMgr*		CObjMgr::m_pInstance = nullptr;


CObjMgr::CObjMgr()
{
}


CObjMgr::~CObjMgr()
{
	Release();
}

CObj* CObjMgr::Get_Target(OBJID eID, CObj * pObj)
{
	if(m_ObjList[eID].empty())
		return nullptr;

	CObj*	pTarget = nullptr;
	float Diagonal = 987654321.f;

	for (auto& iter : m_ObjList[eID])
	{
		if (iter->Get_Dead()) continue;

		float dx = iter->Get_Info().fX - pObj->Get_Info().fX;
		float dy = iter->Get_Info().fY - pObj->Get_Info().fY;

		float tmp = sqrtf(dx*dx + dy*dy);
		if (tmp < Diagonal)
		{
			pTarget = iter;
			Diagonal = tmp;
		}
	}

	return pTarget;
}

void CObjMgr::AddObject(OBJID eID, CObj * pObj)
{
	if (OBJ_END <= eID || pObj == nullptr)
		return;

	m_ObjList[eID].push_back(pObj);
}



int CObjMgr::Update()
{

	for (int i = 0; i < OBJ_END; ++i)
	{
		auto& iter = m_ObjList[i].begin();
		for (; iter != m_ObjList[i].end();)
		{
			
			int Flag = (*iter)->Update();
			if (OBJ_DEAD == Flag)
			{
				SAFE_DELETE(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else ++iter;
		}
	}
	
	
	CCollisionMgr::Collision_Rect(m_ObjList[OBJ_SWORD], m_ObjList[OBJ_MONSTER]);
	CCollisionMgr::Collision_Rect(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_MONSTER]);
	CCollisionMgr::Collision_Rect(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_ATTACK]);

	CCollisionMgr::Collision_Rect(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_ITEM]);
	CCollisionMgr::Collision_Rect(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_WALL]);
	CCollisionMgr::Collision_Rect(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_WALL]);
	CCollisionMgr::Collision_Rect(m_ObjList[OBJ_ITEM], m_ObjList[OBJ_WALL]);

	CCollisionMgr::Collision_Rect(m_ObjList[OBJ_SWORD], m_ObjList[OBJ_THORN]);
	CCollisionMgr::Collision_Rect(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_THORN]);
	
	return 0;
}

void CObjMgr::Late_Update()
{
	
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
		{
			
			iter->Late_Update();
		}
	}

	
}

void CObjMgr::Render(HDC hdc)
{

	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
		{
			
			iter->Render(hdc);
		}
	}
}

void CObjMgr::Delete_OBJ(OBJID eID)
{

	auto& iter = m_ObjList[eID].begin();
	for (; iter != m_ObjList[eID].end();)
	{
		if (*iter)
		{
			SAFE_DELETE(*iter);
			iter = m_ObjList[eID].erase(iter);
		}
	}
}



void	CObjMgr::Load_Data1(OBJID eID)
{
	if (OBJ_WALL == eID)
	{
		HANDLE	hFile = CreateFile(L"../Stage/Stage1/Obstacle1.dat",
			GENERIC_READ,
			NULL,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		if (INVALID_HANDLE_VALUE == hFile)
		{
			MessageBox(g_hWnd, _T("Save File"), _T("Fail"), MB_OK);
			return;
		}

		DWORD		dwByte = 0;


		INFO	m_tInfo{};
		while (true)
		{
			ReadFile(hFile, &m_tInfo, sizeof(m_tInfo), &dwByte, nullptr);

			if (0 == dwByte)
				break;

			CObjMgr::Get_Instance()->AddObject(OBJ_WALL, CAbstractFactory<CWall>::Create(m_tInfo));
		}

		CloseHandle(hFile);
		//MessageBox(g_hWnd, _T("Load 己傍"), _T("己傍"), MB_OK);
	}

	else if (OBJ_GOAL== eID)
	{
		HANDLE	hFile = CreateFile(L"../Stage/Stage1/Goal1.dat",
			GENERIC_READ,
			NULL,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		if (INVALID_HANDLE_VALUE == hFile)
		{
			//MessageBox(g_hWnd, _T("Save File"), _T("Fail"), MB_OK);
			return;
		}


		DWORD dwByte = 0;
		INFO	m_tInfo{};

		while (true)
		{
			ReadFile(hFile, &m_tInfo, sizeof(m_tInfo), &dwByte, nullptr);

			if (0 == dwByte)
				break;

			CObjMgr::Get_Instance()->AddObject(OBJ_GOAL, CAbstractFactory<CGoal>::Create(m_tInfo));
		}



		CloseHandle(hFile);


		//MessageBox(g_hWnd, _T("Load 己傍"), _T("己傍"), MB_OK);
	}
	
	
}

void CObjMgr::Load_Data2(OBJID eID)
{
	if (OBJ_WALL == eID)
	{
		HANDLE	hFile = CreateFile(L"../Stage/Stage2/Obstacle2.dat",
			GENERIC_READ,
			NULL,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		if (INVALID_HANDLE_VALUE == hFile)
		{
			MessageBox(g_hWnd, _T("Save File"), _T("Fail"), MB_OK);
			return;
		}

		DWORD		dwByte = 0;


		INFO	m_tInfo{};
		while (true)
		{
			ReadFile(hFile, &m_tInfo, sizeof(m_tInfo), &dwByte, nullptr);

			if (0 == dwByte)
				break;

			CObjMgr::Get_Instance()->AddObject(OBJ_WALL, CAbstractFactory<CWall>::Create(m_tInfo));
		}

		CloseHandle(hFile);
		//MessageBox(g_hWnd, _T("Load 己傍"), _T("己傍"), MB_OK);
	}
	else if (OBJ_THORN == eID)
	{
		HANDLE	hFile = CreateFile(L"../Stage/Stage2/Thorn2.dat",
			GENERIC_READ,
			NULL,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		if (INVALID_HANDLE_VALUE == hFile)
		{
			MessageBox(g_hWnd, _T("Save File"), _T("Fail"), MB_OK);
			return;
		}


		DWORD dwByte = 0;
		INFO	m_tInfo{};

		while (true)
		{
			ReadFile(hFile, &m_tInfo, sizeof(m_tInfo), &dwByte, nullptr);

			if (0 == dwByte)
				break;

			CObjMgr::Get_Instance()->AddObject(OBJ_THORN, CAbstractFactory<CThorn>::Create(m_tInfo));
		}



		CloseHandle(hFile);



	}

	//else if (OBJ_GOAL== eID)
	//{
	//	HANDLE	hFile = CreateFile(L"../Stage/Stage1/Goal1.dat",
	//		GENERIC_READ,
	//		NULL,
	//		NULL,
	//		OPEN_EXISTING,
	//		FILE_ATTRIBUTE_NORMAL,
	//		NULL);

	//	if (INVALID_HANDLE_VALUE == hFile)
	//	{
	//		//MessageBox(g_hWnd, _T("Save File"), _T("Fail"), MB_OK);
	//		return;
	//	}


	//	DWORD dwByte = 0;
	//	INFO	m_tInfo{};

	//	while (true)
	//	{
	//		ReadFile(hFile, &m_tInfo, sizeof(m_tInfo), &dwByte, nullptr);

	//		if (0 == dwByte)
	//			break;

	//		CObjMgr::Get_Instance()->AddObject(OBJ_GOAL, CAbstractFactory<CGoal>::Create(m_tInfo));
	//	}



	//	CloseHandle(hFile);


	//	//MessageBox(g_hWnd, _T("Load 己傍"), _T("己傍"), MB_OK);
	//}


}

void CObjMgr::Load_Data3(OBJID eID)
{
	if (OBJ_WALL == eID)
	{
		HANDLE	hFile = CreateFile(L"../Stage/Stage3/Obstacle3.dat",
			GENERIC_READ,
			NULL,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		if (INVALID_HANDLE_VALUE == hFile)
		{
			MessageBox(g_hWnd, _T("Save File"), _T("Fail"), MB_OK);
			return;
		}

		DWORD		dwByte = 0;


		INFO	m_tInfo{};
		while (true)
		{
			ReadFile(hFile, &m_tInfo, sizeof(m_tInfo), &dwByte, nullptr);

			if (0 == dwByte)
				break;

			CObjMgr::Get_Instance()->AddObject(OBJ_WALL, CAbstractFactory<CWall>::Create(m_tInfo));
		}

		CloseHandle(hFile);
		//MessageBox(g_hWnd, _T("Load 己傍"), _T("己傍"), MB_OK);
	}
	else if (OBJ_THORN == eID)
	{
		HANDLE	hFile = CreateFile(L"../Stage/Stage3/Thorn3.dat",
			GENERIC_READ,
			NULL,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		if (INVALID_HANDLE_VALUE == hFile)
		{
			MessageBox(g_hWnd, _T("Save File"), _T("Fail"), MB_OK);
			return;
		}


		DWORD dwByte = 0;
		INFO	m_tInfo{};

		while (true)
		{
			ReadFile(hFile, &m_tInfo, sizeof(m_tInfo), &dwByte, nullptr);

			if (0 == dwByte)
				break;

			CObjMgr::Get_Instance()->AddObject(OBJ_THORN, CAbstractFactory<CThorn>::Create(m_tInfo));
		}



		CloseHandle(hFile);



	}

	//else if (OBJ_GOAL== eID)
	//{
	//	HANDLE	hFile = CreateFile(L"../Stage/Stage1/Goal1.dat",
	//		GENERIC_READ,
	//		NULL,
	//		NULL,
	//		OPEN_EXISTING,
	//		FILE_ATTRIBUTE_NORMAL,
	//		NULL);

	//	if (INVALID_HANDLE_VALUE == hFile)
	//	{
	//		//MessageBox(g_hWnd, _T("Save File"), _T("Fail"), MB_OK);
	//		return;
	//	}


	//	DWORD dwByte = 0;
	//	INFO	m_tInfo{};

	//	while (true)
	//	{
	//		ReadFile(hFile, &m_tInfo, sizeof(m_tInfo), &dwByte, nullptr);

	//		if (0 == dwByte)
	//			break;

	//		CObjMgr::Get_Instance()->AddObject(OBJ_GOAL, CAbstractFactory<CGoal>::Create(m_tInfo));
	//	}



	//	CloseHandle(hFile);


	//	//MessageBox(g_hWnd, _T("Load 己傍"), _T("己傍"), MB_OK);
	//}


}

void CObjMgr::Load_Data4(OBJID eID)
{
	if (OBJ_WALL == eID)
	{
		HANDLE	hFile = CreateFile(L"../Stage/Stage4/Obstacle4.dat",
			GENERIC_READ,
			NULL,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		if (INVALID_HANDLE_VALUE == hFile)
		{
			MessageBox(g_hWnd, _T("Save File"), _T("Fail"), MB_OK);
			return;
		}

		DWORD		dwByte = 0;


		INFO	m_tInfo{};
		while (true)
		{
			ReadFile(hFile, &m_tInfo, sizeof(m_tInfo), &dwByte, nullptr);

			if (0 == dwByte)
				break;

			CObjMgr::Get_Instance()->AddObject(OBJ_WALL, CAbstractFactory<CWall>::Create(m_tInfo));
		}

		CloseHandle(hFile);
		//MessageBox(g_hWnd, _T("Load 己傍"), _T("己傍"), MB_OK);
	}


}



void CObjMgr::Release()
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		auto& iter = m_ObjList[i].begin();
		for (; iter != m_ObjList[i].end();)
		{
			if (*iter)
			{
				SAFE_DELETE(*iter);
				iter = m_ObjList[i].erase(iter);
			}
		}
	}
}
