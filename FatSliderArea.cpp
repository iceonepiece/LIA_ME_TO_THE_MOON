#include "FatSliderArea.h"
#include "qdebug.h"

FatSliderArea::FatSliderArea(QWidget *parent):
	SliderArea(parent)
{
	// setup for size
	
	lbl_sizeHead = new QLabel(this);
	lbl_sizeHead->setText("Size");
	lbl_sizeHead->setGeometry(0, 0, 150, 20);

	lbl_minSize = new QLabel(this);
	lbl_minSize->setText("Min");
	lbl_minSize->setGeometry(0, 30, 40, 20);

	lbl_minSizeValue = new QLabel(this);
	lbl_minSizeValue->setGeometry(200, 30, 100, 20);

	lbl_maxSize = new QLabel(this);
	lbl_maxSize->setText("Max");
	lbl_maxSize->setGeometry(0, 60, 40, 20);

	lbl_maxSizeValue= new QLabel(this);
	lbl_maxSizeValue->setGeometry(200, 60, 100, 20);

	slider_minSize = new QSlider(Qt::Horizontal, this);
	slider_minSize->setGeometry(35, 30, 150, 20);

	slider_maxSize = new QSlider(Qt::Horizontal, this);
	slider_maxSize->setGeometry(35, 60, 150, 20);


	// setup for circularity
	lbl_cirHead = new QLabel(this);
	lbl_cirHead->setText("Circularity");
	lbl_cirHead->setGeometry(0, 100, 150, 20);

	lbl_minCir = new QLabel(this);
	lbl_minCir->setText("Min");
	lbl_minCir->setGeometry(0, 130, 40, 20);

	lbl_minCirValue = new QLabel(this);
	//lbl_minCirValue->setGeometry(200, 130, 100, 20);

	lbl_maxCir = new QLabel(this);
	lbl_maxCir->setText("Max");
	lbl_maxCir->setGeometry(0, 160, 40, 20);

	lbl_maxCirValue = new QLabel(this);
	lbl_maxCirValue->setGeometry(200, 160, 100, 20);

	slider_minCir = new QSlider(Qt::Horizontal, this);
	slider_minCir->setRange(0, 100);
	slider_minCir->setGeometry(35, 130, 150, 20);

	slider_maxCir = new QSlider(Qt::Horizontal, this);
	slider_maxCir->setRange(0, 100);
	slider_maxCir->setGeometry(35, 160, 150, 20);


	lEdit_minCir = new QLineEdit(this);
	lEdit_minCir->setValidator(new QIntValidator(0, 100, this));
	lEdit_minCir->setGeometry(200, 130, 100, 20);

	lEdit_maxCir = new QLineEdit(this);
	lEdit_maxCir->setValidator(new QIntValidator(0, 100, this));
	lEdit_maxCir->setGeometry(200, 160, 100, 20);

	connect(slider_minSize, SIGNAL(valueChanged(int)), this, SLOT(updateSlider()));
	connect(slider_maxSize, SIGNAL(valueChanged(int)), this, SLOT(updateSlider()));
	connect(slider_minCir, SIGNAL(valueChanged(int)), this, SLOT(updateSlider()));
	connect(slider_maxCir, SIGNAL(valueChanged(int)), this, SLOT(updateSlider()));
	connect(lEdit_minCir, SIGNAL(editingFinished()), this, SLOT(updateLineEdit()));
	connect(lEdit_maxCir, SIGNAL(editingFinished()), this, SLOT(updateLineEdit()));
}

FatSliderArea::~FatSliderArea()
{

}



void FatSliderArea::setupSlider(DataOption* opt)
{
	FatOption* fatOpt = (FatOption*)opt;


	qDebug() << "MAX Blob Size" << fatOpt->max_blobSize;
	// Size
	slider_minSize->setRange(fatOpt->min_blobSize, fatOpt->max_blobSize);
	slider_minSize->setValue(fatOpt->min_size);

	slider_maxSize->setRange(fatOpt->min_blobSize, fatOpt->max_blobSize);
	slider_maxSize->setValue(fatOpt->max_size);

	// Circularity
	slider_minCir->setValue(fatOpt->min_circularity);
	slider_maxCir->setValue(fatOpt->max_circularity);
}

void FatSliderArea::updateSlider()
{
	std::string str_minSize = std::to_string( slider_minSize->value() );
	std::string str_maxSize = std::to_string( slider_maxSize->value() );
	std::string str_minCir = StringHelper::getPrecisionString(slider_minCir->value() / 100.0, 2);
	std::string str_maxCir = StringHelper::getPrecisionString(slider_maxCir->value() / 100.0, 2);

	lbl_minSizeValue->setText(str_minSize.c_str());
	lbl_maxSizeValue->setText(str_maxSize.c_str());
	lbl_minCirValue->setText(str_minCir.c_str());
	lbl_maxCirValue->setText(str_maxCir.c_str());

	lEdit_minCir->setText(str_minCir.c_str());
	lEdit_maxCir->setText(str_maxCir.c_str());
}

void FatSliderArea::updateLineEdit()
{
	int minCir = std::atoi(lEdit_minCir->text().toStdString().c_str());
	slider_minCir->setValue(minCir);

	int maxCir = std::atoi(lEdit_maxCir->text().toStdString().c_str());
	slider_minCir->setValue(maxCir);
}

void FatSliderArea::getOption(DataOption* opt)
{
	FatOption* opt_fat = (FatOption*)opt;
	opt_fat->min_size = slider_minSize->value();
	opt_fat->max_size = slider_maxSize->value();
	opt_fat->min_circularity = slider_minCir->value();
	opt_fat->max_circularity = slider_maxCir->value();
}