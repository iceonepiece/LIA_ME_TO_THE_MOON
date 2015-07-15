#ifndef FATDATA_H
#define FATDATA_H

#include "Data.h"

class FatData : public Data
{
public:
	FatData( cv::Mat& mat_ori );
	~FatData();

	int px_bg;
	int px_tissue;
	int px_fat;
	int px_nonFat;

	int minBlobSize;
	int maxBlobSize;

	Message getMessage();
	
};

#endif // FATDATA_H
