#ifndef DELETEMODELACTION_H
#define DELETEMODELACTION_H

#include "Action.h"
#include "Model.h"
#include "FileHelper.h"
#include "DialogHelper.h"

class DeleteModelAction : public Action
{
public:
	DeleteModelAction( Model* model );
	~DeleteModelAction();

	void execute(MainWindow* window);

private:
	Model* model;
	
};

#endif // DELETEMODELACTION_H
