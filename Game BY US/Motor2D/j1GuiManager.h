#ifndef __j1GUIMANAGER_H__
#define __j1GUIMANAGER_H__

#include "j1Module.h"

#define CURSOR_WIDTH 2

struct SDL_Texture;
struct SDL_Rect;
class p2SString;
class UIElement;

enum Color
{
	RED,
	GREEN,
	BLUE,
	YELLOW,
	GREY,
	BLACK,
	WHITE,

	COLOR_NOT_DEF
};

enum UI_Type
{
	LABEL,
	BUTTON,
	IMAGE,
	SLIDER,
	CHECK_BOX,

	UI_NOT_DEF
};


class j1GuiManager : public j1Module
{
public:

	j1GuiManager();

	// Destructor
	virtual ~j1GuiManager();

	// Called when before render is available
	bool Awake(pugi::xml_node&);

	// Call before first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// TODO 2: Create the factory methods
	// Gui creation functions

	const SDL_Texture* GetAtlas() const;

private:

	SDL_Texture* atlas;
	p2SString atlas_file_name;
};

#endif // __j1GUIMANAGER_H__