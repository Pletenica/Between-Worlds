#ifndef __UIINPUTTEXT_H__
#define __UIINPUTTEXT_H__

#include "j1Module.h"
#include "j1GuiElement.h"

class InputTextUI :public j1GuiElement
{
public:
	InputTextUI(bool ismenu, GuiType type, j1GuiElement* p, SDL_Rect r, p2SString str, bool d);

	// Destructor
	virtual ~InputTextUI() {}

	// Called after all Updates
	bool PostUpdate();

public:
	p2SString stri;

private:
	bool boolmenu;
};

#endif // __UIINPUTTEXT_H__