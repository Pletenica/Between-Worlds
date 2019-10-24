#include "j1App.h"
#include "j1Textures.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Audio.h"
#include "j1Collision.h"
#include "j1Player.h"
#include "j1Scene.h"
#include "j1Map.h"
#include "SDL/include/SDL_timer.h"

j1Player::j1Player()
{
	/////IDLE ANIMATION//////
	idle.PushBack({ 0, 0, 32, 32 });
	idle.PushBack({ 32, 0, 32, 32 });
	idle.PushBack({ 64, 0, 32, 32 });
	idle.PushBack({ 32, 0, 32, 32 });
	idle.speed = 0.07f;

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
	walk.speed = 0.07f;

	/////LIANA ANIMATION//////
	liana.PushBack({ 0, 96, 32, 32 });
	liana.PushBack({ 32, 96, 32, 32 });
	liana.PushBack({ 64, 96, 32, 32 });
	liana.speed = 0.007f;

	/////DEAD ANIMATION//////
	dead.PushBack({ 96, 96, 32, 32 });
	dead.PushBack({ 96, 32, 32, 32 });
	dead.PushBack({ 96, 0, 32, 32 });
	dead.PushBack({ 96, 0, 32, 32 });
	dead.PushBack({ 96, 0, 32, 32 });
	dead.PushBack({ 96, 0, 32, 32 });
	dead.PushBack({ 96, 0, 32, 32 });
	dead.speed = 0.1f;
}

j1Player::~j1Player()
{}

bool j1Player::Awake(pugi::xml_node& config)
{
	/////// SCENE 1 PORTALS ///////
	Ginit = config.child("gravity").attribute("Ginit").as_int(2);
	jump_vel = config.child("gravity").attribute("JumpVel").as_int(17);
	G_max = config.child("gravity").attribute("Gmax").as_int(25);
	speed_player = config.child("speed").attribute("movement").as_int(2);
	speed_player_ice = config.child("speed").attribute("iceinercy").as_int(1);
	speed_player_jump = config.child("speed").attribute("movementinair").as_int(2);


	return true;
}

// Load assets
bool j1Player::Start()
{
	//// Load All CONDITIONS //// 
	Current_Animation =idle;

	//// Load All Graphics //// 
	normal_graphics = App->tex->Load("textures/PlayerNormal.png");
	fire_graphics = App->tex->Load("textures/PlayerFire.png");
	plant_graphics = App->tex->Load("textures/PlayerPlant.png");
	ice_graphics = App->tex->Load("textures/PlayerSnow.png");
	watter_graphics = App->tex->Load("textures/PlayerWatter.png");
	current_graphics = normal_graphics;

	//// Load All SOUNDS & COLLISIONS //// 
	jumpingsound = App->audio->LoadFx("audio/fx/jump.wav");
	deathsound = App->audio->LoadFx("audio/fx/hello_man.wav");
	//walkingsound = App->audio->LoadChunk("audio/fx/walk.wav");
	//portalsound = App->audio->LoadChunk("audio/fx/portal.wav");
	body = App->collision->AddCollider({ position.x,position.y,20,32 }, COLLIDER_PLAYER, this);
	
	return true;
}

//Clean Up
bool j1Player::CleanUp() {
	App->audio->StopFx();
	//App->audio->UnLoadChunk(jumpingsound);
	//App->audio->UnLoadChunk(deathsound);
	//App->audio->UnLoadChunk(walkingsound);
	//App->audio->UnLoadChunk(portalsound);
	App->tex->UnLoad(current_graphics);
	App->tex->UnLoad(fire_graphics);
	App->tex->UnLoad(plant_graphics);
	App->tex->UnLoad(ice_graphics);
	App->tex->UnLoad(watter_graphics);
	App->tex->UnLoad(normal_graphics);

	return true;
}


