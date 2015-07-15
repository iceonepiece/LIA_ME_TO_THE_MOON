#include "NewFolderDialog.h"
#include "MainWindow.h"
#include "qdebug.h"

NewFolderDialog::NewFolderDialog( MainWindow* window ):
	Dialog(window)
{
	qDebug() << "Address in NewFolderDialog() =" << window;
	qDebug() << "Address in NewFolderDialog() =" << mainWindow;
	this->makeUi();
	this->makeConnection();
}

NewFolderDialog::~NewFolderDialog()
{

}

void NewFolderDialog::makeUi()
{
	this->resize(450, 155);
	this->setWindowTitle("New Folder");

	lEdit_name = new QLineEdit(this);
	lEdit_name->setGeometry(80, 20, 355, 30);

	lbl_name = new QLabel(this);
	lbl_name->setText("Name:");
	lbl_name->setGeometry(20, 20, 80, 30);

	lbl_type = new QLabel(this);
	lbl_type->setText("Type:");
	lbl_type->setGeometry(20, 60, 40, 30);

	btn_ok = new QPushButton(this);
	btn_ok->setText("OK");
	btn_ok->setGeometry(265, 110, 80, 30);

	btn_cancel = new QPushButton(this);
	btn_cancel->setText("Cancel");
	btn_cancel->setGeometry(355, 110, 80, 30);

	radBtn_fat = new QRadioButton(this);
	radBtn_fat->setText("Fat");
	radBtn_fat->setGeometry(90, 60, 80, 30);

	radBtn_fib = new QRadioButton(this);
	radBtn_fib->setText("Fibrosis");
	radBtn_fib->setGeometry(180, 60, 80, 30);

	btnGrp_type = new QButtonGroup(this);
	btnGrp_type->addButton(radBtn_fat);
	btnGrp_type->addButton(radBtn_fib);
}

void NewFolderDialog::makeConnection()
{
	connect(btn_ok, SIGNAL(clicked()), this, SLOT(doNewFolder()));
	connect(btn_cancel, SIGNAL(clicked()), this, SLOT(close()));
}

void NewFolderDialog::doNewFolder()
{
	std::string regex = "[a-zA-Z0-9\\s_-]+";

	std::string name = lEdit_name->text().toStdString();
	name = StringHelper::trim(name);

	int type = btnGrp_type->checkedId();

	std::string errorMessage = "Errors list";

	// validate name
	if (name.size() == 0)
		errorMessage += "\n- Name can't be blank!";
	else if (!StringHelper::matchRegex(name, regex))
		errorMessage += "\n- Name is invalid!";

	// validate sex
	if (type == -1)
		errorMessage += "\n- Type can't be blank!";

	if (errorMessage.size() > 11)
	{
		DialogHelper::popDialog(errorMessage);
	}
	else
	{
		Message message;
		message["name"] = name;
		message["type"] = std::to_string(type);

		mainWindow->executeAction(new NewFolderAction(message));
		this->close();
	}

}
