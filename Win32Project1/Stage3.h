#pragma once
#include "Scene.h"
class CStage3 :
	public CScene
{
public:
	CStage3();
	virtual ~CStage3();

public:
	virtual void Initialize();
	virtual void Update();
	virtual void Late_Update();
	virtual void Render(HDC hdc);
	virtual void Release(void);
};
