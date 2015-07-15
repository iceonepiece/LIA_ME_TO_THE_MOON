#ifndef FOLDERVIEW_H
#define FOLDERVIEW_H

#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QToolButton>
#include <QAction>
#include "View.h"
#include "Folder.h"
#include "UploadImageDialog.h"
#include "ImageHelper.h"
#include "DeleteModelAction.h"

class FolderView : public View
{
	Q_OBJECT 

public:
	FolderView( MainWindow* window );
	~FolderView();

	void onStart();
	void onStop();

public slots:
	void updateView();

private slots:
	void enterImage(int row, int col);
	void goBack(QAction* action);
	void goHome(bool f);
	void showUploadImageDialog();
	void deleteImage();

private:

	void makeUi();
	void makeConnection();

	Folder* currentFolder;
	std::vector<Model*> list_image;

	QToolButton* tBtn_menu;
	QAction* act_patient;
	QAction* act_home;

	QLabel* lbl_folderIcon;
	QLabel* lbl_folderName;
	QLabel* lbl_arrow;

	QPushButton* btn_uploadImage;
	QPushButton* btn_delImage;

	QTableWidget* tab_images;
	QLineEdit* lEdit_search;

};

#endif // FOLDERVIEW_H
