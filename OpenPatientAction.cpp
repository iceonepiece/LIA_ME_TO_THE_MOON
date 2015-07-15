#include "OpenPatientAction.h"
#include "MainWindow.h"
#include "qdebug.h"

OpenPatientAction::OpenPatientAction( Message msg ):
	message(msg)
{

}

OpenPatientAction::~OpenPatientAction()
{

}

void OpenPatientAction::execute(MainWindow* window)
{
	if (!FileHelper::exists(message["location"] + "/patient.lia"))
	{
		DialogHelper::popDialog("This is not the folder of LIA patient");
		return;
	}

	Message in;
	try
	{
		in = FileHelper::readXML(message["location"]);
	}
	catch ( std::exception e )
	{
		DialogHelper::popDialog(e.what());
		return;
	}

	if (!window->isNameAvailable( MainWindow::PATIENT_MODEL, in["name"] ) )
	{
		DialogHelper::popDialog("This patient's name has already been in the program.");
		return;
	}

	Patient* patient = new Patient(in["name"], atoi(in["sex"].c_str()), in["location"] );

	int num = in.size() - 3;

	for (int i = 1; i <= num; i++)
	{
		std::string path = in["location"] + "/" + in["folder" + std::to_string(i)];
		qDebug() << path.c_str();
		window->executeAction( new OpenFolderAction( patient,  path ) );
	}

	window->addPatient(patient);
}