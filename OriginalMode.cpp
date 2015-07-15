#include "OriginalMode.h"
#include "ImageView.h"

OriginalMode::OriginalMode( QPushButton* b):
	Mode(b)
{

}

OriginalMode::~OriginalMode()
{

}

QImage OriginalMode::getQImage(DataImage* image)
{
	return ImageHelper::matToQImage( image->mat_original );
}

void OriginalMode::enterMode(Mode* mode, ImageView* view)
{
	if (this != mode)
	{
		btn_mode->setStyleSheet("QPushButton{background-color: none;}");
		view->changeMode(mode);
	}
}