#ifndef NEWFOLDERACTION_H
#define NEWFOLDERACTION_H

#include "Action.h"

class NewFolderAction : public Action
{
public:
	NewFolderAction( Message msg );
	~NewFolderAction();

	void execute(MainWindow* window);

private:
	Message message;
};

#endif // NEWFOLDERACTION_H
