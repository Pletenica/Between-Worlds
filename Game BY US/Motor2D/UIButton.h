#ifndef __UIBUTTON_H__
#define __UIBUTTON_H__

#include "j1Module.h"
#include "j1GuiElement.h"

class ButtonUI :public j1GuiElement
{
public:

	ButtonUI(bool ismenu, GuiType type, j1GuiElement* p, SDL_Rect r, SDL_Rect sprite, SDL_Rect spriten2, SDL_Rect spriten3, bool d);
	virtual ~ButtonUI() {}


	bool Awake(pugi::xml_node&) { return true; };
	bool Start() { return true; };
	bool PreUpdate();
	bool PostUpdate();
	bool CleanUp() { return true; };

public:
	SDL_Rect sprite2;
	SDL_Rect sprite3;


private:
	bool boolmenu;
};

#endif //__UIBUTTON_H__