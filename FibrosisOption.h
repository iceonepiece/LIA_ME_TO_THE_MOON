#ifndef FIBROSISOPTION_H
#define FIBROSISOPTION_H

#include "DataOption.h"

class FibrosisOption : public DataOption
{
public:
	FibrosisOption();
	~FibrosisOption();

	Message getMessage();

	int meanFib;
	int meanTis;
};

#endif // FIBROSISOPTION_H
