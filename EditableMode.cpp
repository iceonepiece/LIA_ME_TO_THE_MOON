#include "EditableMode.h"
#include "ImageView.h"

EditableMode::EditableMode( QPushButton* b ):
	Mode(b)
{

}

EditableMode::~EditableMode()
{

}

QImage EditableMode::getQImage(DataImage* image)
{

	return ImageHelper::matToQImage(image->data_edited->mat_display);
}

void EditableMode::enterMode(Mode* mode, ImageView* view)
{
	
	if (this != mode)
	{
		btn_mode->setStyleSheet("QPushButton{background-color: none;}");
		view->changeMode(mode);
	}
}