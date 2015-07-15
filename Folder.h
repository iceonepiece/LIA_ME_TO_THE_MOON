#ifndef FOLDER_H
#define FOLDER_H

#include <string>
#include <vector>
#include "Model.h"
#include "DataImage.h"

class Folder : public Model
{
public:
	Folder( std::string name, int type, std::string location );
	Folder();
	~Folder();

	int type;
	std::string typeStr;
	std::vector<Model*> list_dataImage;
	
};

#endif // FOLDER_H
