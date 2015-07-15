#ifndef HOMEVIEW_H
#define HOMEVIEW_H

#include <QPushButton>
#include <QTableWidget>
#include <QLineEdit>
#include "View.h"
#include "NewPatientAction.h"
#include "NewPatientDialog.h"
#include "OpenPatientDialog.h"
#include "DeleteModelAction.h"

class HomeView : public View
{
	Q_OBJECT

public:
	HomeView( MainWindow* window );
	~HomeView();
	
	void onStart();
	void onStop();

public slots:
	void updateView();

private slots:
	void showNewPatientDialog();
	void showOpenPatientDialog();
	void deletePatient();
	void enterPatient(int row, int col);
	void search(QString keyword);

private:

	void makeUi();
	void makeConnection();

	std::vector<Model*> list_patient;

	QLabel* lbl_title;

	QPushButton* btn_newPatient;
	QPushButton* btn_openPatient;
	QPushButton* btn_delPatient;

	QLineEdit* lEdit_search;
	QTableWidget* tab_patients;


	
};

#endif // HOMEVIEW_H
