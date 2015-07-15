#include "DialogHelper.h"

DialogHelper::DialogHelper()
{

}

DialogHelper::~DialogHelper()
{

}

void DialogHelper::popDialog(std::string text)
{
	QMessageBox msgBox;
	msgBox.setText(text.c_str());
	msgBox.exec();
}

bool DialogHelper::popQuestionDialog( std::string title, std::string question )
{
	QMessageBox msgBox(QMessageBox::Information, title.c_str(), question.c_str(), QMessageBox::Yes | QMessageBox::No);

	return QMessageBox::Yes == msgBox.exec();
}
