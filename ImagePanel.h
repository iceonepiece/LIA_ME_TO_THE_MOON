#ifndef IMAGEPANEL_H
#define IMAGEPANEL_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QMouseEvent>
#include "ClickImageAction.h"

class ImageView;
class MainWindow;

class ImagePanel : public QWidget
{
	Q_OBJECT

public:
	ImagePanel( MainWindow* window, ImageView* imageView );
	~ImagePanel();

	int x;
	int y;

	void setImage(QPixmap pix);

private:
	QLabel pixLabel;
	MainWindow* mainWindow;
	ImageView* imageView;
	void mouseDoubleClickEvent(QMouseEvent* Event);

	
};

#endif // IMAGEPANEL_H
