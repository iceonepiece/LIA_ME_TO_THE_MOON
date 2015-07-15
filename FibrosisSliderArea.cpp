#include "FibrosisSliderArea.h"
#include "qdebug.h"

FibrosisSliderArea::FibrosisSliderArea(QWidget *parent):
	SliderArea(parent)
{
	// setup for size
	lbl_saturationHead = new QLabel(this);
	lbl_saturationHead->setText("Saturation");
	lbl_saturationHead->setGeometry(0, 0, 150, 20);

	lbl_meanFib = new QLabel(this);
	lbl_meanFib->setText("Green");
	lbl_meanFib->setGeometry(0, 30, 40, 20);

	lbl_meanFibValue = new QLabel(this);
	lbl_meanFibValue->setGeometry(200, 30, 100, 20);

	lbl_meanTis = new QLabel(this);
	lbl_meanTis->setText("Red");
	lbl_meanTis->setGeometry(0, 60, 40, 20);

	lbl_meanTisValue = new QLabel(this);
	lbl_meanTisValue->setGeometry(200, 60, 100, 20);

	slider_meanFib = new QSlider(Qt::Horizontal, this);
	slider_meanFib->setRange(0, 255);
	slider_meanFib->setGeometry(35, 30, 150, 20);

	slider_meanTis = new QSlider(Qt::Horizontal, this);
	slider_meanTis->setRange(0, 255);
	slider_meanTis->setGeometry(35, 60, 150, 20);

	connect(slider_meanFib, SIGNAL(valueChanged(int)), this, SLOT(updateSlider()));
	connect(slider_meanTis, SIGNAL(valueChanged(int)), this, SLOT(updateSlider()));
}

FibrosisSliderArea::~FibrosisSliderArea()
{

}

void FibrosisSliderArea::setupSlider(DataOption* opt)
{
	FibrosisOption* fibOpt = (FibrosisOption*)opt;

	qDebug() << fibOpt->meanFib << " : " << fibOpt->meanTis;
	slider_meanFib->setValue(fibOpt->meanFib);
	slider_meanTis->setValue(fibOpt->meanTis);
}

void FibrosisSliderArea::updateSlider()
{
	std::string str_meanFib = std::to_string(slider_meanFib->value());
	std::string str_meanTis = std::to_string(slider_meanTis->value());

	lbl_meanFibValue->setText(str_meanFib.c_str());
	lbl_meanTisValue->setText(str_meanTis.c_str());
}

void FibrosisSliderArea::getOption(DataOption* opt)
{
	FibrosisOption* opt_fib = (FibrosisOption*)opt;
	opt_fib->meanFib = slider_meanFib->value();
	opt_fib->meanTis = slider_meanTis->value();
}
