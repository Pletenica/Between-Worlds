#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "j1Module.h"
#include "j1Animation.h"
#include "p2Point.h"
#include "j1Entity.h"

struct SDL_Texture;
struct Mix_Chunk;
struct Collider;

class Enemy : public j1Entity
{
public:
	Enemy();
	virtual ~Enemy();

	bool Awake(pugi::xml_node&config);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();
	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;
	void OnCollision(Collider*, Collider*);

public:
	SDL_Texture* current_graphics = nullptr;
	Animation Current_Animation;
	Animation idle;
	Animation walk;
	SDL_Rect rectenemy;

	float positionxinit;
	float positionyinit;
	Collider* body;
	Collider* todeathcol;
	Collider* colchecktoplayer;
};

#endif