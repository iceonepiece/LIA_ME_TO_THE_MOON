#include "OpenFolderAction.h"
#include "MainWindow.h"
#include "qdebug.h"

OpenFolderAction::OpenFolderAction( Patient* pt, std::string p ):
	patient(pt), path(p)
{

}

OpenFolderAction::~OpenFolderAction()
{

}

void OpenFolderAction::execute(MainWindow* window)
{
	if (!FileHelper::exists( path + "/folder.lia" ))
	{
		DialogHelper::popDialog("This is not the folder of LIA");
		return;
	}

	Message in;
	try
	{
		in = FileHelper::readFolderXML(path);
	}
	catch (std::exception e)
	{
		DialogHelper::popDialog( e.what() );
		return;
	}

	if (!window->isNameAvailable( patient->list_folder, in["name"]))
	{
		DialogHelper::popDialog("This folder's name has already been in the patient.");
		return;
	}

	Folder* folder = new Folder(in["name"], std::atoi(in["type"].c_str()), in["location"]);

	int num = in.size() - 3;

	for (int i = 1; i <= num; i++)
	{
		std::string path = in["location"] + "/" + in["image" + std::to_string(i)];
		qDebug() << "image path: " << path.c_str();
		window->executeAction( new OpenImageAction(folder, path) );
	}

	patient->list_folder.push_back(folder);

}
