#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Transitions.h"

j1Transitions::j1Transitions() : j1Module()
{
	name.create("Transitions");

	/////FADE OUT ANIMATION//////
	fadein.PushBack({ 1200, 960, 400, 320 });
	fadein.PushBack({ 800, 960, 400, 320 });
	fadein.PushBack({ 400, 960, 400, 320 });
	fadein.PushBack({ 0, 960, 400, 320 });
	fadein.PushBack({ 1200, 640, 400, 320 });
	fadein.PushBack({ 800, 640, 400, 320 });
	fadein.PushBack({ 400, 640, 400, 320 });
	fadein.PushBack({ 0, 640, 400, 320 });
	fadein.PushBack({ 1200, 320, 400, 320 });
	fadein.PushBack({ 800, 320, 400, 320 });
	fadein.PushBack({ 400, 320, 400, 320 });
	fadein.PushBack({ 0, 320, 400, 320 });
	fadein.PushBack({ 1200, 0, 400, 320 });
	fadein.PushBack({ 800, 0, 400, 320 });
	fadein.PushBack({ 400, 0, 400, 320 });
	fadein.PushBack({ 0, 0, 400, 320 });
	fadein.speed = 0.8f;

	/////FADE OUT ANIMATION//////
	fadeout.PushBack({ 0, 0, 400, 320 });
	fadeout.PushBack({ 400, 0, 400, 320 });
	fadeout.PushBack({ 800, 0, 400, 320 });
	fadeout.PushBack({ 1200, 0, 400, 320 });
	fadeout.PushBack({ 0, 320, 400, 320 });
	fadeout.PushBack({ 400, 320, 400, 320 });
	fadeout.PushBack({ 800, 320, 400, 320 });
	fadeout.PushBack({ 1200, 320, 400, 320 });
	fadeout.PushBack({ 0, 640, 400, 320 });
	fadeout.PushBack({ 400, 640, 400, 320 });
	fadeout.PushBack({ 800, 640, 400, 320 });
	fadeout.PushBack({ 1200, 640, 400, 320 });
	fadeout.PushBack({ 0, 960, 400, 320 });
	fadeout.PushBack({ 400, 960, 400, 320 });
	fadeout.PushBack({ 800, 960, 400, 320 });
	fadeout.PushBack({ 1200, 960, 400, 320 });
	fadeout.speed = 0.8f;
}

bool j1Transitions::Start()
{
	graphics = App->tex->Load("textures/UI/Transition.png");
	return true;
}

// Destructor
j1Transitions::~j1Transitions()
{}

bool j1Transitions::PostUpdate()
{
	if (isintransition == true) {
		App->render->Blit(graphics, 0, 0, &(current_anim.GetCurrentFrame()), 1.0f, 0, 0, 0, SDL_FLIP_NONE);

		ChangeScenesSphere4(module1, module2, module3, module4);
	}
	return true;
}

void j1Transitions::ChangeScenesSphere(j1Module*module1, j1Module*module2)
{
	if (isintransition == false) {
		this->module1 = module1;
		this->module2 = module2;
		current_anim = fadein;
	}
	isintransition = true;

	if (current_anim.finished == 1 && isfadingout==false) {
		module1->active = false;
		module2->active = true;
		current_anim.Reset();
		current_anim = fadeout;
		isfadingout = true;
	}

	if (fadeout.finished == 1 || current_anim.finished==1) {
		current_anim.finished = 0;
		fadeout.finished = 0;
		fadein.finished = 0;
		isfadingout = false;
		isintransition = false;
	}
}

void j1Transitions::ChangeScenesSphere4(j1Module*module1, j1Module*module2, j1Module* module3, j1Module*module4)
{
	if (isintransition == false) {
		this->module1 = module1;
		this->module2 = module2;
		this->module3 = module3;
		this->module4 = module4;
		current_anim = fadein;
	}
	isintransition = true;

	if (current_anim.finished == 1 && isfadingout == false) {
		module1->active = false;
		module2->active = true;
		module3->active = true;
		module4->active = true;
		current_anim.Reset();
		current_anim = fadeout;
		isfadingout = true;
	}

	if (fadeout.finished == 1 || current_anim.finished == 1) {
		current_anim.finished = 0;
		fadeout.finished = 0;
		fadein.finished = 0;
		isfadingout = false;
		isintransition = false;
	}
}