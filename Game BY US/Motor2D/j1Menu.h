#ifndef __j1MENU_H__
#define __j1MENU_H__

#include "j1Module.h"
#include "j1Animation.h"
#include "j1GuiManager.h"


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

	SDL_Texture* menu_normal_back_graphics = nullptr;
	SDL_Texture* menu_fire_back_graphics = nullptr;
	SDL_Texture* menu_watter_back_graphics = nullptr;
	SDL_Texture* menu_ice_back_graphics = nullptr;
	SDL_Texture* menu_plant_back_graphics = nullptr;
	SDL_Texture* menu_current_back_graphics = nullptr;
	SDL_Rect menubackgroundrect;
	SDL_Texture* menu_graphics = nullptr;
	Animation logo_anim;
	Animation idle_player;

public:
	SDL_Rect textdonerect;
	j1GuiElement* guielement_textdone;

	SDL_Rect startbuttonrect;
	SDL_Rect startbuttonrect1;
	SDL_Rect startbuttonrect2;
	SDL_Rect startbuttonrect3;
	j1GuiElement* guielement_startbutton;

	SDL_Rect continuebuttonrect;
	SDL_Rect continuebuttonrect1;
	SDL_Rect continuebuttonrect2;
	SDL_Rect continuebuttonrect3;
	j1GuiElement* guielement_continuebutton;

	SDL_Rect settingsbuttonrect;
	SDL_Rect settingsbuttonrect1;
	SDL_Rect settingsbuttonrect2;
	SDL_Rect settingsbuttonrect3;
	j1GuiElement* guielement_settingsbutton;

	SDL_Rect exitbuttonrect;
	SDL_Rect exitbuttonrect1;
	SDL_Rect exitbuttonrect2;
	SDL_Rect exitbuttonrect3;
	j1GuiElement* guielement_exitbutton;

	SDL_Rect creditsbuttonrect;
	SDL_Rect creditsbuttonrect1;
	SDL_Rect creditsbuttonrect2;
	SDL_Rect creditsbuttonrect3;
	j1GuiElement* guielement_creditsbutton;

	SDL_Rect githubbuttonrect;
	SDL_Rect githubbuttonrect1;
	SDL_Rect githubbuttonrect2;
	SDL_Rect githubbuttonrect3;
	j1GuiElement* guielement_githubbutton;

	bool issettingsmenuopen = false;
	bool iscreditsmenuopen = false;
};

#endif // __j1MENU_H__