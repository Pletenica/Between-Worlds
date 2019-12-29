#ifndef __COINS_H__
#define __COINS_H__

#include "j1Module.h"
#include "j1Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Mix_Chunk;
struct Collider;

class Coins : public j1Entity
{
public:
	Coins();
	virtual ~Coins();

	bool PostUpdate();

	void OnCollision(Collider*, Collider*);

public:
	bool doinit = false;
	bool isincoltoplayer = false;
	Animation idle;
	bool have_to_destroy = false;
	unsigned int coinsound;
};

#endif