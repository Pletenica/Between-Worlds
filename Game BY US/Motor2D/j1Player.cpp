#include "j1App.h"
#include "j1Textures.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Audio.h"
#include "j1Collision.h"
#include "j1Player.h"
#include "j1Scene.h"
#include "j1Map.h"
#include "j1UiInGame.h"
#include <math.h>
#include "j1EntityManager.h"
#include "EnemyAigua.h"
#include "EnemyFire.h"
#include "EnemyIce.h"
#include "EnemyLiana.h"
#include "j1UiInGame.h"
#include "SDL/include/SDL_timer.h"
#include "p2DynArray.h"
#include "../Game/Brofiler/Brofiler.h"

j1Player::j1Player() :j1Entity(EntityType::PLAYER)
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

	name.create("player");
}

j1Player::~j1Player()
{}

bool j1Player::Awake(pugi::xml_node& config)
{
	/////// SCENE 1 PORTALS ///////
	Ginit = config.child("player").child("gravity").attribute("Ginit").as_float(1);
	jump_vel = config.child("player").child("gravity").attribute("JumpVel").as_float(12);
	G_max = config.child("player").child("gravity").attribute("Gmax").as_float(17);
	speed_player_aux = config.child("player").child("speed").attribute("movement").as_float();
	speed_player_ice_aux = config.child("player").child("speed").attribute("iceinercy").as_float();
	speed_player_jump_aux = config.child("player").child("speed").attribute("movementinair").as_float();
	positionxinit = config.child("player").child("position").attribute("positionxinit").as_int(2);
	positionyinit = config.child("player").child("position").attribute("positionyinit").as_int(2);

	return true;
}

// Load assets
bool j1Player::Start()
{
	//// Load All CONDITIONS //// 
	Current_Animation =idle;
	position.x = positionxinit;
	position.y = positionyinit;

	//// Load All Graphics //// 
	normal_graphics = App->tex->Load("textures/PlayerNormal.png");
	fire_graphics = App->tex->Load("textures/PlayerFire.png");
	plant_graphics = App->tex->Load("textures/PlayerPlant.png");
	ice_graphics = App->tex->Load("textures/PlayerSnow.png");
	watter_graphics = App->tex->Load("textures/PlayerWatter.png");
	current_graphics = normal_graphics;

	//// Load All SOUNDS & COLLISIONS //// 
	jumpingsound = App->audio->LoadFx("audio/fx/jump.wav");
	deathsound = App->audio->LoadFx("audio/fx/death.wav");
	walkingsound = App->audio->LoadFx("audio/fx/walk.wav");
	portalsound = App->audio->LoadFx("audio/fx/portal.wav");
	body = App->collision->AddCollider({ (int)position.x,(int)position.y,18,32 }, COLLIDER_PLAYER, this);

	type = EntityType::PLAYER;
	return true;
}

//Clean Up
bool j1Player::CleanUp() {
	App->audio->StopFx();
	App->tex->UnLoad(current_graphics);
	App->tex->UnLoad(fire_graphics);
	App->tex->UnLoad(plant_graphics);
	App->tex->UnLoad(ice_graphics);
	App->tex->UnLoad(watter_graphics);
	App->tex->UnLoad(normal_graphics);

	return true;
}


