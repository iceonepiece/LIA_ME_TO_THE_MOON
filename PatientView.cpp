#include "PatientView.h"
#include "MainWindow.h"
#include "qdebug.h"

PatientView::PatientView(MainWindow* window) :
	View(window)
{
	this->makeUi();
	this->makeConnection();
}

PatientView::~PatientView()
{

}

void PatientView::makeUi()
{
	lbl_patientIcon = new QLabel(this);
	lbl_patientIcon->setPixmap( QPixmap("Resources/icon_patient.png") );
	lbl_patientIcon->setGeometry(130, 20, 35, 35);

	lbl_patientName = new QLabel(this);
	lbl_patientName->setFont(QFont("Arial", 14));
	lbl_patientName->setGeometry(170, 20, 400, 30);

	lbl_arrow = new QLabel(this);
	lbl_arrow->setText(">");
	lbl_arrow->setFont(QFont("Arial", 14));
	lbl_arrow->setGeometry(110, 20, 10, 30);

	btn_home = new QPushButton(this);
	btn_home->setText("Home");
	btn_home->setFont(QFont("Arial", 14));
	btn_home->setGeometry(20, 20, 80, 30);

	btn_newFolder = new QPushButton(this);
	btn_newFolder->setText("New Folder");
	btn_newFolder->setGeometry(20, 60, 140, 40);

	btn_delFolder = new QPushButton(this);
	btn_delFolder->setText("Delete Folder");
	btn_delFolder->setGeometry(20, 110, 140, 40);

	lbl_type = new QLabel(this);
	lbl_type->setText("Type");
	lbl_type->setGeometry(20, 170, 140, 15);

	com_type = new QComboBox(this);
	com_type->addItem("All");
	com_type->addItem("Fat");
	com_type->addItem("Fibrosis");
	com_type->setGeometry(20, 190, 140, 30);

	lEdit_search = new QLineEdit(this);
	lEdit_search->setPlaceholderText("Search");
	lEdit_search->setGeometry(910, 20, 260, 30);

	QStringList headList;
	headList << "Name" << "Type";
	tab_folders = new QTableWidget(this);
	tab_folders->setColumnCount(2);
	tab_folders->setColumnWidth(0, 350);
	tab_folders->setColumnWidth(1, 150);
	tab_folders->setHorizontalHeaderLabels(headList);
	tab_folders->setSelectionBehavior(QAbstractItemView::SelectRows);
	tab_folders->setEditTriggers(QAbstractItemView::NoEditTriggers);
	tab_folders->setGeometry(180, 60, 990, 600);
}

void PatientView::makeConnection()
{
	connect(btn_newFolder, SIGNAL(clicked()), this, SLOT(showNewFolderDialog()));
	connect(tab_folders, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(enterFolder(int, int)));
	connect(btn_home, SIGNAL(clicked()), this, SLOT(goHome()));
	connect(btn_delFolder, SIGNAL(clicked()), this, SLOT(deleteFolder()));
	connect(com_type, SIGNAL(activated(int)), this, SLOT(updateView()));
	connect(lEdit_search, SIGNAL(textEdited(QString)), this, SLOT(updateView()));
}

void PatientView::onStart()
{
	currentPatient = mainWindow->getCurrentPatient();
	lbl_patientName->setText(currentPatient->name.c_str());
	list_folder = currentPatient->list_folder;
	lEdit_search->clear();
	com_type->setCurrentIndex(0);
	this->updateView();
}

void PatientView::onStop()
{

}

void PatientView::updateView()
{
	list_folder = mainWindow->getModelListByKey(MainWindow::FOLDER_MODEL, lEdit_search->text().toStdString());
	this->groupType(com_type->currentIndex());
	
	tab_folders->setRowCount(0);

	for (int i = 0; i < list_folder.size(); i++)
	{
		Folder* folder = (Folder*)list_folder[i];

		tab_folders->insertRow(i);
		tab_folders->setItem(i, 0, new QTableWidgetItem(QString(folder->name.c_str())));
		tab_folders->setItem(i, 1, new QTableWidgetItem(QString(folder->typeStr.c_str())));
	}
}

void PatientView::groupType(int index)
{
	
	if (index == 0)
		return;

	int n = -2;

	if (index == 2)
		n = -3;

	std::vector<Model*> list_groupFolder;

	for (int i = 0; i < list_folder.size(); i++)
	{
		if (((Folder*)list_folder[i])->type == n)
			list_groupFolder.push_back(list_folder[i]);
	}

	list_folder = list_groupFolder;
	
}

void PatientView::search(QString keyword)
{
	this->updateView();
}


void PatientView::showNewFolderDialog()
{
	qDebug() << "Address in PatientView.showNewFolder() = " << mainWindow->getCurrentPatient();
	NewFolderDialog dialog(mainWindow);
	dialog.exec();
}

void PatientView::enterFolder(int row, int col)
{
	mainWindow->setCurrentFolder( (Folder*)list_folder[row] );
	mainWindow->changeView(MainWindow::FOLDER_VIEW);
}

void PatientView::deleteFolder()
{
	QItemSelectionModel*select = tab_folders->selectionModel();
	QModelIndexList list = select->selectedRows();

	int size = list.size();

	if (size == 0)
		return;

	std::string title;
	std::string question;

	if (size == 1)
	{
		title = "Delete Folder";
		question = "Are you sure want to delete this folder?";
	}
	else
	{
		title = "Delete Multiple Folders";
		question = "Are you sure want to delete these " + std::to_string(size) + " folders?";
	}

	if (!DialogHelper::popQuestionDialog(title, question) == true)
		return;

	std::vector<Model*> list_tempFolder;

	for (int i = 0; i < list_folder.size(); i++)
	{
		bool stay = true;
		for (int j = 0; j < size; j++)
		{
			if (i == list.at(j).row())
			{
				stay = false;

				mainWindow->executeAction(new DeleteModelAction(list_folder[i]));

				break;
			}
		}

		if (stay)
			list_tempFolder.push_back(list_folder[i]);
	}

	currentPatient->list_folder = list_tempFolder;
	FileHelper::writeXML(currentPatient);
	this->updateView();
}

void PatientView::goHome()
{
	mainWindow->changeView(MainWindow::HOME_VIEW);
}