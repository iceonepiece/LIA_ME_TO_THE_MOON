#include "FatOption.h"

FatOption::FatOption()
{

}

FatOption::~FatOption()
{

}

Message FatOption::getMessage()
{
	Message message;
	message["minSize"] = std::to_string( this->min_size );
	message["maxSize"] = std::to_string(this->max_size);
	message["minCir"] = std::to_string(this->min_circularity);
	message["maxCir"] = std::to_string(this->max_circularity);
	message["minBlobSize"] = std::to_string(this->min_blobSize);
	message["maxBlobSize"] = std::to_string(this->max_blobSize);

	return message;
}