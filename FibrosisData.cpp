#include "FibrosisData.h"

FibrosisData::FibrosisData(cv::Mat& mat_ori) :
	Data(mat_ori)
{

}

FibrosisData::~FibrosisData()
{

}

Message FibrosisData::getMessage()
{
	Message message;
	message["bgPix"] = std::to_string(px_bg);
	message["tissuePix"] = std::to_string(px_tissue);
	message["nonFibPix"] = std::to_string(px_nonFib);
	message["fibPix"] = std::to_string(px_fib);
	message["percentage"] = std::to_string(percentage);

	return message;
}
