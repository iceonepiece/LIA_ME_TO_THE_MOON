#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vector>
#include <string>
#include <QWidget>
#include <QStackedWidget>
#include <QEvent>
#include "Patient.h"
#include "Folder.h"
#include "DataImage.h"
#include "Action.h"
#include "HomeView.h"
#include "PatientView.h"
#include "FolderView.h"
#include "ImageView.h"

class MainWindow : public QWidget
{
	Q_OBJECT

public:

	// views
	static const int HOME_VIEW = 0;
	static const int PATIENT_VIEW = 1;
	static const int FOLDER_VIEW = 2;
	static const int IMAGE_VIEW = 3;

	// models
	static const int PATIENT_MODEL = 1;
	static const int FOLDER_MODEL = 2;
	static const int DATA_IMAGE_MODEL = 3;

	MainWindow();
	~MainWindow();

	void executeAction(Action* action);
	void changeView(int view);

	void addPatient(Patient* patient);
	void addFolder(Folder* folder);
	void addImage(DataImage* image);

	void setPatientList(std::vector<Model*> list_patient);
	void setCurrentPatient(Patient* patient);
	void setCurrentFolder(Folder* folder);
	void setCurrentImage(DataImage* image);

	Patient* getCurrentPatient();
	Folder* getCurrentFolder();
	DataImage* getCurrentImage();
	
	bool isNameAvailable(std::vector<Model*> list_model, std::string name);
	bool isNameAvailable( int type, std::string name);

	std::vector<Model*> getModelList(int type);
	std::vector<Model*> getModelListByKey( int type, std::string key );

	Processor* getProcessor( int type );
	
private:

	std::vector<Processor*> list_processor;

	QStackedWidget* stack_view;
	std::vector<Model*> list_patient;
	Patient* currentPatient;
	Folder* currentFolder;
	DataImage* currentImage;
};

#endif // MAINWINDOW_H
