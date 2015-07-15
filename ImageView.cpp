#include "ImageView.h"
#include "MainWindow.h"
#include "qdebug.h"

ImageView::ImageView(MainWindow* window):
	View(window)
{
	this->makeUi();
	this->makeConnection();

	list_mode.push_back(new OriginalMode(btn_oriMode));
	list_mode.push_back(new ProcessedMode(btn_proMode));
	list_mode.push_back(new EditableMode(btn_editMode));

}

ImageView::~ImageView()
{

	for (Mode* mode : list_mode)
	{
		delete mode;
	}
}	

void ImageView::makeUi()
{
	area_slider = new QStackedWidget(this);
	area_slider->addWidget(new FatSliderArea(this));
	area_slider->addWidget(new FibrosisSliderArea(this));
	area_slider->setGeometry(20, 145, 250, 200);

	lbl_imageIcon = new QLabel(this);
	lbl_imageIcon->setPixmap(QPixmap("Resources/icon_image.png"));
	lbl_imageIcon->setGeometry(130, 20, 35, 35);

	lbl_imageName = new QLabel(this);
	lbl_imageName->setFont(QFont("Arial", 14));
	lbl_imageName->setGeometry(170, 20, 400, 30);

	lbl_arrow = new QLabel(this);
	lbl_arrow->setText(">");
	lbl_arrow->setFont(QFont("Arial", 14));
	lbl_arrow->setGeometry(110, 20, 10, 30);

	tBtn_menu = new QToolButton(this);
	tBtn_menu->setPopupMode(QToolButton::InstantPopup);
	tBtn_menu->setFont(QFont("Arial", 14));
	tBtn_menu->setText("Menu");
	tBtn_menu->setGeometry(20, 20, 80, 30);

	act_folder = new QAction(this);
	act_folder->setFont(QFont("Arial", 12));
	act_folder->setIcon(QIcon("Resources/icon_folder.png"));

	act_patient = new QAction(this);
	act_patient->setFont(QFont("Arial", 12));
	act_patient->setIcon(QIcon("Resources/icon_patient.png"));

	act_home = new QAction(this);
	act_home->setText("Home");
	act_home->setFont(QFont("Arial", 12));
	act_home->setIcon(QIcon("Resources/icon_home.png"));

	tBtn_menu->addAction(act_folder);
	tBtn_menu->addAction(act_patient);
	tBtn_menu->addAction(act_home);

	// set up zoom ui
	btn_zoomOut = new QPushButton(this);
	btn_zoomOut->setText("-");
	btn_zoomOut->setGeometry(1070, 20, 30, 30);
	
	btn_zoomIn = new QPushButton(this);
	btn_zoomIn->setGeometry(1170, 20, 30, 30);
	btn_zoomIn->setText("+");

	com_zoom = new QComboBox(this);
	com_zoom->addItem("25%");
	com_zoom->addItem("50%");
	com_zoom->addItem("75%");
	com_zoom->addItem("100%");
	com_zoom->addItem("125%");
	com_zoom->addItem("150%");
	com_zoom->addItem("175%");
	com_zoom->addItem("200%");
	com_zoom->setGeometry(1100, 20, 70, 30);
	// ------------------ END ------------------ //

	// setup view modes buttons
	btn_oriMode = new QPushButton(this);
	btn_oriMode->setText("Original");
	btn_oriMode->setGeometry(800, 20, 80, 30);

	btn_proMode = new QPushButton(this);
	btn_proMode->setText("Processed");
	btn_proMode->setGeometry(880, 20, 80, 30);

	btn_editMode = new QPushButton(this);
	btn_editMode->setText("Editable");
	btn_editMode->setGeometry(960, 20, 80, 30);
	// ------------------ END ------------------ //

	// Show percentage labels

	lbl_showType = new QLabel(this);
	lbl_showType->setFont(QFont("Arial", 12));
	//lbl_showType->setText("Type: Fat");
	//lbl_showType->setGeometry(20, 60, 230, 20);

	lbl_proPercentHead = new QLabel(this);
	lbl_proPercentHead->setFont(QFont("Arial", 10));
	lbl_proPercentHead->setText("Processed");
	lbl_proPercentHead->setGeometry(40, 60, 115, 15);

	lbl_proPercentValue = new QLabel(this);
	lbl_proPercentValue->setFont(QFont("Arial", 12));
	lbl_proPercentValue->setGeometry(40, 85, 115, 15);

	lbl_editPercentHead = new QLabel(this);
	lbl_editPercentHead->setFont(QFont("Arial", 10));
	lbl_editPercentHead->setText("Edited");
	lbl_editPercentHead->setGeometry(155, 60, 115, 15);

	lbl_editPercentValue = new QLabel(this);
	lbl_editPercentValue->setFont(QFont("Arial", 12));
	lbl_editPercentValue->setGeometry(155, 85, 115, 15);


	// ------------------ END ------------------ //

	btn_save = new QPushButton(this);
	btn_save->setGeometry(20, 115, 100, 25);
	btn_save->setText("Save Image");

	btn_process = new QPushButton(this);
	btn_process->setGeometry(140, 115, 100, 25);
	btn_process->setText("Process");

	sArea_image = new QScrollArea(this);
	sArea_image->setGeometry(260, 60, 940, 600);

	lbl_note = new QLabel(this);
	lbl_note->setFont(QFont("Arial", 12, 1));
	lbl_note->setText("Note:");
	lbl_note->setGeometry(20, 350, 220, 20);

	txt_note = new QTextEdit(this);
	txt_note->setFont(QFont("Arial", 12));
	txt_note->setGeometry(20, 370, 220, 290 );

}

