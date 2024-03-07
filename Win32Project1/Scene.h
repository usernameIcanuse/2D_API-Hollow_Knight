#pragma once
#include "Include.h"
class CScene
{
public:
	CScene();
	virtual ~CScene();

public:
	virtual void Initialize()		PURE;
	virtual void Update()			PURE;
	virtual void Late_Update()		PURE;
	virtual void Render(HDC hdc)	PURE;
	virtual void Release(void)		PURE;
};

