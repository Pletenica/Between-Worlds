#ifndef _j1ENTITY_H
#define _j1ENTITY_H
#include "SDL/include/SDL.h"
#include "j1Animation.h"
#include "j1EntityManager.h"

struct SDL_Texture;
struct Collider;

#define COLLIDER_MARGIN 20

enum EntityState {
	IDLE,
	JUMP,
	RUN_FORWARD,
	RUN_BACKWARD,
	FALL,
	ATTACK,
	SLIDE_FORWARD,
	SLIDE_BACKWARD,
	CROUCH_UP,
	CROUCH_DOWN,
};

class j1Entity : public j1EntityManager
{
public:

	j1Entity(EntityType type);
	virtual ~j1Entity();

	virtual bool Awake(pugi::xml_node&);
	virtual bool Start();
	virtual bool PreUpdate();
	virtual bool Update(float dt);
	virtual bool PostUpdate();
	virtual bool CleanUp();
	virtual void OnCollision(Collider* c1, Collider* c2) {};

public:

	fPoint position;
	fPoint current_speed;
	int initial_x_position = 0;
	int initial_y_position = 0;
	int health = 0;

	bool grounded = false;
	float gravity = 0.0f;

	Collider* collider = nullptr;
	Collider* raycast = nullptr;
	Collider* last_collider = nullptr;

	uint die_fx = 0;

	p2SString die_fx_path;

	p2List<Animation*> animations;
	Animation idle;
	Animation jump;
	Animation run;
	Animation fall;
	Animation* current_animation = nullptr;

	EntityType type = EntityType::UNKNOWN;
	EntityState state = EntityState::IDLE;
	SDL_Texture* texture = nullptr;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	bool visible = true;
};
#endif // !_j1ENTITY_H