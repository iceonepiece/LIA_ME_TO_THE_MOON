#ifndef OPENPATIENTDIALOG_H
#define OPENPATIENTDIALOG_H

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>
#include "Dialog.h"
#include "OpenPatientAction.h"

class OpenPatientDialog : public Dialog
{
	Q_OBJECT

public:
	OpenPatientDialog( MainWindow* window );
	~OpenPatientDialog();

private slots:
	void doOpenPatient();
	void browseLocation();

private:
	void makeUi();
	void makeConnection();

	QLabel* lbl_location;
	QLineEdit* lEdit_location;

	QPushButton* btn_ok;
	QPushButton* btn_cancel;
	QPushButton* btn_browse;
	
};

#endif // OPENPATIENTDIALOG_H
