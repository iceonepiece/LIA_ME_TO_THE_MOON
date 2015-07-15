#ifndef PROCESSIMAGEACTION_H
#define PROCESSIMAGEACTION_H

#include "Action.h"
#include "DataImage.h"
#include "DataOption.h"
#include "Processor.h"
#include "FatProcessor.h"
#include "FibrosisProcessor.h"

class ProcessImageAction : public Action
{
public:
	ProcessImageAction( DataImage* image, bool option = false );
	~ProcessImageAction();

	void execute(MainWindow* window);

private:
	DataImage* image;
	bool option;
	
};

#endif // PROCESSIMAGEACTION_H
