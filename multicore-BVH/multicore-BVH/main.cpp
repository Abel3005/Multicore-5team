#include <iostream>
#include <opencv2/opencv.hpp>
#include "Object.h"
#include "defaultParameter.h"

int main()
{
	Object objectList[100];
	for (int i = 0; i < 100; i++)
	{
		objectList[i].calMidPoint();
		std::cout << "[row" << i << "]: " << objectList[i].middlePoint.x<<" ";
		std::cout << "[col" << i << "]: " << objectList[i].middlePoint.y << std::endl;
	}
	return 0;
}