#ifndef __UICONSOLE_H__
#define __UICONSOLE_H__

#include "j1Module.h"
#include "j1GuiElement.h"
#include "UiInputText.h"
#include "UIText.h"
#include "UIWindow.h"

class ConsoleUI :public j1GuiElement
{
public:
	ConsoleUI(bool ismenu, GuiType type, j1GuiElement* p, SDL_Rect r, SDL_Rect sprite, p2SString str, bool d);

	// Destructor
	virtual ~ConsoleUI() {}

	// Called after all Updates
	bool PostUpdate();

private:
	bool boolconsole;

public:
	p2List<TextUI*> console_list_text;
	WindowUI* console_window;
	InputTextUI* input_text;
};

#endif // __UIWINDOW_H__