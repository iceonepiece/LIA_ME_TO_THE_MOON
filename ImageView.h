#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QScrollArea>
#include <QScrollBar>
#include <QToolButton>
#include <QLabel>
#include <QAction>
#include <QComboBox>
#include <QPushButton>
#include <QStackedWidget>
#include <QTextEdit>
#include "View.h"
#include "DataImage.h"
#include "ImagePanel.h"
#include "Mode.h"
#include "OriginalMode.h"
#include "ProcessedMode.h"
#include "EditableMode.h"
#include "FatSliderArea.h"
#include "FibrosisSliderArea.h"
#include "SaveImageAction.h"

class ImageView : public View
{
	Q_OBJECT

public:

	static const int ORIGINAL_MODE = 0;
	static const int PROCESSED_MODE = 1;
	static const int EDITABLE_MODE = 2;

	Mode* mode_current;

	ImageView( MainWindow* window );
	~ImageView();

	void onStart();
	void onStop();
	void changeMode(Mode* mode);

public slots:
	void updateView();

private slots:

	void enterOriginalMode();
	void enterProcessedMode();
	void enterEditableMode();
	void goBack(QAction* action);
	void processImage();
	void saveImage();
	void zoomIn();
	void zoomOut();
	void zoomTo(int n);


private:
	void makeUi();
	void makeConnection();

	void setEditEnabled(bool b);

	std::vector<Mode*> list_mode;

	DataImage* currentImage;
	ImagePanel* panel_image;
	QScrollArea* sArea_image;

	QLabel* lbl_note;
	QTextEdit* txt_note;

	QStackedWidget* area_slider;

	QToolButton* tBtn_menu;
	QAction* act_folder;
	QAction* act_patient;
	QAction* act_home;

	QLabel* lbl_imageIcon;
	QLabel* lbl_imageName;
	QLabel* lbl_arrow;

	// command 
	QPushButton* btn_process;
	QPushButton* btn_save;

	// zoom ui
	QComboBox* com_zoom;
	QPushButton* btn_zoomIn;
	QPushButton* btn_zoomOut;

	// view modes
	QPushButton* btn_oriMode;
	QPushButton* btn_proMode;
	QPushButton* btn_editMode;

	QLabel* lbl_showType;
	QLabel* lbl_proPercentHead;
	QLabel* lbl_proPercentValue;
	QLabel* lbl_editPercentHead;
	QLabel* lbl_editPercentValue;	
};

#endif // IMAGEVIEW_H
