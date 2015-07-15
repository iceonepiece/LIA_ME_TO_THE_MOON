#include "UploadImageAction.h"
#include "MainWindow.h"

UploadImageAction::UploadImageAction( std::string p ):
	path(p)
{

}

UploadImageAction::~UploadImageAction()
{

}

void UploadImageAction::execute( MainWindow* mainWindow )
{
	QFileInfo fileInfo(path.c_str());
	std::string filename = fileInfo.fileName().toStdString();

	if (!mainWindow->isNameAvailable( MainWindow::DATA_IMAGE_MODEL, filename ) )
	{
		DialogHelper::popDialog("Error: This name is not available.");
		return;
	}

	Folder* currentFolder = mainWindow->getCurrentFolder();
	std::string location = currentFolder->location + "/" + filename;
	if (!FileHelper::createDirectory( location ))
	{
		DialogHelper::popDialog("Error: Cannot create this directory.");
		return;
	}

	if (!FileHelper::copyFile(path, location + "/ori_" + filename))
	{
		DialogHelper::popDialog("Error: Cannot copy the image file.");
		return;
	}

	DataImage* image;

	if (currentFolder->type == -2)
	{
		image = new FatImage(filename, currentFolder->type, location, "");
	}
	else if (currentFolder->type == -3)
	{
		image = new FibrosisImage(filename, currentFolder->type, location, "");
	}
	else
	{
		DialogHelper::popDialog("Error: Cannot create an image");
		return;
	}

	mainWindow->executeAction( new ProcessImageAction(image) );
	mainWindow->executeAction( new SaveImageAction(image) );

	mainWindow->addImage(image);
}