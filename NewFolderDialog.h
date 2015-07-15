#ifndef NEWFOLDERDIALOG_H
#define NEWFOLDERDIALOG_H

#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QButtonGroup>
#include "Dialog.h"
#include "StringHelper.h"
#include "DialogHelper.h"
#include "NewFolderAction.h"


class NewFolderDialog : public Dialog
{
	Q_OBJECT

public:
	NewFolderDialog( MainWindow* window );
	~NewFolderDialog();

private slots:
	void doNewFolder();

private:
	void makeUi();
	void makeConnection();

	QLineEdit* lEdit_name;
	QLabel* lbl_name;
	QLabel* lbl_type;

	QPushButton* btn_ok;
	QPushButton* btn_cancel;

	QRadioButton* radBtn_fat;
	QRadioButton* radBtn_fib;

	QButtonGroup* btnGrp_type;
	
};

#endif // NEWFOLDERDIALOG_H
