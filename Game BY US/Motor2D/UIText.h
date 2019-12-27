#ifndef __UITEXT_H__
#define __UITEXT_H__

#include "j1Module.h"
#include "j1GuiElement.h"

class TextUI :public j1GuiElement
{
public:
	TextUI(bool ismenu, GuiType type, j1GuiElement* p, SDL_Rect r, p2SString str, bool d);

	// Destructor
	virtual ~TextUI() {}

	// Called after all Updates
	bool PostUpdate();
	void RefreshText(p2SString stringt);

public:
	p2SString stri;

private:
	bool boolmenu;
};

#endif // __UITEXT_H__