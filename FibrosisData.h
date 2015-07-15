#ifndef FIBROSISDATA_H
#define FIBROSISDATA_H

#include "Data.h"

class FibrosisData : public Data
{
public:
	FibrosisData(cv::Mat& mat_ori);
	~FibrosisData();

	int px_bg;
	int px_tissue;
	int px_fib;
	int px_nonFib;

	Message getMessage();
};

#endif // FIBROSISDATA_H
