#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"
#include "j1Animation.h"

struct SDL_Texture;

class j1Scene : public j1Module
{
public:

	j1Scene();

	// Destructor
	virtual ~j1Scene();

	// Called before render is available
	bool Awake(pugi::xml_node& config);

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();


public:
	SDL_Texture* objects_graphics = nullptr;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	Collider* movecamright;
	Collider* movecamleft;
	Collider* camleftlim;
	Collider* camrightlim;
	Collider* cameralimit01;
	Collider* cameralimit02;
	Collider* plantportal;
	Collider* iceportal;
	Collider* normalportal01;
	Collider* normalportal02;
	Collider* finalportal;
	Animation final_portal;
	Animation plant_portal;
	Animation ice_portal;
	Animation normal_portal;
	int cameraxinvert = 0;

	int iceportalx;
	int iceportaly;
	int plantportalx;
	int plantportaly;
	int normal1portalx;
	int normal1portaly;
	int normal2portalx;
	int normal2portaly;
	int finalportalx;
	int finalportaly;
	int camlimitleft;
	int camlimitright;
	int positionplayerinitx;
	int positionplayerinity;
};

#endif // __j1SCENE_H__