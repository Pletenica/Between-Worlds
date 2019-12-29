#ifndef __j1Transitions_H__
#define __j1Transitions_H__

#include "j1Module.h"
#include "j1Animation.h"

class j1Transitions : public j1Module
{
public:

	j1Transitions();
	~j1Transitions();

	bool Start();
	bool PostUpdate();
	void ChangeScenesSphere(j1Module*module1, j1Module*module2);
	void ChangeScenesSphere4(j1Module*module1, j1Module*module2, j1Module*module3, j1Module*module4);

public:
	bool tochange = false;

private:
	SDL_Texture* graphics = nullptr;
	bool isintransition = false;
	bool isfadingout = false;
	Animation fadein;
	Animation current_anim;
	Animation fadeout;

	j1Module* module1;
	j1Module* module2;
	j1Module* module3;
	j1Module* module4;
};

#endif // __j1Transitions_H__