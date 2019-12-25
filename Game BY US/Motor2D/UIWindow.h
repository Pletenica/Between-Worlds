#ifndef __UIWINDOW_H__
#define __UIWINDOW_H__

#include "j1Module.h"
#include "j1GuiElement.h"

class WindowUI :public j1GuiElement
{
public:
	WindowUI(bool ismenu, GuiType type, j1GuiElement* p, SDL_Rect r, SDL_Rect sprite, bool d);

	// Destructor
	virtual ~WindowUI() {}

	// Called after all Updates
	bool PostUpdate();

private:
	bool boolmenu;
};

#endif // __UIWINDOW_H__