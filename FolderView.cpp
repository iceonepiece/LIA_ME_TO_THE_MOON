#include "FolderView.h"
#include "MainWindow.h"
#include "qdebug.h"

FolderView::FolderView( MainWindow* window ):
	View(window)
{
	this->makeUi();
	this->makeConnection();
}

FolderView::~FolderView()
{

}

void FolderView::makeUi()
{
	lbl_folderIcon = new QLabel(this);
	lbl_folderIcon->setPixmap(QPixmap("Resources/icon_folder.png"));
	lbl_folderIcon->setGeometry(130, 20, 35, 35);

	lbl_folderName = new QLabel(this);
	lbl_folderName->setFont(QFont("Arial", 14));
	lbl_folderName->setGeometry(170, 20, 400, 30);

	lbl_arrow = new QLabel(this);
	lbl_arrow->setText(">");
	lbl_arrow->setFont(QFont("Arial", 14));
	lbl_arrow->setGeometry(110, 20, 10, 30);

	act_patient = new QAction(this);
	act_patient->setFont(QFont("Arial", 12));
	act_patient->setIcon(QIcon("Resources/icon_patient.png"));
	
	act_home = new QAction(this);
	act_home->setText("Home");
	act_home->setFont(QFont("Arial", 12));
	act_home->setIcon(QIcon("Resources/icon_home.png"));

	tBtn_menu = new QToolButton(this);
	tBtn_menu->setPopupMode(QToolButton::InstantPopup);
	tBtn_menu->setFont(QFont("Arial", 14));
	tBtn_menu->setText("Menu");
	tBtn_menu->setGeometry(20, 20, 80, 30);

	tBtn_menu->addAction(act_patient);
	tBtn_menu->addAction(act_home);

	btn_uploadImage = new QPushButton(this);
	btn_uploadImage->setText("Upload Image");
	btn_uploadImage->setGeometry(20, 60, 140, 40);

	btn_delImage = new QPushButton(this);
	btn_delImage->setText("Delete Image");
	btn_delImage->setGeometry(20, 110, 140, 40);

	lEdit_search = new QLineEdit(this);
	lEdit_search->setPlaceholderText("Search");
	lEdit_search->setGeometry(910, 20, 260, 30);

	QStringList headList;
	headList << "Image" << "Name" << "Processed %" << "Edited %" << "Size";
	tab_images = new QTableWidget(this);
	tab_images->setColumnCount(5);
	tab_images->setColumnWidth(0, 120);
	tab_images->setColumnWidth(1, 320);
	tab_images->setColumnWidth(2, 120);
	tab_images->setColumnWidth(3, 120);
	tab_images->setColumnWidth(4, 120);
	tab_images->setHorizontalHeaderLabels(headList);
	tab_images->setSelectionBehavior(QAbstractItemView::SelectRows);
	tab_images->setEditTriggers(QAbstractItemView::NoEditTriggers);
	tab_images->verticalHeader()->sectionResizeMode(QHeaderView::Fixed);
	tab_images->verticalHeader()->setDefaultSectionSize(80);
	tab_images->setGeometry(180, 60, 990, 600);
}

void FolderView::makeConnection()
{
	connect(tBtn_menu, SIGNAL(triggered(QAction*)), this, SLOT(goBack(QAction*)));
	connect(btn_uploadImage, SIGNAL(clicked()), this, SLOT(showUploadImageDialog()));
	connect(btn_delImage, SIGNAL(clicked()), this, SLOT(deleteImage()));
	connect(tab_images, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(enterImage(int,int)));
	connect(lEdit_search, SIGNAL(textEdited(QString)), this, SLOT(updateView()));
}

void FolderView::onStart()
{
	currentFolder = mainWindow->getCurrentFolder();

	std::string prefix = "[ " + currentFolder->typeStr + " ] - ";
	lbl_folderName->setText((prefix + currentFolder->name).c_str());
	act_patient->setText(mainWindow->getCurrentPatient()->name.c_str());
	lEdit_search->clear();
	this->updateView();
}

void FolderView::onStop()
{

}

void FolderView::updateView()
{
	list_image = mainWindow->getModelListByKey(MainWindow::DATA_IMAGE_MODEL, lEdit_search->text().toStdString());
	tab_images->setRowCount(0);

	for (int i = 0; i < list_image.size(); i++)
	{
		tab_images->insertRow(i);

		DataImage* dataImage = (DataImage*)list_image[i];

		QPixmap pixmap = QPixmap::fromImage(ImageHelper::matToQImage(dataImage->mat_original));
		if (  !pixmap.isNull() )
		{
			QTableWidgetItem* image = new QTableWidgetItem;
			image->setData(Qt::DecorationRole, pixmap.scaled(80, 80));
			tab_images->setItem(i, 0, image);

			std::string imageSize = std::to_string(pixmap.width()) + " X " + std::to_string(pixmap.height());
			tab_images->setItem(i, 4, new QTableWidgetItem(QString(imageSize.c_str())));
		}

		tab_images->setItem(i, 1, new QTableWidgetItem(QString(dataImage->name.c_str())));
		tab_images->setItem(i, 2, new QTableWidgetItem(QString(dataImage->data_processed->getPercentString().c_str())));
		tab_images->setItem(i, 3, new QTableWidgetItem(QString(dataImage->data_edited->getPercentString().c_str())));
		
	}
}

void FolderView::enterImage(int row, int col)
{
	mainWindow->setCurrentImage((DataImage*)list_image[row]);
	mainWindow->changeView(MainWindow::IMAGE_VIEW);

}

void FolderView::goBack(QAction* action)
{
	if ( action == act_home )
		mainWindow->changeView(MainWindow::HOME_VIEW);

	else if ( action == act_patient )
		mainWindow->changeView(MainWindow::PATIENT_VIEW);
}

void FolderView::goHome(bool f)
{
	mainWindow->changeView(MainWindow::HOME_VIEW);
}

void FolderView::showUploadImageDialog()
{
	UploadImageDialog dialog(mainWindow);
	dialog.exec();
}

void FolderView::deleteImage()
{
	QItemSelectionModel*select = tab_images->selectionModel();
	QModelIndexList list = select->selectedRows();

	int size = list.size();

	if (size == 0)
		return;

	std::string title;
	std::string question;

	if (size == 1)
	{
		title = "Delete Image";
		question = "Are you sure want to delete this image?";
	}
	else
	{
		title = "Delete Multiple Images";
		question = "Are you sure want to delete these " + std::to_string(size) + " images?";
	}

	if ( !DialogHelper::popQuestionDialog( title, question ) == true )
		return;

	std::vector<Model*> list_tempImage;

	for (int i = 0; i < list_image.size(); i++)
	{
		bool stay = true;
		for (int j = 0; j < size; j++)
		{
			if (i == list.at(j).row())
			{
				stay = false;

				mainWindow->executeAction( new DeleteModelAction( list_image[i] ) );

				break;
			}
		}

		if (stay)
			list_tempImage.push_back( list_image[i] );
	}

	currentFolder->list_dataImage = list_tempImage;
	FileHelper::writeXML(currentFolder);
	this->updateView();
}