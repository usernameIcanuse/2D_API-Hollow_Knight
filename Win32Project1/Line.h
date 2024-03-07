#pragma once
#include"Include.h"
class CLine
{
public:
	CLine();
	CLine(LINEINFO tInfo);
	CLine(POINTPOS& tLeft, POINTPOS& tRight);
	~CLine();

public:
	const LINEINFO& Get_Info(void)const { return m_tInfo; }
	bool	Get_RightCliff() { return b_RightCliff; }
	bool	Get_LeftCliff() { return b_LeftCliff; }

public:
	void Render(HDC hdc);
	void Update();
	
private:
	LINEINFO	m_tInfo;

	bool	b_LeftCliff;
	bool	b_RightCliff;
};

