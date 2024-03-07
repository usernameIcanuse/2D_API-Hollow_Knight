#pragma once
#include "Scene.h"
#include "Obj.h"
class CStage2 :
	public CScene
{
public:
	CStage2();
	virtual ~CStage2();

public:
	virtual void Initialize();
	virtual void Update();
	virtual void Late_Update();
	virtual void Render(HDC hdc);
	virtual void Release(void);

private:
	list<CObj*>		m_pMonster;

	bool	m_bFirst;
};

