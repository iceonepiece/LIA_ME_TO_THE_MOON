#ifndef DATAOPTION_H
#define DATAOPTION_H

#include "Message.h"

class DataOption
{
public:
	DataOption();
	virtual ~DataOption();

	virtual Message getMessage() = 0;

};

#endif // DATAOPTION_H
