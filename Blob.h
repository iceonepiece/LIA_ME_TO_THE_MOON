#ifndef BLOB_H
#define BLOB_H

#include "Processor.h"

class Blob
{
public:

	static const int BACKGROUND = 1;

	Blob();
	~Blob();

	int type;
	int label;

	Contour contour;
	double area;
	double circularity;
	double avgGrayLevel;
	
};

#endif // BLOB_H
