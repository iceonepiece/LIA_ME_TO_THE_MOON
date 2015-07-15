#include "StringHelper.h"

StringHelper::StringHelper()
{

}

StringHelper::~StringHelper()
{

}

bool StringHelper::matchRegex(std::string str, std::string reg )
{
	boost::regex e(reg);
	return boost::regex_match(str, e);
}

std::string StringHelper::trim(std::string str)
{
	boost::trim(str);
	return str;
}

std::string StringHelper::toLower(std::string str)
{
	for (int i = 0; str[i]; i++)
		str[i] = std::tolower(str[i]);

	return str;
}

std::string StringHelper::getPrecisionString(double value, int n)
{
	std::stringstream ss;
	ss << std::fixed << std::setprecision(n) << value;
	return ss.str();
}