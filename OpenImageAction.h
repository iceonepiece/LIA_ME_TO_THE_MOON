#ifndef OPENIMAGEACTION_H
#define OPENIMAGEACTION_H

#include <string>
#include "Action.h"
#include "FileHelper.h"
#include "DialogHelper.h"
#include "Folder.h"

class OpenImageAction : public Action
{
public:
	OpenImageAction( Folder* folder, std::string path );
	~OpenImageAction();
	void execute(MainWindow* window);

private:
	Folder* folder;
	std::string path;
	
};

#endif // OPENIMAGEACTION_H
