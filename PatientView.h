#ifndef PATIENTVIEW_H
#define PATIENTVIEW_H

#include <QPushButton>
#include <QTableWidget>
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>
#include "View.h"
#include "Patient.h"
#include "NewFolderDialog.h"
#include "DeleteModelAction.h"

class PatientView : public View
{
	Q_OBJECT

public:
	PatientView( MainWindow* window );
	~PatientView();

	void onStart();
	void onStop();

public slots:
	void updateView();

private slots:
	void groupType(int index);
	void enterFolder(int row, int col);
	void deleteFolder();
	void goHome();
	void showNewFolderDialog();
	void search(QString keyword);

private:
	void makeUi();
	void makeConnection();

	Patient* currentPatient;
	std::vector<Model*> list_folder;

	QLabel* lbl_patientIcon;
	QLabel* lbl_patientName;
	QLabel* lbl_arrow;
	QPushButton* btn_home;

	QPushButton* btn_newFolder;
	QPushButton* btn_delFolder;

	QLabel* lbl_type;
	QComboBox* com_type;

	QLineEdit* lEdit_search;
	QTableWidget* tab_folders;
	
};

#endif // PATIENTVIEW_H
