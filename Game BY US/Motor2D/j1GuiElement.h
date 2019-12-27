#ifndef __j1GUIELEMENT_H__
#define __j1GUIELEMENT_H__

#include "j1Module.h"
#include "p2Point.h"
#include "../Motor2D/SDL/include/SDL.h"
#include "j1App.h"
#include "j1Input.h"

#define CURSOR_WIDTH 2

struct SDL_Texture;
struct SDL_Rect;
class p2SString;
class UIElement;

enum class GuiType
{
	NONE,
	BUTTON,
	IMAGE,
	WINDOW,
	TEXT,
	UNKNOWN
};

class j1GuiElement :public j1Module
{
public:
	j1GuiElement(GuiType type, SDL_Rect r, j1GuiElement* p, bool d);

	// Destructor
	virtual ~j1GuiElement() {}

	// Called when before render is available
	virtual bool Awake(pugi::xml_node&) { return true; }

	// Call before first frame
	virtual bool Start() { return true; }

	// Called before all Updates
	virtual bool PreUpdate();

	// Called after all Updates
	virtual bool PostUpdate() { return true; }

	// Called before quitting
	virtual bool CleanUp() { return true; }

	bool Move();

	SDL_Rect GetScreenRect();
	SDL_Rect GetLocalRect();
	iPoint GetScreenPos();
	iPoint GetLocalPos();
	void SetLocalPos(iPoint pos);
	bool CheckMouse();
	SDL_Rect Check_Printable_Rect(SDL_Rect sprite, iPoint& dif_sprite);

public:
	SDL_Rect sprite1;
	bool pushed;
	bool over;
private:
	SDL_Rect screen_rect;
	SDL_Rect local_rect;
	SDL_Rect mask_rect;
	j1GuiElement* parent;
	bool drageable;
};

#endif // J1GUIELEMENT