#ifndef DATA_H
#define DATA_H

#include <string>
#include <opencv2\imgproc\imgproc.hpp>
#include "StringHelper.h"
#include "Message.h"

class Data
{
public:
	Data( cv::Mat& mat_ori );
	virtual ~Data();

	cv::Mat& mat_original;
	cv::Mat mat_model;
	cv::Mat mat_display;
	double percentage;

	std::string getPercentString();
	virtual Message getMessage() = 0;
	
};

#endif // DATA_H
