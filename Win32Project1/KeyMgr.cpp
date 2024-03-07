#include "stdafx.h"
#include "KeyMgr.h"

CKeyMgr*	CKeyMgr::m_pInstance = nullptr;

CKeyMgr::CKeyMgr()
{
	ZeroMemory(m_eKeyState, sizeof(m_eKeyState));
}

CKeyMgr::~CKeyMgr()
{
}

bool CKeyMgr::Key_Pressing(int _iKey)
{
	if ((KEY_PRESS == m_eKeyState[_iKey]))
	{
		return true;
	}
	return false;
}

bool CKeyMgr::Key_Down(int _iKey)
{
	if ((KEY_DOWN == m_eKeyState[_iKey]))
	{
		return true;
	}
	return false;
}

bool CKeyMgr::Key_Up(int _iKey)
{
	if ((KEY_UP == m_eKeyState[_iKey]))
	{
		return true;
	}
	return false;
}

bool CKeyMgr::Key_None(int _iKey)
{
	if ((KEY_NONE == m_eKeyState[_iKey]))
	{
		return true;
	}
	return false;
}

void CKeyMgr::Initialize()
{
	for (auto iter : m_eKeyState)
		iter = KEY_NONE;
}

void CKeyMgr::Update()
{
	for (int i = 0; i < VK_MAX; ++i)
	{
		// 이전 x
		if ((KEY_NONE == m_eKeyState[i]) || (KEY_UP == m_eKeyState[i]))
		{
			// 지금 ㅇ
			if (GetAsyncKeyState(i) & 0x8000)
			{
				m_eKeyState[i] = KEY_DOWN;
			}
			// 지금 x
			else
			{
				m_eKeyState[i] = KEY_NONE;
			}
		}
		// 이전 ㅇ
		else
		{
			// 지금 ㅇ
			if (GetAsyncKeyState(i) & 0x8000)
			{
				m_eKeyState[i] = KEY_PRESS;
			}
			// 지금 x
			else
			{
				m_eKeyState[i] = KEY_UP;
			}
		}

	}
}


