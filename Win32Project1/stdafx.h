// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
#include<list>
#include<vector>
#include<map>
#include<string>
#include<ctime>
#include<time.h>
#include<algorithm>


#include <Vfw.h>
#pragma comment(lib, "vfw32.lib")

#include <io.h>

#include "fmod.h"
#include "fmod.hpp"
#pragma comment(lib, "fmodex_vc.lib")



#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#include<stdlib.h>
#include<crtdbg.h>//�����Ҵ�� �޸� ������ �߻��ϴ��� �˷��ִ� �Լ� ���� ���

#endif _DEBUG

#ifndef DBG_NEW

#define	DBG_NEW new (_NORMAL_BLOCK, __FILE__ , __LINE__)
#define new DBG_NEW

#endif DBG_NEW
using namespace std;