#include "j1App.h"
#include "j1Textures.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Audio.h"
#include "j1Collision.h"
#include "j1Player.h"
#include "j1Scene.h"
#include "j1Map.h"
#include <math.h>
#include "j1EntityManager.h"
#include "Enemy.h"
#include "SDL/include/SDL_timer.h"
#include "../Game/Brofiler/Brofiler.h"

Enemy::Enemy() :j1Entity(EntityType::PLAYER)
{
	name.create("enemies");
}

Enemy::~Enemy()
{}

bool Enemy::Awake(pugi::xml_node& config)
{
	return true;
}

bool Enemy::Start()
{
	
	return true;
}

bool Enemy::CleanUp() {
	
	return true;
}

bool Enemy::Update(float dt) {
	BROFILER_CATEGORY("EnemiesPreUpdate", Profiler::Color::Chartreuse)
	
	return true;
}

bool Enemy::PreUpdate()
{
	BROFILER_CATEGORY("EnemiesUpdate", Profiler::Color::DarkSeaGreen)


	return true;
}

bool Enemy::PostUpdate() {
	BROFILER_CATEGORY("EnemiesPostUpdate", Profiler::Color::YellowGreen)
	
	return true;
}

void Enemy::OnCollision(Collider* enemy, Collider* player) {
	BROFILER_CATEGORY("PlayerOnCollision", Profiler::Color::MediumAquaMarine)
		
}

bool Enemy::Save(pugi::xml_node& data) const
{
	data.append_child("enemies");
	data.append_child("enemyattribute");
	data.child("enemyattribute").append_attribute("body_col_x") = body->rect.x;
	data.child("enemyattribute").append_attribute("body_col_y") = body->rect.y;
	return true;
}

bool Enemy::Load(pugi::xml_node& data)
{
	body->rect.x = data.child("enemyattribute").attribute("body_col_x").as_int();
	body->rect.y = data.child("enemyattribute").attribute("body_col_y").as_int();

	return true;
}