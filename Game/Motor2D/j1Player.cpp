#include "j1App.h"
#include "j1Textures.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Audio.h"
#include "j1Collision.h"
#include "j1Player.h"
#include "j1Scene.h"
#include "j1Objects.h"
#include "SDL/include/SDL_timer.h"



j1Player::j1Player()
{

	/////IDLE ANIMATION//////
	idle.PushBack({ 0, 0, 32, 32 });
	idle.PushBack({ 32, 0, 32, 32 });
	idle.PushBack({ 64, 0, 32, 32 });
	idle.speed = 0.005f;

	/////JUMP ANIMATION//////
	//jump.PushBack({ 0, 32, 32, 32 });
	//jump.PushBack({ 32, 32, 32, 32 });
	jump.PushBack({ 64, 32, 32, 32 });
	jump.speed = 0.007f;

	/////WALK ANIMATION//////
	walk.PushBack({ 0, 64, 32, 32 });
	walk.PushBack({ 32, 64, 32, 32 });
	walk.PushBack({ 64, 64, 32, 32 });
	walk.PushBack({ 96, 64, 32, 32 });
	walk.speed = 0.01f;

	/////LIANA ANIMATION//////
	liana.PushBack({ 0, 96, 32, 32 });
	liana.PushBack({ 32, 96, 32, 32 });
	liana.PushBack({ 64, 96, 32, 32 });
	liana.speed = 0.007f;

}

j1Player::~j1Player()
{}

bool dimensionnormal = true;
bool dimensionagua = false;
bool dimensionfuego = false;
bool dimensionhielo = false;
bool dimensionplanta = false;

// Load assets
bool j1Player::Start()
{
	//// Load All CONDITIONS //// 
	bool left = false;
	bool right = true;
	bool jump = false;
	//flip = false;
	position.x = 0;
	position.y = 50;
	Current_Animation =idle;

	//// Load All Graphics //// 
	normal_graphics = App->tex->Load("textures/PlayerNormal.png");
	fire_graphics = App->tex->Load("textures/PlayerFire.png");
	plant_graphics = App->tex->Load("textures/PlayerPlant.png");
	ice_graphics = App->tex->Load("textures/PlayerSnow.png");
	watter_graphics = App->tex->Load("textures/PlayerWatter.png");
	current_graphics = plant_graphics;

	//// Load All SOUNDS & COLLISIONS //// 
	//walksound = App->audio->LoadChunk("Audio_FX/Punch.wav");
	body = App->collision->AddCollider({ position.x+2,position.y,25,32 }, COLLIDER_PLAYER, this);
	//suelo01 = App->collision->AddCollider({ 0,200,200,32 }, COLLIDER_SUELO, this);
	//plantportal = App->collision->AddCollider({ 60,50,50,100 }, COLLIDER_PORTAL_PLANTA, this);
	//liana01 = App->collision->AddCollider({ 0,0,10,10 }, COLLIDER_LIANA, this);
	return true;
}

//Clean Up
bool j1Player::CleanUp() {
	App->tex->UnLoad(current_graphics);
	App->tex->UnLoad(fire_graphics);
	App->tex->UnLoad(plant_graphics);
	App->tex->UnLoad(ice_graphics);
	App->tex->UnLoad(watter_graphics);
	App->tex->UnLoad(normal_graphics);
	//App->audio->StopChunk();
	//App->audio->UnLoadChunk(punchsound);
	return true;
}


