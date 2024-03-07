#include "stdafx.h"
#include "LineMgr.h"
#include "ObjMgr.h"
#include "KeyMgr.h"


CLineMgr*		CLineMgr::m_pInstance = nullptr;



CLineMgr::CLineMgr()
{
}

CLineMgr::~CLineMgr()
{
	Release();
}

void CLineMgr::Initialize(void)
{


}

void CLineMgr::Render(HDC hdc)
{
	for (auto& iter : m_LineList)
		iter->Render(hdc);
}

void CLineMgr::Update()
{
	Key_Input();

	for (auto& iter : m_LineList)
		iter->Update();
}

void CLineMgr::Key_Input()
{
	
	if (CKeyMgr::Get_Instance()->Key_Down(VK_F8))
	{
		//Load_Data2();
		Load_Data1();
	}
}



void	CLineMgr::Load_Data1()
{
	HANDLE	hFile = CreateFile(L"../Stage/Stage1/MyMap1.dat",
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
	LINEINFO	tInfo{};

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(LINEINFO), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		m_LineList.push_back(new CLine(tInfo));
	}


	CloseHandle(hFile);

	//MessageBox(g_hWnd, _T("Load 성공"), _T("성공"), MB_OK);

}


void	CLineMgr::Load_Data2()
{
	HANDLE	hFile = CreateFile(L"../Stage/Stage2/MyMap2.dat",
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

	DWORD		dwByte = 0;
	LINEINFO	tInfo{};

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(LINEINFO), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		m_LineList.push_back(new CLine(tInfo));
	}


	CloseHandle(hFile);

	//MessageBox(g_hWnd, _T("Load 성공"), _T("성공"), MB_OK);

}

void	CLineMgr::Load_Data3()
{
	HANDLE	hFile = CreateFile(L"../Stage/Stage3/MyMap3.dat",
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

	DWORD		dwByte = 0;
	LINEINFO	tInfo{};

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(LINEINFO), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		m_LineList.push_back(new CLine(tInfo));
	}


	CloseHandle(hFile);

	//MessageBox(g_hWnd, _T("Load 성공"), _T("성공"), MB_OK);

}

void	CLineMgr::Load_Data4()
{
	HANDLE	hFile = CreateFile(L"../Stage/Stage4/MyMap4.dat",
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

	DWORD		dwByte = 0;
	LINEINFO	tInfo{};

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(LINEINFO), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		m_LineList.push_back(new CLine(tInfo));
	}


	CloseHandle(hFile);

	//MessageBox(g_hWnd, _T("Load 성공"), _T("성공"), MB_OK);

}



void CLineMgr::Release(void)
{
	for_each(m_LineList.begin(), m_LineList.end(), SAFE_DELETE<CLine>);
	m_LineList.clear();
}

/*
	속력 10으로 이동하는 물체 경사로 오를 때도 10씩 증가하게 하려면
	(10cos(x), 10sin(x))로 각각 이동
*/

bool CLineMgr::Collision_Line(float & fX, float * pY)
{
	if (m_LineList.empty())
		return false;

	CLine* pTargetLine = nullptr;

	for (auto& iter : m_LineList)
	{
		if (fX >= iter->Get_Info().tLeftPoint.fX &&
			fX <= iter->Get_Info().tRightPoint.fX)
		{
			pTargetLine = iter;
		}
	}

	if (!pTargetLine)
		return false;

	float fX1 = pTargetLine->Get_Info().tLeftPoint.fX;
	float fX2 = pTargetLine->Get_Info().tRightPoint.fX;
	float fY1 = pTargetLine->Get_Info().tLeftPoint.fY;
	float fY2 = pTargetLine->Get_Info().tRightPoint.fY;

	*pY = ((fY2 - fY1) / (fX2 - fX1))*(fX - fX1) + fY1;

	return true;
}


bool CLineMgr::Collision_Line(float & fX, float * pY, float& fY)
{
	if(m_LineList.empty())
		return false;

	CLine* pTargetLine = nullptr;
	float fY_temp;
	float fY_Distance = 999999.f;

	float fX1;
	float fX2;
	float fY1;
	float fY2;

	for (auto& iter : m_LineList)
	{
		if (fX >= iter->Get_Info().tLeftPoint.fX &&
			fX <= iter->Get_Info().tRightPoint.fX)
		{
			fX1= iter->Get_Info().tLeftPoint.fX;
			fX2= iter->Get_Info().tRightPoint.fX;
			fY1= iter->Get_Info().tLeftPoint.fY;
			fY2= iter->Get_Info().tRightPoint.fY;
		
			*pY = ((fY2 - fY1) / (fX2 - fX1))*(fX - fX1) + fY1;

			if (*pY > fY)
			{
				if (fY_Distance > *pY - fY)
				{
					fY_temp = *pY;
					pTargetLine = iter;
				}
				
			}
		}
	}

	if (!pTargetLine)
	{
		*pY = 0.f;
		return false;
	}


	*pY = fY_temp;

	return true;
}
