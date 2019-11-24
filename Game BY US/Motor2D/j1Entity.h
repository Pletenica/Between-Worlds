#ifndef _j1ENTITY_H
#define _j1ENTITY_H
#include "SDL/include/SDL.h"
#include "j1Animation.h"
#include "j1EntityManager.h"

struct SDL_Texture;
struct Collider;



class j1Entity : public j1EntityManager
{
public:

	j1Entity(EntityType type) {};
	virtual ~j1Entity() {};

	virtual bool Awake(pugi::xml_node&);
	virtual bool Start();
	virtual bool PreUpdate();
	virtual bool Update(float dt);
	virtual bool PostUpdate();
	virtual bool CleanUp();
	virtual void OnCollision(Collider* c1, Collider* c2) {};

public:

	Collider* body = nullptr;

	Animation idle;
	Animation walk;
	Animation liana;
	Animation dead;
	Animation jump;
	fPoint position;
	Animation* current_animation = nullptr;
	EntityType type = EntityType::UNKNOWN;
	SDL_Texture* texture = nullptr;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
};
#endif // !_j1ENTITY_H