bool j1Player::PreUpdate() {
	right = false;
	left = false;

	if (deadbool == false && isinair == false && isjumping == false) {
		Current_Animation.GetCurrentFrame() = idle.GetCurrentFrame();
	}
	if (stop_left == true) {
		ice_left = false;
	}
	if (stop_right == true) {
		ice_right = false;
	}

	//////// FLIP ////////
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
		flip = SDL_FLIP_HORIZONTAL;
	}

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
		flip = SDL_FLIP_NONE;
	}


	//////// GOD MODE ////////
	if (App->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN) {
		if (App->player->godmode == true) {
			//body = App->collision->AddCollider({ position.x,position.y,20,32 }, COLLIDER_PLAYER, this);
			godmode = false;
		}
		else {
			isinair = false;
			App->player->godmode = true;

		}
	}
	if (godmode == true) {
		isinair = false;
		isjumping = false;
		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
			if (position.y < 288) {
				position.y += speed_player;
			}
		}

		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) {
			if (position.y > 0) {
				position.y -= speed_player;
			}
		}

		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && !stop_left) {
			position.x -= speed_player;
			flip = SDL_FLIP_HORIZONTAL;
		}

		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && !stop_right) {
			position.x += speed_player;
			flip = SDL_FLIP_NONE;
		}
	}


	//////// INPUTS WHEN TOUCHES GROUND ////////
	if (isinair ==false && !isinliana && !godmode && !dimensionagua) {
		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT && !stop_jump) {
			isjumping = true; 
			App->audio->PlayFx(jumpingsound, 0);
		}


		if ((App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)&&!stop_left) {
			position.x -= speed_player;
			
			if (dimensionhielo == true) {
				ice_left = true;
				ice_right = false;
			}
			left = true;
			Current_Animation.GetCurrentFrame() = walk.GetCurrentFrame();
		}

		if ((App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)&&!stop_right) {
			position.x += speed_player;
			//App->audio->PlayChunk(walkingsound);
			if (dimensionhielo == true) {
				ice_right = true;
				ice_left = false;
			}
			right = true;
			Current_Animation.GetCurrentFrame() = walk.GetCurrentFrame();
		}
	}

	//////// WATTER ////////
	if (dimensionagua == true) {
		isjumping = false;
		Current_Animation.GetCurrentFrame() = idle.GetCurrentFrame();
		if (isinair) {
			if (limit_watter == 0) {
				position.y++;
			}
			limit_watter++;
			if (limit_watter == 3) {
				limit_watter = 0;
			}
		}
		if ((App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) && !stop_left) {
			position.x -= speed_player;
			left = true;
			Current_Animation.GetCurrentFrame() = walk.GetCurrentFrame();
		}

		if ((App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) && !stop_right) {
			position.x += speed_player;
			right = true;
			Current_Animation.GetCurrentFrame() = walk.GetCurrentFrame();
		}

		if ((App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN)&& (position.y > 20)) {
			position.y -= speed_player * 15;
		}
		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN) {
			position.y += speed_player * 15;
		}

		isinair = false;
	}

	//////// LIANA ////////
	if (isinliana == true) {
		isjumping = false;
		Current_Animation.GetCurrentFrame() = liana.GetCurrentFrame();
		if (isinair == false) {
			if (limit_liana == 0) {
				position.y++;
			}
			limit_liana++;
			if (limit_liana == 3) {
				limit_liana = 0;
			}
		}
		
		if ((App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) && (stop_left == false)) {
			position.x -= speed_player;
			flip = SDL_FLIP_HORIZONTAL;
		}

		if ((App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) && (stop_right == false)) {
			position.x += speed_player;
			flip = SDL_FLIP_NONE;
		}

		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN) {
			position.y -= 10;
		}
		isinair = false;
	}


	//////// JUMPING ////////
	if (isjumping == true) {
		Current_Animation.GetCurrentFrame() = jump.GetCurrentFrame();
		isinair = false;
		ice_left = false;
		ice_right = false;
		if (G < G_max) {
			G++;
		}
		position.y += G - jump_vel;

		if ((App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) && !stop_left) {
			position.x -= speed_player_jump;
		}

		if ((App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) && !stop_right) {
			position.x += speed_player_jump;
		}
	}


	//////// AIR ////////
	if (isinair==true && isinliana==false) {
		isjumping = false;
		ice_left = false;
		ice_right = false;
		Current_Animation.GetCurrentFrame() = jump.GetCurrentFrame();
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && !stop_left) {
			position.x -= speed_player;
			Current_Animation.GetCurrentFrame() = walk.GetCurrentFrame();
			flip = SDL_FLIP_HORIZONTAL;
		}

		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && !stop_right) {
			position.x += speed_player;
			Current_Animation.GetCurrentFrame() = walk.GetCurrentFrame();
			flip = SDL_FLIP_NONE;
		}
		if (G < G_max) {
			G++;
		}
		position.y += G;
	}


	//////// INPUT FAILS ////////
	if ((App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) && (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)) {
		Current_Animation.GetCurrentFrame() = idle.GetCurrentFrame();
	}



	//////// DEATH ////////
	if (deadbool == true) {
		//App->audio->PlayFx(deathsound, 0);
		Current_Animation.GetCurrentFrame() = dead.GetCurrentFrame();
		stop_left = true;
		stop_jump = true;
		stop_right = true;

		if (dead.finished == 1) {
			if (App->scene->changelevel == false) {
				ChangeToLevel1();
			}
			else {
				ChangeToLevel2();
			}
		}
	}


	//////// CHANGE PLAYER COLLIDER IF FLIP ////////
	if (flip == SDL_FLIP_HORIZONTAL) {
		body->rect.x = App->player->position.x +7;
		body->rect.y = position.y;
	}
	if (flip == SDL_FLIP_NONE) {
		body->rect.x = App->player->position.x +5;
		body->rect.y = position.y;
	}

	return true;
}


