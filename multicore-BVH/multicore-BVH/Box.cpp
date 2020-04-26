#include "Box.h"
#include "defaultParameter.h"
#include <omp.h>
Box::Box(Object* _objectList, int _objNum) {
	objectList = _objectList;
	objNum = _objNum;
}
void Box::serial_calBox() {
	int minX = Maxlength, minY = MaxHeight, maxX = -1, maxY = -1;
	for (int i = 0; i < objNum; i++)
	{
		objectList[i].calMidPoint();
		for (int j = 0; j < 3; j++)
		{
			if (minX > objectList[i].points[j].x)
			{
				minX = objectList[i].points[j].x;
			}
			if (minY > objectList[i].points[j].y)
			{
				minY = objectList[i].points[j].y;
			}
			if (maxX < objectList[i].points[j].x)
			{
				maxX = objectList[i].points[j].x;
			}
			if (maxY < objectList[i].points[j].y)
			{
				maxY = objectList[i].points[j].y;
			}
		}
		
	}
	boxPoint[0].x = minX;
	boxPoint[0].y = minY;
	boxPoint[1].x = maxX;
	boxPoint[1].y = maxY;
	middlePoint.x = (minX + maxX) / 2;
	middlePoint.y = (minY + maxY) / 2;
}
void Box::version1_calBox() {
	int globalMinMax[4][num_thread];
	int minX = Maxlength, minY = MaxHeight, maxX = -1, maxY = -1;
#pragma omp parallel num_threads(num_thread) 
	{
		int my_num = omp_get_thread_num();
		int minX = Maxlength, minY = MaxHeight, maxX = -1, maxY = -1;
#pragma omp parallel for
		for (int i = 0; i < objNum; i++)
		{
			objectList[i].calMidPoint();
			for (int j = 0; j < 3; j++)
			{
				if (minX > objectList[i].points[j].x)
				{
					minX = objectList[i].points[j].x;
				}
				if (minY > objectList[i].points[j].y)
				{
					minY = objectList[i].points[j].y;
				}
				if (maxX < objectList[i].points[j].x)
				{
					maxX = objectList[i].points[j].x;
				}
				if (maxY < objectList[i].points[j].y)
				{
					maxY = objectList[i].points[j].y;
				}
			}
		}
		globalMinMax[0][my_num] = minX;
		globalMinMax[1][my_num] = maxX;
		globalMinMax[2][my_num] = minY;
		globalMinMax[3][my_num] = maxY;
	}
	for (int i = 0; i < num_thread; i++)
	{
		if (minX > globalMinMax[0][i])
			minX = globalMinMax[0][i];
	}
	for (int i = 0; i < num_thread; i++)
	{
		if (maxX < globalMinMax[1][i])
			maxX = globalMinMax[1][i];
	}
	for (int i = 0; i < num_thread; i++)
	{
		if (minY < globalMinMax[2][i])
			minY = globalMinMax[2][i];
	}
	for (int i = 0; i < num_thread; i++)
	{
		if (maxY < globalMinMax[3][i])
			maxY = globalMinMax[3][i];
	}
	boxPoint[0].x = minX;
	boxPoint[0].y = minY;
	boxPoint[1].x = maxX;
	boxPoint[1].y = maxY;
	middlePoint.x = (minX + maxX) / 2;
	middlePoint.y = (minY + maxY) / 2;
}

void Box::drawBox(cv::InputOutputArray img) {
	int npts = 3;
	cv::rectangle(img, boxPoint[0], boxPoint[1], cv::Scalar(0, 55, 255),+1,4);
	
}
void Box::quick_sort_x(int start , int end) {
	if (start >= end) {
		return;
	}

	int pivot = start;
	int i = pivot + 1;
	int j = end;
	Object temp;

	while (i <= j) {
		while (i <= end && objectList[i].middlePoint.x <= objectList[pivot].middlePoint.x)
		{
			i++;
		}
		while (j > start&& objectList[j].middlePoint.x >= objectList[pivot].middlePoint.x)
		{
			j--;
		}
		if (i > j) {
			temp = objectList[j];
			objectList[i] = objectList[j];
			objectList[j] = temp;
		}
	}

	quick_sort_x(start, j - 1);
	quick_sort_x(j + 1, end);
}
void Box::quick_sort_y(int start, int end) {
	if (start >= end) {
		return;
	}

	int pivot = start;
	int i = pivot + 1;
	int j = end;
	Object temp;

	while (i <= j) {
		while (i <= end && objectList[i].middlePoint.y <= objectList[pivot].middlePoint.y)
		{
			i++;
		}
		while (j > start&& objectList[j].middlePoint.y >= objectList[pivot].middlePoint.y)
		{
			j--;
		}
		if (i > j) {
			temp = objectList[j];
			objectList[i] = objectList[j];
			objectList[j] = temp;
		}
	}

	quick_sort_x(start, j - 1);
	quick_sort_x(j + 1, end);
}
