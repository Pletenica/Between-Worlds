#ifndef __j1SCENE2_H__
#define __j1SCENE2_H__

#include "j1Module.h"
#include "j1Animation.h"

struct SDL_Texture;

class j1Scene2 : public j1Module
{
public:

	j1Scene2();

	// Destructor
	virtual ~j1Scene2();

	// Called before render is available
	bool Awake(pugi::xml_node& config);

	bool GetConfigVariables(pugi::xml_node&);

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
	Collider* fireportal;
	Collider* watterportal;
	Collider* normalportal01;
	Collider* normalportal02;
	Collider* finalportal;
	Animation final_portal;
	Animation fire_portal;
	Animation watter_portal;
	Animation fire_ring_animation;
	Animation normal_portal;
	int cameraxinvert = 0;

	int fireportalx;
	int fireportaly;
	int watterportalx;
	int watterportaly;
	int normal1portalx;
	int normal1portaly;
	int normal2portalx;
	int normal2portaly;
	int firering1x;
	int firering1y;
	int firering2x;
	int firering2y;
	int firering3x;
	int firering3y;
	int finalportalx;
	int finalportaly;
	int camlimitleft;
	int camlimitright;
	int positionplayerinitx;
	int positionplayerinity;
};

#endif // __j1SCENE2_H__