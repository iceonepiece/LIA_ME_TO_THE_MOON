#include "FibrosisOption.h"

FibrosisOption::FibrosisOption()
{

}

FibrosisOption::~FibrosisOption()
{

}

Message FibrosisOption::getMessage()
{
	Message message;
	message["meanFib"] = std::to_string(this->meanFib);
	message["meanTis"] = std::to_string(this->meanTis);

	return message;
}