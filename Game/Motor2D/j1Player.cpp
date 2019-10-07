
#include "j1App.h"
#include "j1Textures.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Audio.h"
#include "j1Collision.h"
#include "j1Player.h"
#include "j1Scene.h"
#include "SDL/include/SDL_timer.h"



j1Player::j1Player()
{

	/////IDLE ANIMATION//////
	idle.PushBack({ 0, 0, 32, 32 });
	idle.PushBack({ 32, 0, 32, 32 });
	idle.PushBack({ 64, 0, 32, 32 });
	idle.speed = 0.2f;

	/////JUMP ANIMATION//////
	jump.PushBack({ 0, 32, 32, 32 });
	jump.PushBack({ 32, 32, 32, 32 });
	jump.PushBack({ 64, 32, 32, 32 });
	jump.speed = 0.2f;

	/////WALK ANIMATION//////
	walk.PushBack({ 0, 64, 32, 32 });
	walk.PushBack({ 32, 64, 32, 32 });
	walk.PushBack({ 64, 64, 32, 32 });
	walk.PushBack({ 96, 64, 32, 32 });
	walk.speed = 0.2f;

	/////LIANA ANIMATION//////
	liana.PushBack({ 0, 96, 32, 32 });
	liana.PushBack({ 32, 96, 32, 32 });
	liana.PushBack({ 64, 96, 32, 32 });
	liana.speed = 0.2f;

}

j1Player::~j1Player()
{}

// Load assets
bool j1Player::Start()
{
	//// Load All CONDITIONS //// 
	dimensionnormal = true;
	dimensionagua = false;
	dimensionfuego = false;
	dimensionhielo = false;
	dimensionplanta = false;
	bool left = false;
	bool right = true;
	bool jump = false;
	jump_timer = 0;
	//flip = false;
	position.x = 0;
	position.y = 0;
	Current_Animation =idle;

	//// Load All Graphics //// 
	normal_graphics = App->tex->Load("textures/PlayerNormal.png");
	fire_graphics = App->tex->Load("textures/PlayerFire.png");
	plant_graphics = App->tex->Load("textures/PlayerPlant.png");
	ice_graphics = App->tex->Load("textures/PlayerSnow.png");
	watter_graphics = App->tex->Load("textures/PlayerWatter.png");
	current_graphics = normal_graphics;

	//// Load All SOUNDS & COLLISIONS //// 
	//walksound = App->audio->LoadChunk("Audio_FX/Punch.wav");
	body = App->collision->AddCollider({ position.x,(position.y - 100),35,20 }, COLLIDER_PLAYER, this);

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

	if (!isinair) {
		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
			position.y += 1;

		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
			position.y -= 1;

		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) {
			position.x -= 1;
			Current_Animation = walk;
		}

		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) {
			position.x += 1;
			Current_Animation = walk;
		}
	}

	if (isinair) {
		Current_Animation = jump;
	}

	return true;
}


// Update: draw background
bool j1Player::Update()
{

	return true;
}

bool j1Player::PostUpdate() {
	App->render->Blit(current_graphics, position.x, position.y, &(Current_Animation.GetCurrentFrame()), 1.0f);
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
			position.x += 15;
		}
		if (other->type == COLLIDER_PORTAL_FUEGO) {
			dimensionnormal = false;
			dimensionagua = false;
			dimensionfuego = true;
			dimensionhielo = false;
			dimensionplanta = false;
			current_graphics = fire_graphics;
			position.x += 15;
		}
		if (other->type == COLLIDER_PORTAL_HIELO) {
			dimensionnormal = false;
			dimensionagua = false;
			dimensionfuego = false;
			dimensionhielo = true;
			dimensionplanta = false;
			current_graphics = ice_graphics;
			position.x += 15;
						
		}
		if (other->type == COLLIDER_PORTAL_PLANTA) {
			dimensionnormal = false;
			dimensionagua = false;
			dimensionfuego = false;
			dimensionhielo = false;
			dimensionplanta = true;
			current_graphics = plant_graphics;
			position.x += 15;
		}
		if (other->type != COLLIDER_SUELO) {
			isinair = true;
		}
	}
}