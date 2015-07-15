#include "SaveImageAction.h"

SaveImageAction::SaveImageAction(DataImage* img):
	image(img)
{

}

SaveImageAction::~SaveImageAction()
{

}


void SaveImageAction::execute(MainWindow* window)
{
	if (!cv::imwrite(image->location + "/pro_" + image->name, image->data_processed->mat_model))
	{
		DialogHelper::popDialog("Can't save processed image.");
		return;
	}

	if (!cv::imwrite(image->location + "/edit_" + image->name, image->data_edited->mat_model))
	{
		DialogHelper::popDialog("Can't save edited image.");
		return;
	}

	FileHelper::writeXML(image);

}