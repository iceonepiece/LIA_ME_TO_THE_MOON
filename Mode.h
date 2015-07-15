#ifndef MODE_H
#define MODE_H

#include <QImage>
#include <QPushButton>
#include "DataImage.h"
#include "ImageHelper.h"


class ImageView;

class Mode
{
public:
	Mode(QPushButton* btn_mode);
	virtual ~Mode();

	virtual QImage getQImage(DataImage* image) = 0;
	virtual void enterMode(Mode* mode, ImageView* view) = 0;
	
	QPushButton* btn_mode;
};

#endif // MODE_H
