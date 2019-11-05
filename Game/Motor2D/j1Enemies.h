#ifndef __j1ENEMIES_H__
#define __j1ENEMIES_H__

#include "j1Module.h"
#include "j1Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Mix_Chunk;
struct Collider;

class j1Enemies : public j1Module
{
public:
	j1Enemies();
	virtual ~j1Enemies();

	bool Awake() {};
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

public:
	SDL_Texture* enemies_graphics = nullptr;
	Animation walkanim_enemieliana;

	//Enemy ONE
	Collider* body_enemieliana_one;
	SDL_RendererFlip flip_one = SDL_FLIP_NONE;
	int positionxanemieliana_one = 0;
	int positionyanemieliana_one = 0;
	bool up_one = false;

	//Enemy TWO
	Collider* body_enemieliana_two;
	SDL_RendererFlip flip_two = SDL_FLIP_NONE;
	int positionxanemieliana_two = 0;
	int positionyanemieliana_two = 50;
	bool up_two = true;

	//Enemy THREE
	Collider* body_enemieliana_three;
	SDL_RendererFlip flip_three = SDL_FLIP_NONE;
	int positionxanemieliana_three = 0;
	int positionyanemieliana_three = 150;
	bool up_three = true;

	//Enemy FOUR
	Collider* body_enemieliana_four;
	SDL_RendererFlip flip_four = SDL_FLIP_NONE;
	int positionxanemieliana_four = 0;
	int positionyanemieliana_four = 100;
	bool up_four = false;

};

#endif