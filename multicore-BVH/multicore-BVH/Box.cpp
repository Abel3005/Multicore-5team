#include "Box.h"
Box::Box(Object* _objectList, int _objNum) {
	objectList = _objectList;
	objNum = _objNum;
}
void Box::calBox() {
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

void Box::drawBox(cv::InputOutputArray img) {
	int npts = 3;
	cv::rectangle(img, boxPoint[0], boxPoint[1], cv::Scalar(0, 55, 255),+1,4);
	
}
