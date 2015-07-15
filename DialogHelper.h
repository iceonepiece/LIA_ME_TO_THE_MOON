#ifndef DIALOGHELPER_H
#define DIALOGHELPER_H

#include <string>
#include <QMessageBox>

class DialogHelper
{
public:
	DialogHelper();
	~DialogHelper();

	static void popDialog(std::string text);
	static bool popQuestionDialog(std::string title, std::string question );

};

#endif // DIALOGHELPER_H
