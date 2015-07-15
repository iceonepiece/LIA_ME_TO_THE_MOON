#ifndef FATOPTION_H
#define FATOPTION_H

#include "DataOption.h"

class FatOption : public DataOption
{
public:
	FatOption();
	~FatOption();

	Message getMessage();

	int min_circularity;
	int max_circularity;
	int min_size;
	int max_size;
	int min_blobSize;
	int max_blobSize;
	
};

#endif // FATOPTION_H
