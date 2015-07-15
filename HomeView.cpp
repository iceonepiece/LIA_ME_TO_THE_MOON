#include "HomeView.h"
#include "MainWindow.h"
#include "qdebug.h"

HomeView::HomeView( MainWindow* window ) : 
	View( window )
{
	this->makeUi();
	this->makeConnection();
}

HomeView::~HomeView()
{
	
}

void HomeView::makeUi()
{
	lbl_title = new QLabel(this);
	lbl_title->setText("LIA");
	lbl_title->setFont(QFont("Arial", 14));
	lbl_title->setGeometry(30, 20, 120, 30);

	btn_newPatient = new QPushButton(this);
	btn_newPatient->setText("New Patient");
	btn_newPatient->setGeometry(20, 60, 140, 40);

	btn_openPatient = new QPushButton(this);
	btn_openPatient->setText("Open Patient");
	btn_openPatient->setGeometry(20, 110, 140, 40);

	btn_delPatient = new QPushButton(this);
	btn_delPatient->setText("Delete Patient");
	btn_delPatient->setGeometry(20, 160, 140, 40);

	lEdit_search = new QLineEdit(this);
	lEdit_search->setPlaceholderText("Search");
	lEdit_search->setGeometry(910, 20, 260, 30);

	QStringList headList;
	headList << "Name" << "Sex";
	tab_patients = new QTableWidget(this);
	tab_patients->setColumnCount(2);
	tab_patients->setColumnWidth(0, 350);
	tab_patients->setColumnWidth(1, 150);
	tab_patients->setHorizontalHeaderLabels(headList);
	tab_patients->setSelectionBehavior(QAbstractItemView::SelectRows);
	tab_patients->setEditTriggers(QAbstractItemView::NoEditTriggers);
	tab_patients->setGeometry(180, 60, 990, 600);
	
}

void HomeView::makeConnection()
{
	connect(btn_newPatient, SIGNAL(clicked()), this, SLOT(showNewPatientDialog()));
	connect(btn_openPatient, SIGNAL(clicked()), this, SLOT(showOpenPatientDialog()));
	connect(btn_delPatient, SIGNAL(clicked()), this, SLOT(deletePatient()));
	connect(tab_patients, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(enterPatient(int, int)));
	connect(lEdit_search, SIGNAL(textEdited(QString)), this, SLOT(updateView()));
}

void HomeView::onStart()
{
	lEdit_search->clear();
	this->updateView();
}

void HomeView::onStop()
{

}

void HomeView::updateView()
{
	qDebug() << "YO";
	list_patient = mainWindow->getModelListByKey(MainWindow::PATIENT_MODEL, lEdit_search->text().toStdString());
	tab_patients->setRowCount(0);

	for (int i = 0; i < list_patient.size(); i++)
	{
		Patient* patient = (Patient*)list_patient[i];
		tab_patients->insertRow(i);

		tab_patients->setItem(i, 0, new QTableWidgetItem(QString(patient->name.c_str())));

		std::string sexStr;
		if (patient->sex == -2)
			sexStr = "Male";
		else if (patient->sex == -3)
			sexStr = "Female";
		else
			sexStr = "...";

		tab_patients->setItem(i, 1, new QTableWidgetItem(QString(sexStr.c_str())));
	}
}

void HomeView::search(QString keyword)
{
	this->updateView();
}

void HomeView::showNewPatientDialog()
{
	NewPatientDialog dialog(mainWindow);
	dialog.exec();
}

void HomeView::showOpenPatientDialog()
{
	OpenPatientDialog dialog( mainWindow );
	dialog.exec();
}

void HomeView::deletePatient()
{
	QItemSelectionModel*select = tab_patients->selectionModel();
	QModelIndexList list = select->selectedRows();

	int size = list.size();

	if (size == 0)
		return;

	std::string title;
	std::string question;

	if (size == 1)
	{
		title = "Delete Patient";
		question = "Are you sure want to delete this patient?";
	}
	else
	{
		title = "Delete Multiple Patients";
		question = "Are you sure want to delete these " + std::to_string(size) + " patients?";
	}

	if (!DialogHelper::popQuestionDialog(title, question))
		return;

	std::vector<Model*> list_tempPatient;

	for (int i = 0; i < list_patient.size(); i++)
	{
		bool stay = true;
		for (int j = 0; j < size; j++)
		{
			if (i == list.at(j).row())
			{
				stay = false;

				mainWindow->executeAction(new DeleteModelAction(list_patient[i]));

				break;
			}
		}

		if (stay)
			list_tempPatient.push_back(list_patient[i]);
	}

	mainWindow->setPatientList(list_tempPatient);
	this->updateView();
}

void HomeView::enterPatient(int row, int col)
{
	mainWindow->setCurrentPatient((Patient*)list_patient[row]);
	mainWindow->changeView( MainWindow::PATIENT_VIEW );
}