bool j1Player::Update(float dt) {
	BROFILER_CATEGORY("PlayerPreUpdate", Profiler::Color::Chartreuse)
	right = false;
	left = false;
	speed_player = speed_player_aux;
	speed_player = speed_player * dt * 500;
	speed_player_jump = speed_player_jump_aux;
	speed_player_jump = speed_player_jump * dt * 100;
	speed_player_ice = speed_player_ice_aux;
	speed_player_ice = speed_player_ice * dt * 50;

	round(speed_player);

	if (deadbool == false && isinair == false && isjumping == false && isdoublejumping==false) {
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
		if (App->entities->player->godmode == true) {
			//body = App->collision->AddCollider({ position.x,position.y,20,32 }, COLLIDER_PLAYER, this);
			godmode = false;
		}
		else {
			isinair = false;
			G = 7;
			App->entities->player->godmode = true;

		}
	}
	if (godmode == true) {
		isinair = false;
		isjumping = false;
		isdoublejumping = false;
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

		if ((App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)&&!stop_left) {
			position.x -= speed_player;
			App->audio->PlayFx(walkingsound, 0);
			if (dimensionhielo == true) {
				ice_left = true;
				ice_right = false;
			}
			left = true;
			Current_Animation.GetCurrentFrame() = walk.GetCurrentFrame();
		}

		if ((App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)&&!stop_right) {
			position.x += speed_player;
			App->audio->PlayFx(walkingsound,0);
			if (dimensionhielo == true) {
				ice_right = true;
				ice_left = false;
			}
			right = true;
			Current_Animation.GetCurrentFrame() = walk.GetCurrentFrame();
		}
		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT && !stop_jump) {
			isjumping = true;
			if (App->audio->PlayFx(walkingsound, 0) == true || App->audio->PlayFx(walkingsound, 0) == false) {
				App->audio->PlayFx(jumpingsound, 0);
			}
		}
	}

	//////// WATTER ////////
	if (dimensionagua == true) {
		isjumping = false;
		isdoublejumping = false;
		Current_Animation.GetCurrentFrame() = idle.GetCurrentFrame();
		if (godmode == false) {

			position.y += speed_player/5;

			
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

			if ((App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) && (position.y > 20) && (!stop_up)) {
				position.y -= speed_player;
			}
			if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
				position.y += speed_player;
			}

			isinair = false;
		}
	}

	//////// LIANA ////////
	if (isinliana == true) {
		isjumping = false;
		isinair = false;
		G = 10;
		isdoublejumping = false;
		Current_Animation.GetCurrentFrame() = liana.GetCurrentFrame();
		position.y += speed_player / 10;
		
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

	}

	//////// JUMPING ////////
	if (isjumping == true) {
		Current_Animation.GetCurrentFrame() = jump.GetCurrentFrame();
		if (position.y > 0) {
			if (isdoublejumping == false) {
				if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN) {
					isdoublejumping = true;
					isjumping = false;
					if (App->audio->PlayFx(walkingsound, 0) == true || App->audio->PlayFx(walkingsound, 0) == false) {
						App->audio->PlayFx(jumpingsound, 0);
					}
					G = Ginit;
				}
				isinair = false;
				ice_left = false;
				ice_right = false;
				
				G+=1*dt*100;
				position.y += (G - jump_vel)*dt * 20;

				if ((App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) && !stop_left) {
					position.x -= speed_player_jump;
				}

				if ((App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) && !stop_right) {
					position.x += speed_player_jump;
				}
			}
		}
		else {
			G = 5;
			isinair = true;
			isjumping = false;
			isdoublejumping = false;
		}
	}

	//////// DOUBLE JUMPING ////////
	if (isdoublejumping == true) {
		Current_Animation.GetCurrentFrame() = jump.GetCurrentFrame();

		if (position.y > 0) {
			isinair = false;
			ice_left = false;
			ice_right = false;

			G += 1 * dt * 100;
			position.y += (G - jump_vel)*dt * 20;

			if ((App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) && !stop_left) {
				position.x -= speed_player_jump;
			}

			if ((App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) && !stop_right) {
				position.x += speed_player_jump;
			}
		}
		else {
			G = 5;
			isinair = true;
			isjumping = false;
			isdoublejumping = false;
		}
	}

	//////// AIR ////////
	if (isinair==true && isinliana==false) {
		isjumping = false;
		isdoublejumping = false;
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
		
		position.y += G*dt * 50;
	}

	//////// INPUT FAILS ////////
	if ((App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) && (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)) {
		Current_Animation.GetCurrentFrame() = idle.GetCurrentFrame();
	}

	//////// DEATH ////////
	if (deadbool == true) {
		
		if (App->audio->PlayFx(deathsound, 0) == false) {
			App->audio->PlayFx(deathsound, 0);
		}

		Current_Animation.GetCurrentFrame() = dead.GetCurrentFrame();
		stop_left = true;
		stop_jump = true;
		stop_right = true;
		G = 1;
		if (dead.finished == 1) {
			if (lifes > 0) lifes--;
			if (App->scene->changelevel == false) {
				ChangeToLevel1();
			}
			else {
				ChangeToLevel2();
			}
		}
	}

	body->rect.x = position.x + 5;
	body->rect.y = position.y;
	
	if (dimensionhielo == true) {
		if ((ice_left == true)&& (App->input->GetKey(SDL_SCANCODE_A) != KEY_REPEAT)) {
			position.x -= speed_player_ice;
		}
		if ((ice_right == true) && (App->input->GetKey(SDL_SCANCODE_D) != KEY_REPEAT)) {
			position.x += speed_player_ice;
		}
	}

	return true;
}


