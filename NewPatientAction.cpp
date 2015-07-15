#include "NewPatientAction.h"
#include "MainWindow.h"
#include <qdebug.h>

NewPatientAction::NewPatientAction( Message msg ):
	message(msg)
{
}

NewPatientAction::~NewPatientAction()
{
	
}

void NewPatientAction::execute(MainWindow* mainWindow)
{
	if (!mainWindow->isNameAvailable( MainWindow::PATIENT_MODEL , message["name"] ) )
	{
		DialogHelper::popDialog("Error: This name is not available.");
		return;
	}

	if (!FileHelper::createDirectory(message["location"] + "/" + message["name"]))
	{
		DialogHelper::popDialog("Error: Cannot create this directory.");
		return;
	}

	Patient* patient = new Patient( message["name"], atoi(message["sex"].c_str()), message["location"] + "/" + message["name"] );
	FileHelper::writeXML(patient);
	mainWindow->addPatient(patient);

}
