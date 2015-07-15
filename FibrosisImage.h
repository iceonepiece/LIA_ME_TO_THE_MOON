#ifndef FIBROSISIMAGE_H
#define FIBROSISIMAGE_H

#include "DataImage.h"

class FibrosisImage : public DataImage
{
public:
	FibrosisImage(std::string name, int type, std::string location, std::string note);
	~FibrosisImage();

	bool load(Message& message);

private:
	
};

#endif // FIBROSISIMAGE_H