// Update: draw background
bool j1Player::PreUpdate()
{
	BROFILER_CATEGORY("PlayerUpdate", Profiler::Color::DarkSeaGreen)
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
	BROFILER_CATEGORY("PlayerPostUpdate", Profiler::Color::YellowGreen)
	isinair = true;
	isinliana = false;
	stop_right = false;
	stop_left = false;
	stop_jump = false;
	stop_up = false;

	if (body->CheckCollision(App->scene->cameralimit01->rect) == true) {
		stop_left = true;
	}
	if (body->CheckCollision(App->scene->cameralimit02->rect) == true) {
		stop_right = true;
	}
	App->render->Blit(current_graphics, position.x, position.y, &(Current_Animation.GetCurrentFrame()), 1.0f, 0, 0, 0, flip);
	//App->scene->justtouchcheckpoint = false;
	return exitgame;
}


void j1Player::OnCollision(Collider* player, Collider* other) {
	BROFILER_CATEGORY("PlayerOnCollision", Profiler::Color::MediumAquaMarine)
	if (player->type == COLLIDER_PLAYER) {
		if (other->type == COLLIDER_CORRIENTE_AGUA) {
			position.x -= speed_player / 4;
			
		}
		if (other->type == COLLIDER_PORTAL_AGUA) {
			App->audio->PlayFx(portalsound, 0);
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
			App->audio->PlayFx(portalsound, 0);
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
			App->audio->PlayFx(portalsound, 0);
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
			App->audio->PlayFx(portalsound, 0);
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
			App->audio->PlayFx(portalsound, 0);
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
			App->audio->PlayFx(portalsound, 0);
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
			App->audio->PlayFx(portalsound, 0);
			App->entities->player->ChangeToLevel2();
			App->SaveGame();
		}

		if (other->type == COLLIDER_SUELO) {
			isinliana = false;
			isinair = false;
			isinice = false;
			isjumping = false;
			isdoublejumping = false;
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
				if ((other->rect.y <= position.y) && (SDL_SCANCODE_W)) {
					stop_up = true;
					Current_Animation.GetCurrentFrame() = idle.GetCurrentFrame();
				}
				if (((other->rect.y <= position.y) && position.x < other->rect.x) && (SDL_SCANCODE_D)) {
					stop_right = true;
					Current_Animation.GetCurrentFrame() = idle.GetCurrentFrame();
				}
				if (((other->rect.y <= position.y) && position.x > other->rect.x) && (SDL_SCANCODE_A)) {
					stop_left = true;
					Current_Animation.GetCurrentFrame() = idle.GetCurrentFrame();
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
				isdoublejumping = false;
				deadbool = true;
				stop_right = true;
				stop_left = true;
				stop_jump = true;
				position.y = other->rect.y-20;
			}
		}
		if (other->type == COLLIDER_DEATH_ENEMY) {
			if (godmode == false) {
				isinair = false;
				isjumping = false;
				isdoublejumping = false;
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
		if (other->type == COLLIDER_CHECKPOINT_SCENE) {
			if (App->scene->justtouchcheckpoint != true) {
				App->SaveGame();
			}
			App->scene->justtouchcheckpoint = true;
		}
		if (other->type == COLLIDER_TO_KILL_ENEMY) {
			//App->entities->entities_list.del();
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
	
	if (deadbool == true) {
		App->LoadGame();
	}
	if (deadbool == false && App->scene->changelevel==true) {
		App->uiingame->CleanUpCoinsArray();
		//App->uiingame->CreateFirstWorldCoins();
	}
	
	deadbool = false;
	App->scene->cameraxinvert = 0;
	App->render->camera.x = 0;
	App->map->CleanUp();
	App->map->collidersdone = false;
	App->map->Load("Scene01.tmx");
	App->scene->cameralimit01->rect.x = App->render->camera.x;
	App->scene->cameralimit02->rect.x = App->render->camera.x + 380;
	App->scene->donecollidersscene2 = true;
	App->scene->donecollidersscene1 = false;
	App->scene->changelevel = false;
	App->scene->justtouchcheckpoint = false;
	position.x = positionxinit;
	position.y = positionyinit;
	App->SaveGame();
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
	
	if (deadbool == true) {
		App->LoadGame();
	}
	if (deadbool == false && App->scene->changelevel == false) {
		App->uiingame->CleanUpCoinsArray();
		//App->uiingame->CreateSecondWorldCoins();
	}
	
	deadbool = false;
	App->scene->cameraxinvert = 0;
	App->render->camera.x = 0;
	App->scene->changelevel = true;
	App->map->CleanUp();
	App->map->collidersdone = false;
	App->map->Load("Scene02.tmx");
	App->scene->cameralimit01->rect.x = App->render->camera.x;
	App->scene->cameralimit02->rect.x = App->render->camera.x + 380;
	App->scene->donecollidersscene2 = false;
	App->scene->donecollidersscene1 = true;
	App->scene->changelevel = true;
	App->scene->justtouchcheckpoint = false;
	position.x = positionxinit;
	position.y = positionyinit;
	App->SaveGame();
}

bool j1Player::Save(pugi::xml_node& data) const
{
	data.append_child("player");
	data.append_child("playerposition");
	data.child("playerposition").append_attribute("x") = position.x;
	data.child("playerposition").append_attribute("y") = position.y;
	data.child("playerposition").append_attribute("x_init") = positionxinit;
	data.child("playerposition").append_attribute("y_init") = positionyinit;
	data.append_child("playerworld");
	data.child("playerworld").append_attribute("watter") = dimensionagua;
	data.child("playerworld").append_attribute("fire") = dimensionfuego;
	data.child("playerworld").append_attribute("plant") = dimensionplanta;
	data.child("playerworld").append_attribute("ice") = dimensionhielo;
	data.child("playerworld").append_attribute("normal") = dimensionnormal;
	data.append_child("playerattribute");
	data.child("playerattribute").append_attribute("ice_right") = ice_right;
	data.child("playerattribute").append_attribute("ice_left") = ice_left;
	data.child("playerattribute").append_attribute("left") = left;
	data.child("playerattribute").append_attribute("right") = right;
	data.child("playerattribute").append_attribute("body_col_x") = body->rect.x;
	data.child("playerattribute").append_attribute("body_col_y") = body->rect.y;
	return true;
}

bool j1Player::Load(pugi::xml_node& data)
{
	body->rect.x= data.child("playerattribute").attribute("body_col_x").as_int();
	body->rect.y = data.child("playerattribute").attribute("body_col_y").as_int();
	right=data.child("playerattribute").attribute("right").as_bool();
	left = data.child("playerattribute").attribute("left").as_bool();
	position.x = data.child("playerposition").attribute("x").as_float();
	position.y = data.child("playerposition").attribute("y").as_float()-30;
	positionxinit = data.child("playerposition").attribute("x_init").as_float();
	positionyinit = data.child("playerposition").attribute("y_init").as_float();
	dimensionnormal = data.child("playerworld").attribute("normal").as_bool();
	dimensionagua = data.child("playerworld").attribute("watter").as_bool();
	dimensionfuego = data.child("playerworld").attribute("fire").as_bool();
	dimensionplanta = data.child("playerworld").attribute("plant").as_bool();
	dimensionhielo = data.child("playerworld").attribute("ice").as_bool();
	ice_right = data.child("playerattribute").attribute("ice_right").as_bool();
	ice_left = data.child("playerattribute").attribute("ice_left").as_bool();
	G = 5;
	return true;
}