bool j1Player::PreUpdate() {

	//// INPUTS ////

	Current_Animation.GetCurrentFrame() = idle.GetCurrentFrame();

	if (!isinair && !isinliana) {
		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
			isjumping = true;

		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) {
			position.x -= 1;
			Current_Animation.GetCurrentFrame() = walk.GetCurrentFrame();
			flip = SDL_FLIP_HORIZONTAL;
		}

		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) {
			position.x += 1;
			//plantportal->rect.x -= 0.01;
			Current_Animation.GetCurrentFrame() = walk.GetCurrentFrame();
			flip = SDL_FLIP_NONE;
		}
	}

	/*
	if (isinair) {
		if (isinliana==false && dimensionagua == false) {
			Current_Animation.GetCurrentFrame() = jump.GetCurrentFrame();


			G = G + 0.0007;


			//position.y += velocity_y;

			if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT) {
				position.y += 10;
			}

			if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) {
				position.x -= 10;
				left = true;
			}

			if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) {
				position.x += 1;
				left = false;
			}
		}
		if (isinliana) {
			Current_Animation = liana;
			//position.y--;
			if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT) {
				position.y += 1;
			}

			if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT) {
				position.y -= 1;
			}

			if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) {
				position.x -= 1;
				left = true;
			}

			if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) {
				position.x += 1;
				left = false;
			}
		}
		if (dimensionagua == true) {
			position.y--;
			if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT) {
				position.y += 2;
			}

			if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) {
				position.x -= 1;
				left = true;
				Current_Animation = walk;
			}

			if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) {
				position.x += 1;
				Current_Animation = walk;
				left = false;
			}
		}
	}
	*/

	//////// LIANA ////////
	if (isinliana == true) {
		isinair = false;
		Current_Animation.GetCurrentFrame() = liana.GetCurrentFrame();
		if (limitator == 0) {
			position.y++;
		}
		limitator++;
		if (limitator == 20) {
			limitator = 0;
		}
		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN) {
			position.y -= 20;
		}

		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) {
			position.x -= 1;
			flip = SDL_FLIP_HORIZONTAL;
		}

		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) {
			position.x += 1;
			flip = SDL_FLIP_NONE;
		}
	}

	if (body->CheckCollision(App->objects->liana01->rect) == false && body->CheckCollision(App->objects->liana02->rect) == false) {
		isinliana = false;
	}

	//////// INPUT FAILS ////////
	if ((App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) && (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)) {
		Current_Animation.GetCurrentFrame() = idle.GetCurrentFrame();
	}



	//////// GOD MODE ////////

	if (App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN) {
		if (body->to_delete != false) {
			body = App->collision->AddCollider({ position.x + 2,position.y,25,32 }, COLLIDER_PLAYER, this);
			godmode = false;
		}
		else {
			body->to_delete=true;
			godmode == true;
		}
	}

	if (godmode == true) {
		//isinair = true;
		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) {
			position.y -= 0.5;
		}

		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
			position.y += 0.5;
		}

		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) {
			position.x -= 0.5;
			Current_Animation.GetCurrentFrame() = walk.GetCurrentFrame();
			flip = SDL_FLIP_HORIZONTAL;
		}

		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) {
			position.x += 0.5;
			Current_Animation.GetCurrentFrame() = walk.GetCurrentFrame();
			flip = SDL_FLIP_NONE;
		}
	}

	if (flip == SDL_FLIP_HORIZONTAL) {
		body->rect.x = App->player->position.x +5;
		body->rect.y = position.y;
	}
	if (flip == SDL_FLIP_NONE) {
		body->rect.x = App->player->position.x;
		body->rect.y = position.y;
	}
	return true;
}


// Update: draw background
bool j1Player::Update()
{
	/*
	if (flip == SDL_FLIP_HORIZONTAL) {
		if (dimensionhielo == true) {
			body->rect.x = position.x + 10;
		}
	}
	else {
		if (dimensionhielo == true) {
			body->rect.x = position.x;
			body->rect.w = 10;
		}
	}
	*/



	return true;
}

bool j1Player::PostUpdate() {
	
	App->render->Blit(current_graphics, position.x, position.y, &(Current_Animation.GetCurrentFrame()), 1.0f, 0, 0, 0, flip);
	
	return true;
}


void j1Player::OnCollision(Collider* player, Collider* other) {
	if (player->type == COLLIDER_PLAYER) {
		if (other->type == COLLIDER_PORTAL_AGUA) {
			dimensionnormal = false;
			dimensionagua = true;
			dimensionfuego = false;
			dimensionhielo = false;
			dimensionplanta = false;
			current_graphics = watter_graphics;
		}
		if (other->type == COLLIDER_PORTAL_FUEGO) {
			dimensionnormal = false;
			dimensionagua = false;
			dimensionfuego = true;
			dimensionhielo = false;
			dimensionplanta = false;
			current_graphics = fire_graphics;
		}
		if (other->type == COLLIDER_PORTAL_HIELO) {
			dimensionnormal = false;
			dimensionagua = false;
			dimensionfuego = false;
			dimensionhielo = true;
			dimensionplanta = false;
			position.x = 100;
			current_graphics = ice_graphics;						
		}
		if (other->type == COLLIDER_PORTAL_PLANTA) {
			dimensionnormal = false;
			dimensionagua = false;
			dimensionfuego = false;
			dimensionhielo = false;
			dimensionplanta = true;
			position.x += 100;
			current_graphics = plant_graphics;
		}
		if (other->type == COLLIDER_LIANA) {
			isinliana = true;
		}
	}
}