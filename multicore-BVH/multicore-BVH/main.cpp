#include <iostream>
#include <opencv2/opencv.hpp>
#include "Object.h"
#include "defaultParameter.h"
#include "ObjectReader.h"
#include "Box.h"
#include "DS_timer.h"
#include "DS_definitions.h"
#include "Tree.h"
#include <omp.h>

using namespace std;
using namespace cv;
TreeNode* serial_execute(Object* List, int objectNum, int depth, InputOutputArray img);
TreeNode* version1_execute(Object* List, int objectNum, int depth, InputOutputArray img);
TreeNode* version2_execute(Object* List, int objectNum, int depth, cv::InputOutputArray img);
int main()
{
	/*ObjectReader objectReader;
	objectReader.readTxt("input.txt");

	Object* objectList = objectReader.objectList;
	*/int num = ObjectNums;
	Object objectList[100];
	DS_timer timer(3);
	timer.setTimerName(0, (char*)"Serial");
	timer.setTimerName(1, (char*)"Version1");
	timer.setTimerName(2, (char*)"Version2");
	cv::Mat bgImage = cv::Mat::zeros(Maxlength, MaxHeight,CV_8UC1);
	Mat serial_img(Maxlength, MaxHeight, CV_8UC3);
	Mat version1_img(Maxlength, MaxHeight, CV_8UC3);
	Mat version2_img(Maxlength, MaxHeight, CV_8UC3);
	serial_img.setTo(0);
	version1_img.setTo(0);
	version2_img.setTo(0);
	int npts = 3;

	for (int i = 0; i < ObjectNums; i++) {
		objectList[i].drawObject(serial_img);
		objectList[i].drawObject(version1_img);
		objectList[i].drawObject(version2_img);
	}
	timer.onTimer(0);
	Tree tree(serial_execute(objectList, ObjectNums, 32, serial_img));
	timer.offTimer(0);
	timer.onTimer(1);
	Tree tree1(version1_execute(objectList, ObjectNums, 32, version1_img));
	timer.offTimer(1);
	omp_set_nested(1);
	timer.onTimer(2);
	Tree tree2(version2_execute(objectList, ObjectNums, 32, version2_img));
	timer.offTimer(2);
	imshow("result", serial_img);
	imshow("result1",version1_img);
	imshow("result2", version2_img);

	/*Box box(objectList, num);
	box.serial_calBox();
	box.drawBox(img);*/

	
	timer.printTimer();
	waitKey();
	return 0;
}
TreeNode* serial_execute(Object* List, int objectNum, int depth, cv::InputOutputArray img)
{
	if (depth == 0 || objectNum <= 1)
	{
		return nullptr;
	}
	Box box(List, objectNum);
	box.serial_calBox();
	box.drawBox(img);
	TreeNode* node = new TreeNode(box);
	Object* lList = new Object[objectNum];
	Object* RList = new Object[objectNum];
	int lnums = 0;
	int rnums = 0;
	/************************************************************************/
/* your cord here                                                */
/************************************************************************/

	if (depth % 2 == 1)
	{
		for (int i = 0; i < objectNum; i++)
		{
			if (box.middlePoint.x < List[i].middlePoint.x)
			{
				RList[rnums] = List[i];
				rnums++;
			}
			else
			{
				lList[lnums] = List[i];
				lnums++;
			}
		}
	}
	else {
		for (int i = 0; i < objectNum; i++)
		{
			if (box.middlePoint.y < List[i].middlePoint.y)
			{
				RList[rnums] = List[i];
				rnums++;
			}
			else
			{
				lList[lnums] = List[i];
				lnums++;
			}
		}
	}
	
	node->left = serial_execute(lList, lnums, depth - 1, img);
	node->right = serial_execute(RList, rnums, depth - 1, img);
	return node;

}
TreeNode* version1_execute(Object* List, int objectNum, int depth, cv::InputOutputArray img)
{
	if (depth == 0 || objectNum <= 1)
	{
		return nullptr;
	}
	Box box(List, objectNum);
	box.version1_calBox();
	box.drawBox(img);
	TreeNode* node = new TreeNode(box);
	Object* lList = new Object[objectNum];
	Object* RList = new Object[objectNum];
	int lnums = 0;
	int rnums = 0;
	if (depth % 2 == 1)
	{
		for (int i = 0; i < objectNum; i++)
		{
			if (box.middlePoint.x < List[i].middlePoint.x)
			{
				RList[rnums] = List[i];
				rnums++;
			}
			else
			{
				lList[lnums] = List[i];
				lnums++;
			}
		}
	}
	else {
		for (int i = 0; i < objectNum; i++)
		{
			if (box.middlePoint.y < List[i].middlePoint.y)
			{
				RList[rnums] = List[i];
				rnums++;
			}
			else
			{
				lList[lnums] = List[i];
				lnums++;
			}
		}
	}

	node->left = serial_execute(lList, lnums, depth - 1, img);
	node->right = serial_execute(RList, rnums, depth - 1, img);
	return node;

}
TreeNode* version2_execute(Object* List, int objectNum, int depth, cv::InputOutputArray img)
{
	static int call = 0;
	if (depth == 0 || objectNum <= 1)
	{
		return nullptr;
	}
	Box box(List, objectNum);
	box.serial_calBox();
	box.drawBox(img);
	TreeNode* node = new TreeNode(box);
	Object* lList = new Object[objectNum];
	Object* RList = new Object[objectNum];
	int lnums = 0;
	int rnums = 0;
	if (depth % 2 == 1)
	{
		for (int i = 0; i < objectNum; i++)
		{
			if (box.middlePoint.x < List[i].middlePoint.x)
			{
				RList[rnums] = List[i];
				rnums++;
			}
			else
			{
				lList[lnums] = List[i];
				lnums++;
			}
		}
	}
	else {
		for (int i = 0; i < objectNum; i++)
		{
			if (box.middlePoint.y < List[i].middlePoint.y)
			{
				RList[rnums] = List[i];
				rnums++;
			}
			else
			{
				lList[lnums] = List[i];
				lnums++;
			}
		}
	}
	if (call < log(num_thread)) {
#pragma omp parallel sections num_threads(2)
		{
#pragma omp section
			{
				node->left = serial_execute(lList, lnums, depth - 1, img);
			}
#pragma omp section
			{
				node->right = serial_execute(RList, rnums, depth - 1, img);
			}
		}
	}
	else {
		node->left = serial_execute(lList, lnums, depth - 1, img);
		node->right = serial_execute(RList, rnums, depth - 1, img);
	}

	return node;

}