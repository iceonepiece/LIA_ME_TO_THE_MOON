#ifndef UPLOADIMAGEACTION_H
#define UPLOADIMAGEACTION_H

#include <string>
#include <QStringList>
#include "Action.h"
#include "Processor.h"
#include "ProcessImageAction.h"
#include "FatImage.h"
#include "FibrosisImage.h"


class UploadImageAction : public Action
{
public:
	UploadImageAction( std::string path );
	~UploadImageAction();

	void execute(MainWindow* window);

private:
	std::string path;
	
};

#endif // UPLOADIMAGEACTION_H
