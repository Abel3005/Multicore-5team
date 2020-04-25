#pragma once
#include "Object.h"
class ObjectReader
{

public:
	Object* objectList;
	int num;
	ObjectReader();
	~ObjectReader();
	void readTxt(const char* filename);
};

