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
#include "EnemyLiana.h"
#include "p2Log.h"

#include "SDL/include/SDL_timer.h"
#include "../Game/Brofiler/Brofiler.h"

EnemyLiana::EnemyLiana() :j1Entity(EntityType::ENEMY_LIANA)
{
	type = EntityType::ENEMY_LIANA;


	/////MOVEMENT ANIMATION//////
	idle.PushBack({ 149, 47, 20, 26 });
	idle.PushBack({ 146, 12, 24, 32 });
	idle.PushBack({ 149, 47, 20, 26 });
	idle.PushBack({ 149, 75, 23, 34 });
	idle.speed = 0.03f;



	name.create("enemy_liana");
}

EnemyLiana::~EnemyLiana()
{}

bool EnemyLiana::CleanUp() {

	return true;
}

bool EnemyLiana::Start() {
	//// Load All CONDITIONS //// 
	Current_Animation = idle;
	initialposition.x=position.x;
	initialposition.y = position.y;

	//// Load All Graphics //// 
	texture = App->tex->Load("textures/enemiesspriteshit.png");

	body = App->collision->AddCollider({ (int)position.x-5,(int)position.y,20,25 }, COLLIDER_DEATH_ENEMY, this);

	return true;
}

bool EnemyLiana::Update(float dt) {
	BROFILER_CATEGORY("EnemiesPreUpdate", Profiler::Color::Chartreuse)
	enemyspeed.x = 0;

	if (isup == true) {
		enemyspeed.y = -1;
	}
	if (isup == false) {
		enemyspeed.y = 1;
	}

	if (position.y <= 0) {
		isup = false;
	}
	if (position.y >= initialposition.y) {
		isup = true;
	}

	position.y += enemyspeed.y;

	return true;
}

bool EnemyLiana::PreUpdate()
{
	BROFILER_CATEGORY("EnemiesUpdate", Profiler::Color::DarkSeaGreen)


		return true;
}

bool EnemyLiana::PostUpdate() {
	BROFILER_CATEGORY("EnemiesPostUpdate", Profiler::Color::YellowGreen)

		if (isup==false) {
			flip = SDL_FLIP_VERTICAL;
		}
		else {
			flip = SDL_FLIP_NONE;
		}

	body->rect.x = (int)position.x;
	body->rect.y = (int)position.y + 3;

	App->render->Blit(texture, (int)position.x, (int)position.y, &(idle.GetCurrentFrame()), 1.0f, angle, 0, 0, flip);
	return true;
}


bool EnemyLiana::Save(pugi::xml_node& data) const
{
	data.append_child("enemyattribute");
	data.child("enemyattribute").append_attribute("body_col_x") = body->rect.x;
	data.child("enemyattribute").append_attribute("body_col_y") = body->rect.y;
	data.append_child("enemyposition");
	data.child("enemyposition").append_attribute("position_x") = position.x;
	data.child("enemyposition").append_attribute("position_y") = position.y;
	return true;
}

bool EnemyLiana::Load(pugi::xml_node& data)
{
	body->rect.x = data.child("enemyattribute").attribute("body_col_x").as_int();
	body->rect.y = data.child("enemyattribute").attribute("body_col_y").as_int();
	position.x = data.child("enemyposition").attribute("position_x").as_float();
	position.y = data.child("enemyposition").attribute("position_y").as_float();

	return true;
}

fPoint EnemyLiana::Move(fPoint speed) {



	return speed;
}