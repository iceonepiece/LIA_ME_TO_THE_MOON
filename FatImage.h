#ifndef FATIMAGE_H
#define FATIMAGE_H

#include "DataImage.h"
#include "Blob.h"

class FatImage : public DataImage
{
public:
	FatImage(std::string name, int type, std::string location, std::string note);
	~FatImage();

	bool load( Message& message );

	std::vector<Blob> list_blob;
	cv::Mat mat_blob;

	float minBlobSize;
	float maxBlobSize;
	
};

#endif // FATIMAGE_H
