#ifndef OPENPATIENTACTION_H
#define OPENPATIENTACTION_H

#include "Action.h"
#include "DialogHelper.h"
#include "FileHelper.h"
#include "OpenFolderAction.h"

class OpenPatientAction : public Action
{
public:
	OpenPatientAction(Message msg);
	~OpenPatientAction();

	void execute(MainWindow* window);

private:
	Message message;
};

#endif // OPENPATIENTACTION_H