// Update: draw background
bool j1Player::Update(float dt)
{

	if (dimensionfuego == true) {
		current_graphics = fire_graphics;
	}
	if (dimensionplanta == true) {
		current_graphics = plant_graphics;
	}
	if (dimensionagua == true) {
		current_graphics = watter_graphics;
	}
	if (dimensionhielo == true) {
		current_graphics = ice_graphics;
	}
	if (dimensionnormal == true) {
		current_graphics = normal_graphics;
	}
	return true;
}

bool j1Player::PostUpdate() {

	isinair = true;
	isinliana = false;
	stop_right = false;
	stop_left = false;
	stop_jump = false;

	if (body->CheckCollision(App->scene->cameralimit01->rect) == true) {
		stop_left = true;
	}
	if (body->CheckCollision(App->scene->cameralimit02->rect) == true) {
		stop_right = true;
	}
	App->render->Blit(current_graphics, position.x, position.y, &(Current_Animation.GetCurrentFrame()), 1.0f, 0, 0, 0, flip);
	
	return exitgame;
}


void j1Player::OnCollision(Collider* player, Collider* other) {
	if (player->type == COLLIDER_PLAYER) {
		if (other->type == COLLIDER_CORRIENTE_AGUA) {
			if (limit_wave_watter == 0) {
				position.x--;
			}
			limit_wave_watter++;
			if (limit_wave_watter == 3) {
				limit_wave_watter = 0;
			}
		}
		if (other->type == COLLIDER_PORTAL_AGUA) {
			ice_right = false;
			ice_left = false;
			dimensionnormal = false;
			dimensionagua = true;
			dimensionfuego = false;
			dimensionhielo = false;
			dimensionplanta = false;

			current_graphics = watter_graphics;
			
			if (position.x > other->rect.x - 32) {
				stop_left = true;
				stop_jump = true;
			}
		}
		if (other->type == COLLIDER_PORTAL_FUEGO) {
			ice_right = false;
			ice_left = false;
			dimensionnormal = false;
			dimensionagua = false;
			dimensionfuego = true;
			dimensionhielo = false;
			dimensionplanta = false;
			dimensionplanta = false;

			current_graphics = fire_graphics;
			
			if (position.x > other->rect.x - 32) {
				stop_left = true;
				stop_jump = true;
			}
		}
		if (other->type == COLLIDER_PORTAL_HIELO) {
			ice_right = false;
			ice_left = false;
			dimensionnormal = false;
			dimensionagua = false;
			dimensionfuego = false;
			dimensionhielo = true;
			dimensionplanta = false;
			current_graphics = ice_graphics;	
			
			if (position.x > other->rect.x - 32) {
				stop_left = true;
				stop_jump = true;
			}
		}
		if (other->type == COLLIDER_PORTAL_PLANTA) {
			ice_right = false;
			ice_left = false;
			dimensionnormal = false;
			dimensionagua = false;
			dimensionfuego = false;
			dimensionhielo = false;
			dimensionplanta = true;
			current_graphics = plant_graphics;
			
			if (position.x > other->rect.x-32) {
				stop_left = true;
				stop_jump = true;
			}
		}
		if (other->type == COLLIDER_PORTAL_NORMAL1) {
			ice_right = false;
			ice_left = false;
			dimensionnormal = true;
			dimensionagua = false;
			dimensionfuego = false;
			dimensionhielo = false;
			dimensionplanta = false;

			current_graphics = normal_graphics;

			if (position.x > other->rect.x - 32) {
				stop_left = true;
				stop_jump = true;
			}
		}
		if (other->type == COLLIDER_PORTAL_NORMAL2) {
			ice_right = false;
			ice_left = false;
			dimensionnormal = true;
			dimensionagua = false;
			dimensionfuego = false;
			dimensionhielo = false;
			dimensionplanta = false;

			current_graphics = normal_graphics;

			if (position.x > other->rect.x - 32) {
				stop_left = true;
				stop_jump = true;
			}
		}
		if (other->type == COLLIDER_PORTAL_CHANGESCENE1) {
			App->player->ChangeToLevel2();
		}

		if (other->type == COLLIDER_SUELO) {
			isinliana = false;
			isinair = false;
			isinice = false;
			isjumping = false;
			if (godmode == false) {
				if (position.y >= other->rect.y) {
					isinair = true;
					if (position.x < other->rect.x) {
						stop_right = true;
					}
					if (position.x > other->rect.x) {
						stop_left = true;
					}
				}
				if (position.y < other->rect.y) {
					position.y = other->rect.y - 32;
				}
				G = Ginit;
				if (((other->rect.y <= position.y) && position.x < other->rect.x) && (SDL_SCANCODE_D)) {
					stop_right = true;
					Current_Animation.GetCurrentFrame() = idle.GetCurrentFrame();
				}
				if (((other->rect.y <= position.y) && position.x > other->rect.x) && (SDL_SCANCODE_A)) {
					stop_left = true;
					Current_Animation.GetCurrentFrame() = idle.GetCurrentFrame();
				}
				if (dimensionhielo == true) {
					if (limit_ice == 0) {
						if (ice_left == true) {
							position.x -= speed_player_ice;
						}
						if (ice_right == true) {
							position.x += speed_player_ice;
						}
					}
					limit_ice++;
					if (limit_ice >= 2) {
						limit_ice = 0;
					}
				}
			}
		}

		if (other->type == COLLIDER_LIANA) {
			if (godmode == false) {
				isinliana = true;
				isinair = false;
			}
		}
		if (other->type == COLLIDER_DEATH) {
			if (godmode == false) {
				isinair = false;
				isjumping = false;
				deadbool = true;
				stop_right = true;
				stop_left = true;
				stop_jump = true;
				position.y = other->rect.y - 10;
			}
		}
		if (other->type == COLLIDER_CAMERA) {
			stop_left = true;
		}

		if (other->type == COLLIDER_PORTAL_CHANGESCENEFINAL) {
			exitgame = false;
		}
	}
}

