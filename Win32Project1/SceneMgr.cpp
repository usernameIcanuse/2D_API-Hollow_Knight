#include "stdafx.h"
#include "SceneMgr.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"

CSceneMgr* CSceneMgr::m_pInstance = nullptr;

CSceneMgr::CSceneMgr()
	: m_pScene(nullptr)
{
	m_pScene_Array[0] = nullptr;
	m_pScene_Array[1] = nullptr;
	m_pScene_Array[2] = nullptr;
	m_pScene_Array[3] = nullptr;
	m_pScene_Array[4] = nullptr;
}


CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::Scene_Change(SCENEID eID)
{

	m_eCurScene = eID;

	if (m_ePreScene != m_eCurScene)
	{
		/*if (m_pScene)
		{
			SAFE_DELETE(m_pScene);
		}*/

		switch (m_eCurScene)
		{
		case SC_LOGO:
			CSoundMgr::Get_Instance()->PlayBGM(L"Title.wav", 0.4f);
			m_pScene = m_pScene_Array[0];
			break;

		case SC_STAGE1:CSoundMgr::Get_Instance()->StopAll();
			CSoundMgr::Get_Instance()->PlayBGM(L"S23-11 INSIDE LOOP.wav", 0.3f);
			m_pScene = m_pScene_Array[1];
			break;

		case SC_STAGE2:
			m_pScene = m_pScene_Array[2];
			break;

		case SC_STAGE3:
			m_pScene = m_pScene_Array[3];
			break;

		case SC_STAGE4:
			m_pScene = m_pScene_Array[4];
			break;
	
		}
		m_pScene->Initialize();
		
		m_ePreScene = m_eCurScene;
	}

}

void CSceneMgr::Initialize()
{
	
	m_pScene_Array[0] = new CLogo;

	m_pScene_Array[1] = new CStage1;
	//m_pScene_Array[1]->Initialize();

	m_pScene_Array[2] = new CStage2;
	//m_pScene_Array[2]->Initialize();

	m_pScene_Array[3] = new CStage3;
	//m_pScene_Array[3]->Initialize();

	m_pScene_Array[4] = new CStage4;
	//m_pScene_Array[4]->Initialize();

}

void CSceneMgr::Update(void)
{
	if (m_pScene)
		m_pScene->Update();
}

void CSceneMgr::Late_Update(void)
{
	if (m_pScene)
		m_pScene->Late_Update();

}

void CSceneMgr::Render(HDC hdc)
{
	if (m_pScene)
		m_pScene->Render(hdc);
}

void CSceneMgr::Release(void)
{
	//SAFE_DELETE(m_pScene);

	for (int i = 0; i < 5; ++i)
		SAFE_DELETE(m_pScene_Array[i]);

	CObjMgr::Get_Instance()->Destroy_Instance();
	CLineMgr::Get_Instance()->Destroy_Instance();
	CScrollMgr::Get_Instance()->Destroy_Instance();
}

