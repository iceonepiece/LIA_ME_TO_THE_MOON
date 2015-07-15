#ifndef UPLOADIMAGEDIALOG_H
#define UPLOADIMAGEDIALOG_H

#include <QPushButton>
#include <QTableWidget>
#include <QFileDialog>
#include <QPixmap>
#include <QHeaderView>
#include "Dialog.h"
#include "UploadImageAction.h"

class UploadImageDialog : public Dialog
{
	Q_OBJECT

public:
	UploadImageDialog( MainWindow* window );
	~UploadImageDialog();

private slots:
	void browseImage();
	void deleteImage();
	void uploadImage();

private:
	void makeUi();
	void makeConnection();

	void updateDialog();


	QStringList list_imagePath;

	QPushButton* btn_browse;
	QPushButton* btn_delete;
	QPushButton* btn_upload;
	QPushButton* btn_cancel;

	QTableWidget* tab_image;




};

#endif // UPLOADIMAGEDIALOG_H
