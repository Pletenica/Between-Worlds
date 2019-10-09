#ifndef __j1Objects_H__
#define __j1Objects_H__

#include "j1Module.h"
#include "j1Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Mix_Chunk;
struct Collider;


class j1Objects : public j1Module
{
public:
	j1Objects();
	~j1Objects();

	bool Start();
	bool Awake();
	bool PreUpdate();
	bool Update();
	bool PostUpdate();
	bool CleanUp();
	void OnCollision(Collider*, Collider*);

public:
	SDL_Texture* objects_graphics = nullptr;

	Mix_Chunk *walksound;
	Mix_Chunk *jumpsound;
	Animation fire_ring_portal;
	Animation plant_portal;
	Animation fire_portal;
	Animation watter_portal;
	Animation ice_portal;
	Animation normal_portal;
	SDL_Rect rectobjects;
	iPoint position;
	Collider* liana01;
	Collider* liana02;
	Collider* plantportal;
	Collider* fireportal;
	Collider* iceportal;
	Collider* normalportal;
	Collider* watterportal;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
};

#endif