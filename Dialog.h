#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

class MainWindow;

class Dialog : public QDialog
{
	Q_OBJECT

public:
	Dialog( MainWindow* window );
	virtual ~Dialog();

protected:
	virtual void makeUi() = 0;
	virtual void makeConnection() = 0;

	MainWindow* mainWindow;
	
};

#endif // DIALOG_H
