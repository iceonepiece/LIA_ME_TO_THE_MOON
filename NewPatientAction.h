#ifndef NEWPATIENTACTION_H
#define NEWPATIENTACTION_H

#include "DialogHelper.h"
#include "FileHelper.h"
#include "Action.h"
#include "Patient.h"

class NewPatientAction : public Action
{
public:
	NewPatientAction( Message msg );
	~NewPatientAction();

	void execute(MainWindow* window);

private:
	Message message;
};

#endif // NEWPATIENTACTION_H
