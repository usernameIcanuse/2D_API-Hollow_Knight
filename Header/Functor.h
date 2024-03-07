#pragma once

template<typename T>
void SAFE_DELETE(T* p)
{
	delete p;
	p = nullptr;
}

class CTagFinder
{
private:
	const TCHAR*		m_pStrKey;

public:
	CTagFinder(const TCHAR* pStrKey)
		:m_pStrKey(pStrKey) {}

public:
	template<typename T>
	bool		operator()(T& Pair)
	{
		return !lstrcmp(m_pStrKey, Pair.first);
	}
};

class CDeleteMap
{
public:
	template<typename T>
	void operator()(T& Pair)
	{
		if (Pair.second)
		{
			delete Pair.second;
			Pair.second = nullptr;
		}
	}
};