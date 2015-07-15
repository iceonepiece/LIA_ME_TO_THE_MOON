#ifndef ORIGINALMODE_H
#define ORIGINALMODE_H

#include "Mode.h"

class OriginalMode : public Mode
{
public:
	OriginalMode(QPushButton* btn_mode);
	~OriginalMode();

	QImage getQImage(DataImage* image);
	void enterMode(Mode* mode, ImageView* view);
	
};

#endif // ORIGINALMODE_H
