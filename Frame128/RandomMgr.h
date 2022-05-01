#pragma once
#include "SingletonBase.h"
class CRandomMgr : public CSingletonBase<CRandomMgr>
{
	friend CSingletonBase;
private:
	CRandomMgr()
	{
		srand(GetTickCount());
	}
	~CRandomMgr();
public:
	inline int getInt(int num) { return rand() % num; }
	inline int getFromInto(int fromNum, int toNum)
	{
		return rand() % (toNum - fromNum + 1) + fromNum;
	}

	inline float getFloat(float num) { return ((float)rand() / (float)RAND_MAX) * num; }
	inline float getFromFloatTo(float fromNum, float toNum)
	{
		float rnd = (float)rand() / (float)RAND_MAX;
		return (rnd * (toNum - fromNum) + fromNum);
	}
};

