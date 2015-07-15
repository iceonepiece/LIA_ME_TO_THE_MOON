#ifndef FILEHELPER_H
#define FILEHELPER_H

#include <string>
#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include "Patient.h"
#include "Message.h"

class FileHelper
{
public:
	FileHelper();
	~FileHelper();

	static bool createDirectory(std::string path);
	static bool copyFile(std::string filePath, std::string desPath);
	static bool deleteFile(std::string path);
	static bool exists(std::string path);

	static void writeXML(Patient* patient);
	static void writeXML(Folder* folder);
	static void writeXML(DataImage* image);

	static Message readXML(std::string path);
	static Message readFolderXML(std::string path);
	static Message readImageXML(std::string path);
	
};

#endif // FILEHELPER_H
