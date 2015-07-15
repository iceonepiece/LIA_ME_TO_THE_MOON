#ifndef PROCESSEDMODE_H
#define PROCESSEDMODE_H

#include "Mode.h"

class ProcessedMode : public Mode
{
public:
	ProcessedMode( QPushButton* btn_mode );
	~ProcessedMode();

	QImage getQImage(DataImage* image);
	void enterMode(Mode* mode, ImageView* view);
	
};

#endif // PROCESSEDMODE_H
