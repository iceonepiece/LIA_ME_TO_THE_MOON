#include "Patient.h"

Patient::Patient()
{

}

Patient::Patient(std::string n, int s, std::string l)
{
	name = n;
	sex = s;
	location = l;
}

Patient::~Patient()
{
	for (Model* folder : list_folder)
	{
		delete folder;
	}
	list_folder.resize(0);
}

