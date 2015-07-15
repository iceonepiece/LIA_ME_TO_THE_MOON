#include "FatImage.h"

FatImage::FatImage(std::string name, int type, std::string location, std::string note):
	DataImage(name, type, location, note)
{
	data_processed = new FatData(mat_original);
	data_edited = new FatData(mat_original);
	option = new FatOption();
}

FatImage::~FatImage()
{
}

bool FatImage::load( Message& message )
{
	data_processed->mat_model = cv::imread(location + "/pro_" + name, CV_LOAD_IMAGE_GRAYSCALE);
	data_edited->mat_model = cv::imread(location + "/edit_" + name, CV_LOAD_IMAGE_GRAYSCALE);

	FatOption* fatOption = (FatOption*)option;
	fatOption->min_size = std::atoi( message["minSize"].c_str() );
	fatOption->max_size = std::atoi( message["maxSize"].c_str() );
	fatOption->min_blobSize = std::atoi( message["minBlobSize"].c_str() );
	fatOption->max_blobSize = std::atoi( message["maxBlobSize"].c_str() );
	fatOption->min_circularity = std::atoi( message["minCir"].c_str() );
	fatOption->max_circularity = std::atoi( message["maxCir"].c_str() );

	return true;
}
