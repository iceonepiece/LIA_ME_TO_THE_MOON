#include "ClickImageAction.h"
#include "ImageView.h"
#include "MainWindow.h"

ClickImageAction::ClickImageAction( ImageView* view, int x, int y) :
	imageView(view), x(x), y(y)
{

}

ClickImageAction::~ClickImageAction()
{

}

void ClickImageAction::execute(MainWindow* mainWindow)
{
	/*int currentZoom = currentDataImage->getCurrentZoom();

	float trueX = imagePanel->x / ((currentZoom * 25) / 100.0);
	float trueY = imagePanel->y / ((currentZoom * 25) / 100.0);

	if (currentDataImage->click(trueX, trueY))
		updateView();*/
	DataImage* image = mainWindow->getCurrentImage();
	Processor* processor = mainWindow->getProcessor(image->type);

	if (processor == nullptr)
		return;

	int currentZoom = image->zoom;

	float trueX = x / ((currentZoom * 25) / 100.0);
	float trueY = y / ((currentZoom * 25) / 100.0);

	if (processor->click(image->data_edited, trueX, trueY))
	{
		imageView->updateView();
	}


}
