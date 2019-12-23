#ifndef __UITEXT_H__
#define __UITEXT_H__

#include "j1Module.h"
#include "j1GuiElement.h"

class TextUI :public j1GuiElement
{
public:
	TextUI(GuiType type, j1GuiElement* p, SDL_Rect r, p2SString str, bool d);

	// Destructor
	virtual ~TextUI() {}

	// Called after all Updates
	bool PostUpdate();

public:
	p2SString stri;
};

#endif // __UITEXT_H__