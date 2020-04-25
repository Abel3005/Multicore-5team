#pragma once
#include "Object.h"
#include "defaultParameter.h"
class Box
{
private:
	Object* objectList;
	int objNum;
public:
	cv::Point boxPoint[2];
	cv::Point middlePoint;
	Box(Object* _objectList, int _objNum);
	void calBox();
	void drawBox(cv::InputOutputArray img);

};

