#ifndef SLIDERAREA_H
#define SLIDERAREA_H

#include <QWidget>
#include <QLabel>
#include <QSlider>
#include "DataOption.h"

class SliderArea : public QWidget
{
	Q_OBJECT

public:
	SliderArea(QWidget *parent);
	~SliderArea();

	virtual void setupSlider(DataOption* opt) = 0;
	virtual void getOption(DataOption* opt) = 0;

public slots:
	virtual void updateSlider() = 0;
};


#endif // SLIDERAREA_H
