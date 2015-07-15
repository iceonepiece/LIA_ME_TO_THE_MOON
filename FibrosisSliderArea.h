#ifndef FIBROSISSLIDERAREA_H
#define FIBROSISSLIDERAREA_H

#include "SliderArea.h"
#include "FibrosisOption.h"

class FibrosisSliderArea : public SliderArea
{
public:
	FibrosisSliderArea(QWidget *parent);
	~FibrosisSliderArea();

	void setupSlider(DataOption* opt);
	void getOption(DataOption* opt);

public slots:
	void updateSlider();

private:
	
	QLabel* lbl_saturationHead;

	QLabel* lbl_meanFib;
	QLabel* lbl_meanFibValue;

	QLabel* lbl_meanTis;
	QLabel* lbl_meanTisValue;

	QSlider* slider_meanFib;
	QSlider* slider_meanTis;

	
};

#endif // FIBROSISSLIDERAREA_H
