#pragma once
#include"Include.h"

class CObj;

class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void Initialize();
	void Update();
	void Late_Update();
	void Render();
	void Release();

private:
	HDC		m_DC;
	
	int		m_iTime;

	int	m_iFPS;
	TCHAR  m_szFPS[32];
	DWORD m_dwTime;
};

