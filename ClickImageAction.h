#ifndef CLICKIMAGEACTION_H
#define CLICKIMAGEACTION_H

#include "Action.h"

class ImageView;

class ClickImageAction : public Action
{
public:
	ClickImageAction( ImageView* view, int x, int y );
	~ClickImageAction();

	void execute(MainWindow* window);

private:
	int x;
	int y;
	ImageView* imageView;

};

#endif // CLICKIMAGEACTION_H
