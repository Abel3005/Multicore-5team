#pragma once
#include <opencv2/opencv.hpp>
class Object
{
private:
	cv::Point2d points[3];
	
public:

	cv::Point2d middlePoint;

	Object(cv::Point2d a, cv::Point2d b, cv::Point2d c);
	Object();
	~Object();

	void calMidPoint();
};

