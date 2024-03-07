#pragma once
#include "Include.h"
#include "Logo.h"
#include "Stage1.h"
#include "Stage2.h"
#include "Stage3.h"
#include "Stage4.h"


class CSceneMgr
{
private:
	CSceneMgr();
	~CSceneMgr();

public:
	static CSceneMgr*		Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CSceneMgr;
		}

		return m_pInstance;
	}

	static void	Destroy_Instance(void)
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

public:
	void	Scene_Change(SCENEID eID);
	void	Initialize();
	void	Update(void);
	void	Late_Update(void);
	void	Render(HDC hdc);
	void	Release(void);

	const SCENEID& Get_Scene() const { return m_eCurScene; }

private:
	static	CSceneMgr*		m_pInstance;
	CScene*					m_pScene;

	CScene*					m_pScene_Array[5];
	
	SCENEID					m_eCurScene = SC_LOGO;
	SCENEID					m_ePreScene = SC_END;

};

