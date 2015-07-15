#include "OpenPatientDialog.h"
#include "MainWindow.h"

OpenPatientDialog::OpenPatientDialog( MainWindow* window ):
	Dialog(window)
{
	this->makeUi();
	this->makeConnection();
}

OpenPatientDialog::~OpenPatientDialog()
{

}

void OpenPatientDialog::makeUi()
{
	this->resize(540, 120);
	this->setWindowTitle("Open Patient");

	lEdit_location = new QLineEdit(this);
	lEdit_location->setEnabled(false);
	lEdit_location->setGeometry(80, 20, 355, 30);

	lbl_location = new QLabel(this);
	lbl_location->setText("Location:");
	lbl_location->setGeometry(20, 20, 80, 30);

	btn_browse = new QPushButton(this);
	btn_browse->setText("Browse...");
	btn_browse->setGeometry(445, 20, 80, 30);

	btn_ok = new QPushButton(this);
	btn_ok->setText("OK");
	btn_ok->setGeometry(355, 70, 80, 30);

	btn_cancel = new QPushButton(this);
	btn_cancel->setText("Cancel");
	btn_cancel->setGeometry(445, 70, 80, 30);
}

void OpenPatientDialog::makeConnection()
{
	connect(btn_ok, SIGNAL(clicked()), this, SLOT(doOpenPatient()));
	connect(btn_cancel, SIGNAL(clicked()), this, SLOT(close()));
	connect(btn_browse, SIGNAL(clicked()), this, SLOT(browseLocation()));
}

void OpenPatientDialog::doOpenPatient()
{
	Message message;
	message["location"] = lEdit_location->text().toStdString();

	mainWindow->executeAction(new OpenPatientAction(message));
	this->close();
}

void OpenPatientDialog::browseLocation()
{
	QString filename = QFileDialog::getExistingDirectory(this);
	lEdit_location->setText(filename);
}
