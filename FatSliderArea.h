#ifndef FATSLIDERAREA_H
#define FATSLIDERAREA_H

#include <QLineEdit>
#include <QValidator>
#include "SliderArea.h"
#include "FatOption.h"
#include "StringHelper.h"

class FatSliderArea : public SliderArea
{
public:
	FatSliderArea(QWidget *parent);
	~FatSliderArea();

	void setupSlider(DataOption* opt);
	void getOption(DataOption* opt);

public slots:
	void updateSlider();
	void updateLineEdit();

private:
	// size
	QLabel* lbl_sizeHead;
	QLabel* lbl_minSize;
	QLabel* lbl_minSizeValue;
	QLabel* lbl_maxSize;
	QLabel* lbl_maxSizeValue;

	QSlider* slider_minSize;
	QSlider* slider_maxSize;

	QLineEdit* lEdit_minSize;
	QLineEdit* lEdit_maxSize;

	// circularity
	QLabel* lbl_cirHead;
	QLabel* lbl_minCir;
	QLabel* lbl_minCirValue;
	QLabel* lbl_maxCir;
	QLabel* lbl_maxCirValue;

	QSlider* slider_minCir;
	QSlider* slider_maxCir;

	QLineEdit* lEdit_minCir;
	QLineEdit* lEdit_maxCir;
};

#endif // FATSLIDERAREA_H
