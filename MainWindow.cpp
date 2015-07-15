#include "MainWindow.h"
#include "qdebug.h"

MainWindow::MainWindow()
{
	stack_view = new QStackedWidget(this);
	stack_view->setGeometry(0, 0, 1200, 680);

	stack_view->addWidget( new HomeView(this) );
	stack_view->addWidget( new PatientView(this) );
	stack_view->addWidget( new FolderView(this) );
	stack_view->addWidget( new ImageView(this) );

	list_processor.push_back(new FatProcessor());
	list_processor.push_back(new FibrosisProcessor());

	resize(1220, 680);
}

MainWindow::~MainWindow()
{
	for (Model* patient : list_patient)
	{
		delete patient;
	}
	list_patient.resize(0);

	for (Processor* processor : list_processor)
	{
		delete processor;
	}
	list_processor.resize(0);
}

void MainWindow::executeAction(Action* action)
{
	action->execute(this);
	delete action;
}

void MainWindow::changeView(int view)
{
	((View*)stack_view->currentWidget())->onStop();
	stack_view->setCurrentIndex(view);
	((View*)stack_view->currentWidget())->onStart();
}

Processor* MainWindow::getProcessor(int type)
{
	if (type == -2)
		return list_processor[0];
	else if (type == -3)
		return list_processor[1];

	return nullptr;
}

void MainWindow::addPatient(Patient* patient)
{
	list_patient.push_back(patient);
	((View*)stack_view->currentWidget())->updateView();
}

void MainWindow::addFolder(Folder* folder)
{
	currentPatient->list_folder.push_back(folder);
	FileHelper::writeXML(currentPatient);
	((View*)stack_view->currentWidget())->updateView();
}

void MainWindow::addImage(DataImage* image)
{
	currentFolder->list_dataImage.push_back(image);
	FileHelper::writeXML(currentFolder);
	((View*)stack_view->currentWidget())->updateView();
}

void MainWindow::setPatientList( std::vector<Model*> list )
{
	list_patient = list;
}

void MainWindow::setCurrentPatient(Patient* patient)
{
	currentPatient = patient;
}

void MainWindow::setCurrentFolder(Folder* folder)
{
	currentFolder = folder;
}

void MainWindow::setCurrentImage(DataImage* image)
{
	currentImage = image;
}

Patient* MainWindow::getCurrentPatient()
{
	return currentPatient;
}

Folder* MainWindow::getCurrentFolder()
{
	return currentFolder;
}

DataImage* MainWindow::getCurrentImage()
{
	qDebug() << currentImage->name.c_str();
	return currentImage;
}

bool MainWindow::isNameAvailable( std::vector<Model*> list_model, std::string name)
{
	for (Model* model : list_model)
	{
		if (model->name == name)
			return false;
	}

	return true;
}

bool MainWindow::isNameAvailable( int type , std::string name )
{
	std::vector<Model*> list_model = this->getModelList(type);

	for (Model* model : list_model)
	{
		if (model->name == name)
			return false;
	}

	return true;
}

std::vector<Model*> MainWindow::getModelList( int type )
{
	if (type == PATIENT_MODEL)
		return list_patient;

	else if (type == FOLDER_MODEL)
		return currentPatient->list_folder;

	else if (type == DATA_IMAGE_MODEL)
		return currentFolder->list_dataImage;

	return std::vector<Model*>();
}

std::vector<Model*> MainWindow::getModelListByKey( int type, std::string key )
{
	std::vector<Model*> list_model = this->getModelList(type);

	if (key.size() == 0)
		return list_model;

	std::vector<Model*> re_list_model;
	std::string useKeyword = StringHelper::toLower(key);

	for (Model* model : list_model)
	{
		if (StringHelper::toLower(model->name).find(useKeyword) != std::string::npos)
			re_list_model.push_back(model);
	}

	return re_list_model;
}
