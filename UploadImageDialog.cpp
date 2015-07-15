#include "UploadImageDialog.h"
#include "MainWindow.h"

UploadImageDialog::UploadImageDialog( MainWindow* window ):
	Dialog(window)
{
	this->makeUi();
	this->makeConnection();
}

UploadImageDialog::~UploadImageDialog()
{

}

void UploadImageDialog::makeUi()
{
	btn_browse = new QPushButton(this);
	btn_browse->setText("Browse...");
	btn_browse->setGeometry(10, 10, 80, 30);

	btn_delete = new QPushButton(this);
	btn_delete->setText("Delete");
	btn_delete->setGeometry(10, 50, 80, 30);

	btn_upload = new QPushButton(this);
	btn_upload->setText("Upload");
	btn_upload->setGeometry(300, 250, 80, 30);

	btn_cancel = new QPushButton(this);
	btn_cancel->setText("Cancel");
	btn_cancel->setGeometry(390, 250, 80, 30);

	QStringList headList;
	headList << "Image" << "Filename" << "Size";
	tab_image = new QTableWidget(this);
	tab_image->setColumnCount(3);
	tab_image->setColumnWidth(0, 80);
	tab_image->setColumnWidth(1, 200);
	tab_image->setColumnWidth(2, 80);
	tab_image->setHorizontalHeaderLabels(headList);
	tab_image->setSelectionBehavior(QAbstractItemView::SelectRows);
	tab_image->setEditTriggers(QAbstractItemView::NoEditTriggers);
	tab_image->verticalHeader()->sectionResizeMode(QHeaderView::Fixed);
	tab_image->verticalHeader()->setDefaultSectionSize(50);
	tab_image->setGeometry(100, 10, 390, 230);
}


void UploadImageDialog::makeConnection()
{
	connect(btn_browse, SIGNAL(clicked()), this, SLOT(browseImage()));
	connect(btn_delete, SIGNAL(clicked()), this, SLOT(deleteImage()));
	connect(btn_cancel, SIGNAL(clicked()), this, SLOT(close()));
	connect(btn_upload, SIGNAL(clicked()), this, SLOT(uploadImage()));

}

void UploadImageDialog::updateDialog()
{
	tab_image->setRowCount(0);

	for (int i = 0; i < list_imagePath.size(); i++)
	{
		QFileInfo fileInfo(list_imagePath.at(i));
		QPixmap pixmap;
		if (pixmap.load(list_imagePath.at(i)))
		{
			QTableWidgetItem* image = new QTableWidgetItem;
			image->setData(Qt::DecorationRole, pixmap.scaled(50, 50));
			tab_image->insertRow(i);
			tab_image->setItem( i, 0, image );
			tab_image->setItem( i, 1, new QTableWidgetItem( fileInfo.fileName() ) );

			std::string imageSize = std::to_string(pixmap.width()) + " X " + std::to_string(pixmap.height());
			tab_image->setItem(i, 2, new QTableWidgetItem( QString(imageSize.c_str()) ) );
			
		}
	}
}


void UploadImageDialog::browseImage()
{
	QStringList list = QFileDialog::getOpenFileNames();
	for (int i = 0; i < list.size(); i++)
	{
		QPixmap pixmap;
		if (pixmap.load(list.at(i)))
			list_imagePath.push_back(list.at(i));
	}

	updateDialog();
}

void UploadImageDialog::deleteImage()
{
	QItemSelectionModel *select = tab_image->selectionModel();
	QModelIndexList list = select->selectedRows();

	QStringList dummyImagePathList;

	for (int i = 0; i < list_imagePath.size(); i++)
	{
		bool stay = true;
		for (int j = 0; j < list.size(); j++)
		{
			if (i == list.at(j).row())
			{
				stay = false;
				break;
			}
		}

		if (stay)
			dummyImagePathList.push_back(list_imagePath.at(i));
	}

	list_imagePath = dummyImagePathList;

	updateDialog();
}

void UploadImageDialog::uploadImage()
{		
	for (QString path : list_imagePath)
	{
		mainWindow->executeAction(new UploadImageAction(path.toStdString()));
	}

	this->close();
}
