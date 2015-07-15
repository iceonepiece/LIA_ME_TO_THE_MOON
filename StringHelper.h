#ifndef STRINGHELPER_H
#define STRINGHELPER_H

#include <string>
#include <iomanip> 
#include <sstream>
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>

class StringHelper
{
public:
	StringHelper();
	~StringHelper();

	static bool matchRegex(std::string str, std::string regex);
	static std::string trim(std::string str);
	static std::string toLower(std::string str);
	static std::string getPrecisionString(double value, int n);
	
};

#endif // STRINGHELPER_H
