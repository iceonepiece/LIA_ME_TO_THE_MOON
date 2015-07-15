#include "Folder.h"

Folder::Folder()
{

}

Folder::Folder(std::string n, int t, std::string l)
{
	name = n;
	type = t;
	location = l;

	if (type == -2)
		typeStr = "Fat";
	else if (type == -3)
		typeStr = "Fibrosis";
	else
		typeStr = "None";

}

Folder::~Folder()
{
	for (Model* image : list_dataImage)
	{
		delete image;
	}
	list_dataImage.resize(0);
}
