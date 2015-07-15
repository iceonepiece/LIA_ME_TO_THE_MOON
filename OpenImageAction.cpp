#include "OpenImageAction.h"
#include "MainWindow.h"

OpenImageAction::OpenImageAction(Folder* f, std::string p):
	folder(f), path(p)
{

}

OpenImageAction::~OpenImageAction()
{

}

void OpenImageAction::execute(MainWindow* window)
{
	if (!FileHelper::exists( path + "/image.lia" ))
	{
		DialogHelper::popDialog("This is not the image of LIA");
		return;
	}

	Message in;
	try
	{
		in = FileHelper::readImageXML(path);
	}
	catch (std::exception e)
	{
		DialogHelper::popDialog(e.what());
		return;
	}


	if (!window->isNameAvailable(folder->list_dataImage, in["name"]))
	{
		DialogHelper::popDialog("This Image's name has already been in the folder.");
		return;
	}

	DataImage* image;
	int type = std::atoi(in["type"].c_str());

	if (type == -2)
	{
		image = new FatImage(in["name"], type, in["location"], in["note"]);
	}
	else if (type == -3)
	{
		image = new FibrosisImage(in["name"], type, in["location"], in["note"]);
	}
	else
	{
		DialogHelper::popDialog("Error: Cannot load an image");
		return;
	}

	if (!image->load(in))
	{
		DialogHelper::popDialog("Error: Cannot load an image");
		delete image;
		return;
	}

	Processor* processor = window->getProcessor(image->type);
	processor->computePercentage(image->data_processed);
	processor->computePercentage(image->data_edited);
	processor->highlight(image->data_processed);
	processor->highlight(image->data_edited);

	folder->list_dataImage.push_back(image);
}
