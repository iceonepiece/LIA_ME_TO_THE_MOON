#include "ImagePanel.h"
#include "MainWindow.h"
#include "ImageView.h"
#include "qdebug.h"

ImagePanel::ImagePanel( MainWindow* window, ImageView* view ):
	mainWindow(window), imageView(view)
{
	QVBoxLayout layout;
	layout.addWidget(&pixLabel);
	this->setLayout(&layout);
}

ImagePanel::~ImagePanel()
{

}

void ImagePanel::setImage(QPixmap pix)
{
	pixLabel.setGeometry(0, 0, pix.width(), pix.height());
	this->setGeometry(0, 0, pix.width(), pix.height());
	pixLabel.setPixmap(pix);
}

void ImagePanel::mouseDoubleClickEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		
		if (typeid(*imageView->mode_current) == typeid(EditableMode))
		{
			mainWindow->executeAction(new ClickImageAction(imageView, event->x(), event->y()));
		}

	}
}
