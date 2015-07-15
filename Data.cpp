#include "Data.h"

Data::Data( cv::Mat& mat_ori ):
	mat_original(mat_ori)
{
	mat_display = mat_original.clone();
}

Data::~Data()
{

}

std::string Data::getPercentString()
{
	return StringHelper::getPrecisionString(this->percentage, 2) + "%";
}