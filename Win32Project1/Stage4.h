#pragma once
#include "Scene.h"
class CStage4 :
	public CScene
{
public:
	CStage4();
	virtual ~CStage4();

public:
	virtual void Initialize();
	virtual void Update();
	virtual void Late_Update();
	virtual void Render(HDC hdc);
	virtual void Release(void);
};
