#ifndef _j1ENTITY_H
#define _j1ENTITY_H

#include "j1Module.h"
#include "SDL/include/SDL.h"
#include "j1Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

enum class EntityType
{
	NONE,
	PLAYER,
	ENEMY_LIANA,
	ENEMY_FIRE,
	ENEMY_WATTER,
	ENEMY_ICE,
	UNKNOWN
};


class j1Entity : public j1Module
{
public:

	j1Entity(EntityType type);
	virtual ~j1Entity() {};

	virtual bool Awake(pugi::xml_node&);
	virtual bool Start();
	virtual bool PreUpdate();
	virtual bool Update(float dt);
	virtual bool PostUpdate();
	virtual bool CleanUp();
	virtual void OnCollision(Collider* c1, Collider* c2) {};
	virtual bool Load(pugi::xml_node& data){return true;};
	virtual bool Save(pugi::xml_node& data)const{return true;};

public:

	Collider* body = nullptr;

	Animation idle;
	Animation walk;
	Animation liana;
	Animation dead;
	Animation jump;
	fPoint position;
	Animation* current_animation = nullptr;
	EntityType type;
	SDL_Texture* texture = nullptr;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
};
#endif // !_j1ENTITY_H