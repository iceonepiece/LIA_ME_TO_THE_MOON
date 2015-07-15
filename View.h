#ifndef VIEW_H
#define VIEW_H

#include <QWidget>

class MainWindow;

class View : public QWidget
{
	Q_OBJECT

public:
	View( MainWindow* window );
	virtual ~View();

	View* create();

	virtual void onStart() = 0;
	virtual void onStop() = 0;

public slots:
	virtual void updateView() = 0;

protected:
	virtual void makeUi(){};
	virtual void makeConnection(){};

	static View* instance;
	MainWindow* mainWindow;
	
};

#endif // VIEW_H
