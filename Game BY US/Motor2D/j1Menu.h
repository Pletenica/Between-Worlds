#ifndef __j1MENU_H__
#define __j1MENU_H__

#include "j1Module.h"
#include "j1Animation.h"

struct SDL_Texture;
struct Collider;

class j1Menu : public j1Module
{
public:
	j1Menu();
	virtual ~j1Menu();

	bool Awake(pugi::xml_node& config);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;

public:
	bool isinmenu = true;

	SDL_Texture* menu_graphics = nullptr;
	Animation logo_anim;

};

#endif // __j1MENU_H__