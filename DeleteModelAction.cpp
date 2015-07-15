#include "DeleteModelAction.h"

DeleteModelAction::DeleteModelAction( Model* m ):
	model(m)
{

}

DeleteModelAction::~DeleteModelAction()
{

}

void DeleteModelAction::execute(MainWindow* mainWindow)
{
	// check is location exist
	if (!FileHelper::exists(model->location))
	{
		DialogHelper::popDialog("This item directory is not exist.");
		return;
	}

	// delete directory
	FileHelper::deleteFile(model->location);
	delete model;
}
