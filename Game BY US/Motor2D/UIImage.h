#ifndef __UIIMAGE_H__
#define __UIIMAGE_H__

#include "j1Module.h"
#include "j1GuiElement.h"

class ImageUI :public j1GuiElement
{
public:
	ImageUI(bool ismenu, GuiType type, j1GuiElement* p, SDL_Rect r, SDL_Rect sprite, bool d);

	// Destructor
	virtual ~ImageUI() {}

	// Called after all Updates
	bool PostUpdate();

private:
	bool boolmenu;
};

#endif // __UIIMAGE_H__