#include "FatData.h"

FatData::FatData( cv::Mat& mat_ori ):
	Data(mat_ori)
{

}

FatData::~FatData()
{

}

Message FatData::getMessage()
{
	Message message;
	message["bgPix"] = std::to_string(px_bg);
	message["tissuePix"] = std::to_string(px_tissue);
	message["nonFatPix"] = std::to_string(px_nonFat);
	message["fatPix"] = std::to_string(px_fat);
	message["percentage"] = std::to_string(percentage);

	return message;
}
