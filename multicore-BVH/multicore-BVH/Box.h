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
	Box() {};
	void serial_calBox();
	void version1_calBox();
	
	void drawBox(cv::InputOutputArray img);
	void quick_sort_x(int start, int end);
	void quick_sort_y(int start, int end);

};

