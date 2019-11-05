#include "j1App.h"
#include "j1Textures.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Audio.h"
#include "j1Collision.h"
#include "j1Player.h"
#include "j1Scene.h"
#include "j1Map.h"
#include "j1Enemies.h"
#include "SDL/include/SDL_timer.h"

j1Enemies::j1Enemies()
{
	/////IDLE ANIMATION//////
	walkanim_enemieliana.PushBack({ 0, 0, 24, 19 });
	walkanim_enemieliana.speed = 0.07f;
}

j1Enemies::~j1Enemies()
{}


// Load assets
bool j1Enemies::Start()
{

	//// Load All Graphics //// 
	enemies_graphics = App->tex->Load("textures/Enemies.png");

	positionxanemieliana_one = 997;
	body_enemieliana_one = App->collision->AddCollider({ positionxanemieliana_one,positionyanemieliana_one,24,19 }, COLLIDER_DEATH_ENEMY, this);

	positionxanemieliana_two = 868;
	body_enemieliana_two = App->collision->AddCollider({ positionxanemieliana_two,positionyanemieliana_two,24,19 }, COLLIDER_DEATH_ENEMY, this);

	positionxanemieliana_three = 772;
	body_enemieliana_three = App->collision->AddCollider({ positionxanemieliana_three,positionyanemieliana_three,24,19 }, COLLIDER_DEATH_ENEMY, this);

	positionxanemieliana_four = 1220;
	body_enemieliana_four = App->collision->AddCollider({ positionxanemieliana_four,positionyanemieliana_four,24,19 }, COLLIDER_DEATH_ENEMY, this);

	return true;
}

//Clean Up
bool j1Enemies::CleanUp() {
	App->audio->StopFx();
	App->tex->UnLoad(enemies_graphics);
	return true;
}


bool j1Enemies::PreUpdate() {

	return true;
}


// Update: draw background
bool j1Enemies::Update(float dt)
{

	return true;
}

bool j1Enemies::PostUpdate() {
	if (App->player->deadbool == false) {
		////MOVEMENT ENEMY ONE/////
		if (up_one == false) {
			positionyanemieliana_one++;
			body_enemieliana_one->rect.y++;
			flip_one = SDL_FLIP_VERTICAL;
			if (positionyanemieliana_one == 210) {
				up_one = true;
			}
		}
		else if (up_one == true) {
			positionyanemieliana_one--;
			body_enemieliana_one->rect.y--;
			flip_one = SDL_FLIP_NONE;
			if (positionyanemieliana_one == 0) {
				up_one = false;
			}
		}

		////MOVEMENT ENEMY TWO/////
		if (up_two == false) {
			positionyanemieliana_two++;
			body_enemieliana_two->rect.y++;
			flip_two = SDL_FLIP_VERTICAL;
			if (positionyanemieliana_two == 210) {
				up_two = true;
			}
		}
		else if (up_two == true) {
			positionyanemieliana_two--;
			body_enemieliana_two->rect.y--;
			flip_two = SDL_FLIP_NONE;
			if (positionyanemieliana_two == 20) {
				up_two = false;
			}
		}

		////MOVEMENT ENEMY THREE/////
		if (up_three == false) {
			positionyanemieliana_three++;
			body_enemieliana_three->rect.y++;
			flip_three = SDL_FLIP_VERTICAL;
			if (positionyanemieliana_three == 120) {
				up_three = true;
			}
		}
		else if (up_three == true) {
			positionyanemieliana_three--;
			body_enemieliana_three->rect.y--;
			flip_three = SDL_FLIP_NONE;
			if (positionyanemieliana_three == 0) {
				up_three = false;
			}
		}

		////MOVEMENT ENEMY FOUR/////
		if (up_four == false) {
			positionyanemieliana_four++;
			body_enemieliana_four->rect.y++;
			flip_four = SDL_FLIP_VERTICAL;
			if (positionyanemieliana_four == 210) {
				up_four = true;
			}
		}
		else if (up_four == true) {
			positionyanemieliana_four--;
			body_enemieliana_four->rect.y--;
			flip_four = SDL_FLIP_NONE;
			if (positionyanemieliana_four == 0) {
				up_four = false;
			}
		}
	}




	App->render->Blit(enemies_graphics, positionxanemieliana_one, positionyanemieliana_one, &(walkanim_enemieliana.GetCurrentFrame()), 1.0f, 0, 0, 0, flip_one);
	App->render->Blit(enemies_graphics, positionxanemieliana_two, positionyanemieliana_two, &(walkanim_enemieliana.GetCurrentFrame()), 1.0f, 0, 0, 0, flip_two);
	App->render->Blit(enemies_graphics, positionxanemieliana_three, positionyanemieliana_three, &(walkanim_enemieliana.GetCurrentFrame()), 1.0f, 0, 0, 0, flip_three);
	App->render->Blit(enemies_graphics, positionxanemieliana_four, positionyanemieliana_four, &(walkanim_enemieliana.GetCurrentFrame()), 1.0f, 0, 0, 0, flip_four);
	return true;
}
