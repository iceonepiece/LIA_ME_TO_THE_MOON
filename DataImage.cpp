#include "DataImage.h"

DataImage::DataImage(std::string n, int t, std::string l, std::string nt)
{
	name = n;
	type = t;
	location = l;
	note = nt;
	zoom = 4;
	hasProcessed = false;
	mat_original = cv::imread( location + "/ori_" + name, CV_LOAD_IMAGE_COLOR );
	data_processed = nullptr;
	data_edited = nullptr;
	option = nullptr;

	if (type == -2)
		typeStr = "Fat";
	else if (type == -3)
		typeStr = "Fibrosis";
	else
		typeStr = "None";

}


DataImage::DataImage()
{

}

DataImage::~DataImage()
{
	if (data_processed != nullptr)
		delete data_processed;

	if (data_edited != nullptr)
		delete data_edited;

	if (option != nullptr)
		delete option;
}
