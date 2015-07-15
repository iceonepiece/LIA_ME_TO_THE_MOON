#ifndef EDITABLEMODE_H
#define EDITABLEMODE_H

#include "Mode.h"

class EditableMode : public Mode
{
public:
	EditableMode(QPushButton* btn_mode);
	~EditableMode();

	QImage getQImage(DataImage* image);
	void enterMode(Mode* mode, ImageView* view);
};

#endif // EDITABLEMODE_H
