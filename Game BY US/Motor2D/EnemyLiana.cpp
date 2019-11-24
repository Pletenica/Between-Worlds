#include "j1Textures.h"
#include "j1Render.h"
#include "j1Audio.h"
#include "j1App.h"
#include "j1Collision.h"
#include "j1Player.h"
#include "j1Scene.h"
#include "j1Map.h"
#include "j1EntityManager.h"
#include "EnemyLiana.h"

#include "SDL/include/SDL_timer.h"
#include "../Game/Brofiler/Brofiler.h"

EnemyLiana::EnemyLiana() :j1Entity(EntityType::ENEMY_LIANA)
{
	type = EntityType::ENEMY_LIANA;

	
	/////IDLE ANIMATION//////
	Current_Animation.PushBack({ 0, 0, 32, 32 });
	Current_Animation.PushBack({ 32, 0, 32, 32 });
	Current_Animation.PushBack({ 64, 0, 32, 32 });
	Current_Animation.PushBack({ 32, 0, 32, 32 });
	Current_Animation.speed = 0.07f;



	name.create("enemy_liana");
}

EnemyLiana::~EnemyLiana()
{}

bool EnemyLiana::CleanUp(){

	return true;
}

bool EnemyLiana::Start() {
	//// Load All CONDITIONS //// 
	Current_Animation = idle;
	position.x = 200;
	position.y = 100;

	//// Load All Graphics //// 
	texture = App->tex->Load("textures/Enemies.png");

	body = App->collision->AddCollider({ (int)position.x,(int)position.y+3,18,32 }, COLLIDER_DEATH_ENEMY, this);
	todeathcol = App->collision->AddCollider({ (int)position.x+3,(int)position.y,14,3 }, COLLIDER_TO_KILL_ENEMY, this);
	return true;
}

bool EnemyLiana::Update(float dt) {
	BROFILER_CATEGORY("EnemiesPreUpdate", Profiler::Color::Chartreuse)


		return true;
}

bool EnemyLiana::PreUpdate()
{
	BROFILER_CATEGORY("EnemiesUpdate", Profiler::Color::DarkSeaGreen)


		return true;
}

bool EnemyLiana::PostUpdate() {
	BROFILER_CATEGORY("EnemiesPostUpdate", Profiler::Color::YellowGreen)

	App->render->Blit(texture,0, 0, &(Current_Animation.GetCurrentFrame()), 1.0f, 0, 0, 0, flip);
	return true;
}

void EnemyLiana::OnCollision(Collider* enemy, Collider* player) {
	BROFILER_CATEGORY("PlayerOnCollision", Profiler::Color::MediumAquaMarine)

}

bool EnemyLiana::Save(pugi::xml_node& data) const
{
	data.append_child("enemies");
	data.append_child("enemyattribute");
	data.child("enemyattribute").append_attribute("body_col_x") = body->rect.x;
	data.child("enemyattribute").append_attribute("body_col_y") = body->rect.y;
	return true;
}

bool EnemyLiana::Load(pugi::xml_node& data)
{
	body->rect.x = data.child("enemyattribute").attribute("body_col_x").as_int();
	body->rect.y = data.child("enemyattribute").attribute("body_col_y").as_int();

	return true;
}