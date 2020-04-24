#pragma once
#include <opencv2/opencv.hpp>
class Object
{
private:
	
	
public:
	cv::Point points[3];
	cv::Point middlePoint;

	Object(cv::Point a, cv::Point b, cv::Point c);
	Object();
	~Object();

	void calMidPoint();
};

