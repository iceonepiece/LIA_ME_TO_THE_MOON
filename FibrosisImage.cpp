#include "FibrosisImage.h"
#include "qdebug.h"

FibrosisImage::FibrosisImage(std::string name, int type, std::string location, std::string note):
	DataImage(name,type,location,note)
{
	data_processed = new FibrosisData(mat_original);
	data_edited = new FibrosisData(mat_original);
	option = new FibrosisOption();
}

FibrosisImage::~FibrosisImage()
{

}

bool FibrosisImage::load(Message& message)
{

	data_processed->mat_model = cv::imread(location + "/pro_" + name, CV_LOAD_IMAGE_GRAYSCALE);
	data_edited->mat_model = cv::imread(location + "/edit_" + name, CV_LOAD_IMAGE_GRAYSCALE);

	FibrosisOption* fibOption = (FibrosisOption*)option;
	fibOption->meanFib = std::atoi(message["meanFib"].c_str());
	fibOption->meanTis = std::atoi(message["meanTis"].c_str());

	qDebug() << "Fibrosis Load:" << fibOption->meanFib << ":" << fibOption->meanTis;

	return true;
}