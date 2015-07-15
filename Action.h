#ifndef ACTION_H
#define ACTION_H

#include "Message.h"

class MainWindow;

class Action
{
public:
	Action();
	virtual ~Action();

	virtual void execute(MainWindow* window) = 0;
};

#endif // ACTION_H
