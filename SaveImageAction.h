#ifndef SAVEIMAGEACTION_H
#define SAVEIMAGEACTION_H

#include "Action.h"
#include "DataImage.h"
#include "DialogHelper.h"
#include "FileHelper.h"

class SaveImageAction : public Action
{
public:
	SaveImageAction( DataImage* image );
	~SaveImageAction();

	void execute(MainWindow* window);

private:
	DataImage* image;

	
};

#endif // SAVEIMAGEACTION_H
