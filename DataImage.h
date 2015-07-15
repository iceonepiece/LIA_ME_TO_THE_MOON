#ifndef DATAIMAGE_H
#define DATAIMAGE_H


#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "Model.h"
#include "Data.h"
#include "FatData.h"
#include "FibrosisData.h"
#include "DataOption.h"
#include "FatOption.h"
#include "FibrosisOption.h"
#include "Message.h"

class DataImage : public Model
{
public:
	DataImage(std::string name, int type, std::string location, std::string note);
	DataImage();
	virtual ~DataImage();

	virtual bool load(Message& message) = 0;

	int type;
	std::string typeStr;
	std::string note;

	cv::Mat mat_original;

	Data* data_processed;
	Data* data_edited;

	DataOption* option;

	int zoom;
	bool hasProcessed;
};

#endif // DATAIMAGE_H
