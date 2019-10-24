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

	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;

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
	Collider* fireportal;
	Collider* watterportal;
	Collider* normalportal01;
	Collider* normalportal02;
	Collider* normalportal03;
	Collider* normalportal04;
	Collider* finalportal;
	Collider* endportal;
	Collider* firering11;
	Collider* firering12;
	Collider* firering21;
	Collider* firering22;
	Collider* firering31;
	Collider* firering32;
	Collider* firering41;
	Collider* firering42;
	Collider* firering51;
	Collider* firering52;
	Collider* firering61;
	Collider* firering62;
	Animation final_portal;
	Animation plant_portal;
	Animation ice_portal;
	Animation fire_portal;
	Animation watter_portal;
	Animation fire_ring_anim;
	Animation watter_wave_anim;
	Animation normal_portal;
	int cameraxinvert = 0;
	bool donecollidersscene1 = false;
	bool donecollidersscene2 = false;
	bool changelevel = false;

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
	int fireportalx;
	int fireportaly;
	int watterportalx;
	int watterportaly;
	int normal3portalx;
	int normal3portaly;
	int normal4portalx;
	int normal4portaly;
	int endportalx;
	int endportaly;
	int firering1x;
	int firering1y;
	int firering2x;
	int firering2y;
	int firering3x;
	int firering3y;
	int firering4x;
	int firering4y;
	int firering5x;
	int firering5y;
	int firering6x;
	int firering6y;

	int camlimitleft;
	int camlimitright;
	int positionplayerinitx;
	int positionplayerinity;
};

#endif // __j1SCENE_H__