void ImageView::makeConnection()
{
	connect(tBtn_menu, SIGNAL(triggered(QAction*)), this, SLOT(goBack(QAction*)));
	connect(btn_oriMode, SIGNAL(clicked()), this, SLOT(enterOriginalMode()));
	connect(btn_proMode, SIGNAL(clicked()), this, SLOT(enterProcessedMode()));
	connect(btn_editMode, SIGNAL(clicked()), this, SLOT(enterEditableMode()));
	connect(btn_save, SIGNAL(clicked()), this, SLOT(saveImage()));
	connect(btn_process, SIGNAL(clicked()), this, SLOT(processImage()));

	connect(btn_zoomIn, SIGNAL(clicked()), this, SLOT(zoomIn()));
	connect(btn_zoomOut, SIGNAL(clicked()), this, SLOT(zoomOut()));
	connect(com_zoom, SIGNAL(currentIndexChanged(int)), this, SLOT(zoomTo(int)));
	
	
}


void ImageView::onStart()
{
	panel_image = new ImagePanel(nullptr, nullptr);

	currentImage = mainWindow->getCurrentImage();

	std::string prefix = "[ " + currentImage->typeStr +" ] - ";
	lbl_imageName->setText( ( prefix + currentImage->name ).c_str() );
	act_patient->setText(mainWindow->getCurrentPatient()->name.c_str());
	act_folder->setText(mainWindow->getCurrentFolder()->name.c_str());

	txt_note->setText(currentImage->note.c_str());

	if ( currentImage->type == -2)
		area_slider->setCurrentIndex(0);
	else if ( currentImage->type == -3)
		area_slider->setCurrentIndex(1);

	((SliderArea*)area_slider->currentWidget())->setupSlider(currentImage->option);

	this->changeMode(list_mode[ORIGINAL_MODE]);
}

void ImageView::onStop()
{
	currentImage->note = txt_note->toPlainText().toStdString();
	mode_current->btn_mode->setStyleSheet("QPushButton{background-color: none;}");
}

void ImageView::updateView()
{
	lbl_proPercentValue->setText( currentImage->data_processed->getPercentString().c_str());
	lbl_editPercentValue->setText( currentImage->data_edited->getPercentString().c_str());

	int v = sArea_image->verticalScrollBar()->value();
	int h = sArea_image->horizontalScrollBar()->value();

	delete panel_image;
	panel_image = new ImagePanel(mainWindow, this);

	int disHeight = ImageHelper::findZoomSize(currentImage->mat_original.size().height, currentImage->zoom * 25);
	int disWidth = ImageHelper::findZoomSize(currentImage->mat_original.size().width, currentImage->zoom * 25);

	panel_image->setImage(QPixmap::fromImage(
		mode_current->getQImage(currentImage).scaled(disWidth, disHeight)
		));

	com_zoom->setCurrentIndex( currentImage->zoom - 1);
	

	sArea_image->setWidget(panel_image);
	sArea_image->verticalScrollBar()->setValue(v);
	sArea_image->horizontalScrollBar()->setValue(h);


}

void ImageView::enterOriginalMode()
{
	mode_current->enterMode(list_mode[ORIGINAL_MODE], this );	
}

void ImageView::enterProcessedMode()
{
	mode_current->enterMode(list_mode[PROCESSED_MODE], this );
}

void ImageView::enterEditableMode()
{
	mode_current->enterMode(list_mode[EDITABLE_MODE], this );
}

void ImageView::changeMode(Mode* mode)
{
	mode_current = mode;
	mode_current->btn_mode->setStyleSheet("QPushButton{background-color: #AAAAFF;}");

	this->setEditEnabled(mode_current == list_mode[EDITABLE_MODE]);
	this->updateView();
}

void ImageView::setEditEnabled(bool b)
{
	area_slider->setEnabled(b);
	btn_process->setEnabled(b);
}

void ImageView::goBack(QAction* action)
{
	if (action == act_home)
		mainWindow->changeView(MainWindow::HOME_VIEW);

	else if (action == act_patient)
		mainWindow->changeView(MainWindow::PATIENT_VIEW);

	else if (action == act_folder)
		mainWindow->changeView(MainWindow::FOLDER_VIEW);
}

void ImageView::processImage()
{
	qDebug() << "PROCESS IMAGE";
	((SliderArea*)area_slider->currentWidget())->getOption(currentImage->option);
	mainWindow->executeAction(new ProcessImageAction( currentImage, true ));
	this->updateView();
}

void ImageView::saveImage()
{
	currentImage->note = txt_note->toPlainText().toStdString();
	mainWindow->executeAction( new SaveImageAction(currentImage) );
}

void ImageView::zoomTo(int n)
{
	currentImage->zoom = n + 1;
	this->updateView();
}

void ImageView::zoomIn()
{
	if (currentImage->zoom < 8)
		currentImage->zoom++;

	this->updateView();
}

void ImageView::zoomOut()
{
	if (currentImage->zoom > 1)
		currentImage->zoom--;

	this->updateView();
}
