#include "ProcessedMode.h"
#include "ImageView.h"

ProcessedMode::ProcessedMode(QPushButton* b):
	Mode(b)
{

}

ProcessedMode::~ProcessedMode()
{

}

QImage ProcessedMode::getQImage(DataImage* image)
{
	return ImageHelper::matToQImage(image->data_processed->mat_display);
}

void ProcessedMode::enterMode(Mode* mode, ImageView* view)
{
	if (this != mode)
	{
		btn_mode->setStyleSheet("QPushButton{background-color: none;}");
		view->changeMode(mode);
	}
}