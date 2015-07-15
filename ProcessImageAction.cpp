#include "ProcessImageAction.h"
#include "MainWindow.h"
#include "qdebug.h"

ProcessImageAction::ProcessImageAction( DataImage* i, bool opt ):
	image(i), option(opt)
{

}

ProcessImageAction::~ProcessImageAction()
{

}

void ProcessImageAction::execute(MainWindow* mainWindow)
{
	Processor* processor = mainWindow->getProcessor( image->type );
	
	if (processor == nullptr)
	{
		qDebug() << "NULL JA";
		return;
	}

	if (option == false)
	{
		processor->process(image);
		processor->computePercentage(image->data_edited);

		processor->setupOption(image);
		processor->highlight(image->data_edited);
		processor->copy(image->data_edited, image->data_processed);
	}
	else
	{
		processor->process(image, true);
		processor->computePercentage(image->data_edited);

		processor->highlight(image->data_edited);

	}
}
