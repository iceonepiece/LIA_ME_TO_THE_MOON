#ifndef NEWPATIENTDIALOG_H
#define NEWPATIENTDIALOG_H

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QButtonGroup>
#include <QRadioButton>
#include <QMessageBox>
#include <QFileDialog>
#include "Dialog.h"
#include "NewPatientAction.h"
#include "StringHelper.h"
#include "DialogHelper.h"

class NewPatientDialog : public Dialog
{
	Q_OBJECT

public:
	NewPatientDialog( MainWindow* window );
	~NewPatientDialog();

private slots:
	void doNewPatient();
	void browseLocation();
	void check();

private:
	void makeUi();
	void makeConnection();

	QLabel* lbl_name;
	QLabel* lbl_sex;
	QLabel* lbl_location;
	
	QLineEdit* lEdit_name;
	QLineEdit* lEdit_location;

	QPushButton* btn_ok;
	QPushButton* btn_cancel;
	QPushButton* btn_browse;
	
	QButtonGroup* btnGrp_sex;
	QRadioButton* radBtn_male;
	QRadioButton* radBtn_female;

};

#endif // NEWPATIENTDIALOG_H
