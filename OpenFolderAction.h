#ifndef OPENFOLDERACTION_H
#define OPENFOLDERACTION_H

#include "Action.h"
#include "Patient.h"
#include "FileHelper.h"
#include "DialogHelper.h"
#include "OpenImageAction.h"

class OpenFolderAction : public Action
{
public:
	OpenFolderAction( Patient* patient, std::string path );
	~OpenFolderAction();

	void execute(MainWindow* window);

private:
	Patient* patient;
	std::string path;
	
};

#endif // OPENFOLDERACTION_H