void j1Player::ChangeToLevel1() {
	ice_right = false;
	ice_left = false;
	dimensionnormal = true;
	dimensionagua = false;
	dimensionfuego = false;
	dimensionhielo = false;
	dimensionplanta = false;
	current_graphics = normal_graphics;
	deadbool = false;
	App->scene->cameraxinvert = 0;
	App->render->camera.x = 0;
	App->map->CleanUp();
	App->map->collidersdone = false;
	App->map->Load("Scene01.tmx");
	App->scene->cameralimit01->rect.x = App->render->camera.x;
	App->scene->cameralimit02->rect.x = App->render->camera.x + 380;
	position.x = App->scene->positionplayerinitx;
	position.y = App->scene->positionplayerinity;
	App->scene->donecollidersscene2 = true;
	App->scene->donecollidersscene1 = false;
	App->scene->changelevel = false;
}

void j1Player::ChangeToLevel2() {
	ice_right = false;
	ice_left = false;
	dimensionnormal = true;
	dimensionagua = false;
	dimensionfuego = false;
	dimensionhielo = false;
	dimensionplanta = false;
	current_graphics = normal_graphics;
	deadbool = false;
	App->scene->cameraxinvert = 0;
	App->render->camera.x = 0;
	App->scene->changelevel = true;
	App->map->CleanUp();
	App->map->collidersdone = false;
	App->map->Load("Scene02.tmx");
	//App->tex->UnLoad(App->scene->objects_graphics);
	//App->scene->objects_graphics = App->tex->Load("textures/Objects.png");
	App->scene->cameralimit01->rect.x = App->render->camera.x;
	App->scene->cameralimit02->rect.x = App->render->camera.x + 380;
	position.x = App->scene->positionplayerinitx;
	position.y = App->scene->positionplayerinity;
	App->scene->donecollidersscene2 = false;
	App->scene->donecollidersscene1 = true;
	App->scene->changelevel = true;
}


bool j1Player::Save(pugi::xml_node& data) const
{
	//data.append_child("player");
	//data.child("player").append_attribute("x") = position.x;
	//data.child("player").append_attribute("y") = position.y;
	return true;
}

bool j1Player::Load(pugi::xml_node& data)
{
	//position.x = data.child("player").attribute("x").as_int();
	//position.y = data.child("player").attribute("y").as_int();

	return true;
}