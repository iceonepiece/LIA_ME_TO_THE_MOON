#include "NewFolderAction.h"
#include "MainWindow.h"
#include "qdebug.h"

NewFolderAction::NewFolderAction( Message msg ) :
	message(msg)
{

}

NewFolderAction::~NewFolderAction()
{

}

void NewFolderAction::execute(MainWindow* mainWindow)
{
	if (!mainWindow->isNameAvailable( MainWindow::FOLDER_MODEL, message["name"] ) )
	{
		DialogHelper::popDialog("Error: This name is not available.");
		return;
	}

	std::string location = mainWindow->getCurrentPatient()->location + "/" + message["name"];

	qDebug() << "Patient Location: " << mainWindow->getCurrentPatient()->location.c_str();
	if ( !FileHelper::createDirectory( location ) )
	{
		DialogHelper::popDialog("Error: Cannot create this directory.");
		return;
	}

	Folder* folder = new Folder( message["name"], std::atoi(message["type"].c_str()), location );
	FileHelper::writeXML(folder);
	mainWindow->addFolder(folder);
}