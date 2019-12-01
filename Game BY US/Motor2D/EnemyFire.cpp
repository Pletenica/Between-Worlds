#include "j1Textures.h"
#include "j1Render.h"
#include "j1Audio.h"
#include "j1App.h"
#include "j1Collision.h"
#include "j1Player.h"
#include "j1Scene.h"
#include "j1PathFinding.h"
#include "j1Map.h"
#include "j1EntityManager.h"
#include "EnemyFire.h"
#include "p2Log.h"

#include "SDL/include/SDL_timer.h"
#include "../Game/Brofiler/Brofiler.h"

EnemyFire::EnemyFire() :j1Entity(EntityType::ENEMY_FIRE)
{
	type = EntityType::ENEMY_FIRE;


	/////IDLE ANIMATION//////
	idle.PushBack({ 49, 51, 41, 24 });
	idle.PushBack({ 3, 54, 41, 21 });
	idle.PushBack({ 49, 51, 41, 24 });
	idle.PushBack({ 97, 53, 40, 22 });
	idle.speed = 0.07f;

	/////MOVEMENT ANIMATION//////
	/*
	idle.PushBack({ 1, 165, 33, 24 });
	idle.PushBack({ 41, 166, 34, 23 });
	idle.PushBack({ 1, 165, 33, 24 });
	idle.PushBack({ 78, 165, 40, 24 });
	idle.speed = 0.03f;*/


	name.create("enemy_fire");
}

EnemyFire::~EnemyFire()
{}

bool EnemyFire::CleanUp() {

	return true;
}

bool EnemyFire::Start() {
	//// Load All CONDITIONS //// 
	Current_Animation = idle;
	position.x = 640;
	position.y = 224;

	//// Load All Graphics //// 
	texture = App->tex->Load("textures/enemiesspriteshit.png");

	body = App->collision->AddCollider({ (int)position.x,(int)position.y + 3,32,25 }, COLLIDER_DEATH_ENEMY, this);
	todeathcol = App->collision->AddCollider({ (int)position.x + 5,(int)position.y,20,3 }, COLLIDER_TO_KILL_ENEMY, this);
	colchecktoplayer = App->collision->AddCollider({ (int)position.x - 80,(int)position.y - 90,200,200 }, COLLIDER_CHECK_ENEMY, this);

	return true;
}

bool EnemyFire::Update(float dt) {
	BROFILER_CATEGORY("EnemiesPreUpdate", Profiler::Color::Chartreuse)

		enemypoint.x = position.x;
	enemypoint.y = position.y;
	playerpoint.x = App->entities->player->position.x;
	playerpoint.y = App->entities->player->position.y;

	if (isincoltoplayer == true) {
		App->pathfinding->CreatePath(App->map->WorldToMap(enemypoint.x, enemypoint.y), App->map->WorldToMap(playerpoint.x, playerpoint.y));

		App->map->WorldToMap(enemypoint.x, enemypoint.y);
		if (App->pathfinding->last_path.At(1) != NULL) {
			enemyspeed = Move(enemyspeed);
			LOG("%f, %f", enemyspeed.x, enemyspeed.y);
			LOG("%d, %d", App->pathfinding->last_path.At(1)->x, App->pathfinding->last_path.At(1)->y);
		}

		enemypoint.x += enemyspeed.x;
		enemypoint.y -= enemyspeed.y;
	}

	position.x = enemypoint.x;
	position.y = enemypoint.y;


	isincoltoplayer = false;
	return true;
}

bool EnemyFire::PreUpdate()
{
	BROFILER_CATEGORY("EnemiesUpdate", Profiler::Color::DarkSeaGreen)


		return true;
}

bool EnemyFire::PostUpdate() {
	BROFILER_CATEGORY("EnemiesPostUpdate", Profiler::Color::YellowGreen)

		if (App->entities->player->position.x >= position.x) {
			flip = SDL_FLIP_HORIZONTAL;
		}
		else {
			flip = SDL_FLIP_NONE;
		}

	colchecktoplayer->rect.x = (int)position.x - 80;
	colchecktoplayer->rect.y = (int)position.y - 90;
	todeathcol->rect.x = (int)position.x + 5;
	todeathcol->rect.y = (int)position.y;
	body->rect.x = (int)position.x;
	body->rect.y = (int)position.y + 3;

	App->render->Blit(texture, (int)position.x, (int)position.y, &(idle.GetCurrentFrame()), 1.0f, angle, 0, 0, flip);
	return true;
}

void EnemyFire::OnCollision(Collider* enemy, Collider* player) {
	BROFILER_CATEGORY("PlayerOnCollision", Profiler::Color::MediumAquaMarine)
		if (enemy->type == COLLIDER_CHECK_ENEMY) {
			if (player->type == COLLIDER_PLAYER) {
				isincoltoplayer = true;
			}
		}
}

bool EnemyFire::Save(pugi::xml_node& data) const
{
	data.append_child("enemyattribute");
	data.child("enemyattribute").append_attribute("body_col_x") = body->rect.x;
	data.child("enemyattribute").append_attribute("body_col_y") = body->rect.y;
	data.child("enemyattribute").append_attribute("check_col_x") = colchecktoplayer->rect.x;
	data.child("enemyattribute").append_attribute("check_col_y") = colchecktoplayer->rect.y;
	data.child("enemyattribute").append_attribute("to_kill_col_x") = todeathcol->rect.x;
	data.child("enemyattribute").append_attribute("to_kill_col_y") = todeathcol->rect.y;
	data.append_child("enemyposition");
	data.child("enemyposition").append_attribute("position_x") = position.x;
	data.child("enemyposition").append_attribute("position_y") = position.y;
	return true;
}

bool EnemyFire::Load(pugi::xml_node& data)
{
	body->rect.x = data.child("enemyattribute").attribute("body_col_x").as_int();
	body->rect.y = data.child("enemyattribute").attribute("body_col_y").as_int();
	colchecktoplayer->rect.x = data.child("enemyattribute").attribute("check_col_x").as_int();
	colchecktoplayer->rect.y = data.child("enemyattribute").attribute("check_col_y").as_int();
	todeathcol->rect.x = data.child("enemyattribute").attribute("to_kill_col_x").as_int();
	todeathcol->rect.y = data.child("enemyattribute").attribute("to_kill_col_y").as_int();
	position.x = data.child("enemyposition").attribute("position_x").as_float();
	position.y = data.child("enemyposition").attribute("position_y").as_float();

	return true;
}

fPoint EnemyFire::Move(fPoint speed) {

	iPoint position_map = App->map->WorldToMap(position.x, position.y);
	if (position_map.x > App->pathfinding->last_path.At(1)->x) {
		speed.x = -1;
	}
	else if (position_map.x < App->pathfinding->last_path.At(1)->x) {
		speed.x = 1;
	}

	if (position_map.y > App->pathfinding->last_path.At(1)->y) {
		speed.y = 1;
	}
	else if (position_map.y < App->pathfinding->last_path.At(1)->y) {
		speed.y = -1;
	}

	return speed;
}