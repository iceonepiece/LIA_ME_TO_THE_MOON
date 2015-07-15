#include "NewPatientDialog.h"
#include "MainWindow.h"
#include <qDebug>

NewPatientDialog::NewPatientDialog( MainWindow* window ):
	Dialog(window)
{
	this->makeUi();
	this->makeConnection();
}

NewPatientDialog::~NewPatientDialog()
{

}

void NewPatientDialog::makeUi()
{
	this->resize(540, 200);
	this->setWindowTitle("New Patient");

	lEdit_name = new QLineEdit(this);
	lEdit_name->setGeometry(80, 20, 355, 30);

	lEdit_location = new QLineEdit(this);
	lEdit_location->setEnabled(false);
	lEdit_location->setGeometry(80, 100, 355, 30);

	lbl_name = new QLabel(this);
	lbl_name->setText("Name:");
	lbl_name->setGeometry(20, 20, 80, 30);

	lbl_sex = new QLabel(this);
	lbl_sex->setText("Sex:");
	lbl_sex->setGeometry(20, 60, 40, 30);

	lbl_location = new QLabel(this);
	lbl_location->setText("Location:");
	lbl_location->setGeometry(20, 100, 60, 30);

	btn_ok = new QPushButton(this);
	btn_ok->setText("OK");
	btn_ok->setGeometry(355, 150, 80, 30);

	btn_cancel = new QPushButton(this);
	btn_cancel->setText("Cancel");
	btn_cancel->setGeometry(445, 150, 80, 30);

	btn_browse = new QPushButton(this);
	btn_browse->setText("Browse...");
	btn_browse->setGeometry(445, 100, 80, 30);

	radBtn_male = new QRadioButton(this);
	radBtn_male->setText("Male");
	radBtn_male->setGeometry(90, 60, 80, 30);

	radBtn_female = new QRadioButton(this);
	radBtn_female->setText("Female");
	radBtn_female->setGeometry(180, 60, 80, 30);

	btnGrp_sex = new QButtonGroup(this);
	btnGrp_sex->addButton(radBtn_male);
	btnGrp_sex->addButton(radBtn_female);
}

void NewPatientDialog::makeConnection()
{
	connect(btn_ok, SIGNAL(clicked()), this, SLOT(doNewPatient()));
	connect(btn_cancel, SIGNAL(clicked()), this, SLOT(close()));
	connect(btn_browse, SIGNAL(clicked()), this, SLOT(browseLocation()));
	
}

void NewPatientDialog::browseLocation()
{
	QString filename = QFileDialog::getExistingDirectory(this);
	lEdit_location->setText(filename);
}

void NewPatientDialog::check()
{

}

void NewPatientDialog::doNewPatient()
{
	std::string regex = "[a-zA-Z0-9\\s_-]+";
	
	std::string name = lEdit_name->text().toStdString();
	name = StringHelper::trim(name);

	int sex = btnGrp_sex->checkedId();

	std::string location = lEdit_location->text().toStdString();

	std::string errorMessage = "Errors list";

	// validate name
	if (name.size() == 0)
		errorMessage += "\n- Name can't be blank!";
	else if (!StringHelper::matchRegex(name, regex))
		errorMessage += "\n- Name is invalid!";

	// validate sex
	if (sex == -1)
		errorMessage += "\n- Sex can't be blank!";

	// validate location
	if (location.size() == 0)
		errorMessage += "\n- Location can't be blank!";


	if (errorMessage.size() > 11)
	{
		DialogHelper::popDialog(errorMessage);
	}
	else
	{
		Message message;
		message["name"] = name;
		message["sex"] = std::to_string(sex);
		message["location"] = location;

		mainWindow->executeAction(new NewPatientAction(message));
		this->close();
		
	}

}
