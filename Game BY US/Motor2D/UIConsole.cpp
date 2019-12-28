#include "UIConsole.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1GuiManager.h"
#include "j1GuiElement.h"
#include "j1Menu.h"

ConsoleUI::ConsoleUI(bool ismenu, GuiType type, j1GuiElement* p, SDL_Rect r, SDL_Rect sprite, p2SString str, bool d) :j1GuiElement(type, r, p, d) {

}

bool ConsoleUI::PostUpdate() {

	return true;
}