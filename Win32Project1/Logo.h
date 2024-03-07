#pragma once
#include "Scene.h"
class CLogo :
	public CScene
{
public:
	CLogo();
	~CLogo();

public:
	virtual void Initialize();
	virtual void Update();
	virtual void Late_Update();
	virtual void Render(HDC hdc);
	virtual void Release(void);

private:
	INFO	m_tMouse;
	RECT	m_tMouseRect;
};

