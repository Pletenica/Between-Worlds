#ifndef __j1GUIMANAGER_H__
#define __j1GUIMANAGER_H__

#include "j1Module.h"
#include "j1GuiElement.h"

#define CURSOR_WIDTH 2

struct SDL_Texture;
struct SDL_Rect;
class p2SString;
class UIElement;

class j1GuiManager : public j1Module
{
public:

	j1GuiManager();
	virtual ~j1GuiManager();


	bool Awake(pugi::xml_node&);
	bool Start();
	bool PreUpdate();
	bool PostUpdate();
	bool CleanUp();

	const SDL_Texture* GetAtlas() const;
	j1GuiElement* CreateUIElement(bool ismenu, GuiType type, j1GuiElement* p, SDL_Rect r, SDL_Rect sprite = { 0,0,0,0 }, p2SString str = "", SDL_Rect sprite2 = { 0,0,0,0 }, SDL_Rect sprite3 = { 0,0,0,0 });
	bool DeleteUIElement(j1GuiElement*);

private:
	p2List<j1GuiElement*> gui_element_list;
	SDL_Texture* atlas;
	p2SString atlas_file_name;
};

#endif // __j1GUIMANAGER_H__