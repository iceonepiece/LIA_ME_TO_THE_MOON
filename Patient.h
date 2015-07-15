#ifndef PATIENT_H
#define PATIENT_H

#include <string>
#include <vector>
#include "Model.h"
#include "Folder.h"

class Patient : public Model
{
public:
	Patient(std::string n, int s, std::string l);
	Patient();
	~Patient();

	int sex;
	std::vector<Model*> list_folder;

};

#endif // PATIENT_H
