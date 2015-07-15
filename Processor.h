#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <opencv2/ml/ml.hpp>
#include "Data.h"
#include "ImageHelper.h"
#include "DataOption.h"
#include "DataImage.h"
#include "MathHelper.h"

typedef std::vector<cv::Point> Contour;

class Processor
{
public:

	Processor();
	~Processor();

	
	virtual void process(DataImage* image, bool option = false ) = 0;
	virtual void classify(DataImage* image) = 0;
	virtual void copy(DataImage* image){};
	virtual void setupOption(DataImage* image) = 0;
	virtual void highlight(Data* data) = 0;
	virtual void copy(Data* from, Data* to) = 0;

	virtual void processWithOption(DataImage* image){};
	virtual void process(Data* data, DataOption* option){};

	virtual void computePercentage(Data* data) = 0;

	virtual bool click(Data* data, int x, int y ) = 0;
	virtual void miniComputePercentage(Data* data) = 0;
	virtual void miniHighlight( Data* data, std::vector<cv::Point>& list_point) = 0;

	
};

#endif // PROCESSOR_H
