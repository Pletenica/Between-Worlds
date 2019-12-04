#include "j1EntityManager.h"
#include "j1Entity.h"
#include "j1App.h"
#include "j1Player.h"
#include "EnemyAigua.h"
#include "EnemyLiana.h"
#include "EnemyIce.h"
#include "EnemyFire.h"
#include "p2Log.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Input.h"
#include "j1Collision.h"
#include "j1Window.h"
#include "j1Scene.h"
#include "j1Map.h"
#include "j1Audio.h"


j1EntityManager::j1EntityManager()
{
	player = (j1Player*)CreateEntity(EntityType::PLAYER);
	name.create("EntityManager");
	
}


j1EntityManager::~j1EntityManager()
{}

j1Entity* j1EntityManager::CreateEntity(EntityType type, int posx, int posy)
{
	//static_assert(EntityType::UNKNOWN == 4, "code needs update");
	j1Entity* entity = nullptr;
	switch (type)
	{
	case EntityType::PLAYER:
		entity = new j1Player();
		break;
	case EntityType::ENEMY_WATTER:
		entity = new EnemyAigua();
		entity->position.x = posx;
		entity->position.y = posy;
		break;
	case EntityType::ENEMY_FIRE:
		entity = new EnemyFire();
		entity->position.x = posx;
		entity->position.y = posy;
		break;
	case EntityType::ENEMY_LIANA:
		entity = new EnemyLiana();
		entity->position.x = posx;
		entity->position.y = posy;
		break;
	case EntityType::ENEMY_ICE:
		entity = new EnemyIce();
		entity->position.x = posx;
		entity->position.y = posy;
		break;
	case EntityType::UNKNOWN:
		break;
	default:
		break;
	}
	entities_list.add(entity);
	return entity;
}

void j1EntityManager::DestroyEntity(j1Entity* delete_entity)
{
	RELEASE(delete_entity);
}

bool j1EntityManager::Awake(pugi::xml_node& config)
{
	
	//enemy_ice1 = (EnemyIce*)App->entities->CreateEntity(EntityType::ENEMY_ICE, 2144, 208);
	//enemy_ice2 = (EnemyIce*)App->entities->CreateEntity(EntityType::ENEMY_ICE, 2558, 208);
	//enemy_ice3 = (EnemyIce*)App->entities->CreateEntity(EntityType::ENEMY_ICE, 3130, 208);
	//enemy_liana1 = (EnemyLiana*)App->entities->CreateEntity(EntityType::ENEMY_LIANA, 808, 95);
	//enemy_liana2 = (EnemyLiana*)App->entities->CreateEntity(EntityType::ENEMY_LIANA, 904, 189);
	//enemy_liana3 = (EnemyLiana*)App->entities->CreateEntity(EntityType::ENEMY_LIANA, 1032, 96);
	//enemy_liana4 = (EnemyLiana*)App->entities->CreateEntity(EntityType::ENEMY_LIANA, 1160, 146);
	//enemy_liana5 = (EnemyLiana*)App->entities->CreateEntity(EntityType::ENEMY_LIANA, 1224, 96);
	
	/*
	EnemyAigua* enemy_aigua1 = (EnemyAigua*)App->entities->CreateEntity(EntityType::ENEMY_WATTER, 2420, 64);
	EnemyAigua* enemy_aigua2 = (EnemyAigua*)App->entities->CreateEntity(EntityType::ENEMY_WATTER, 2624, 160);
	EnemyAigua* enemy_aigua3 = (EnemyAigua*)App->entities->CreateEntity(EntityType::ENEMY_WATTER, 3008, 96);
	EnemyAigua* enemy_aigua4 = (EnemyAigua*)App->entities->CreateEntity(EntityType::ENEMY_WATTER, 3008, 224);
	EnemyFire* enemy_fire1 = (EnemyFire*)App->entities->CreateEntity(EntityType::ENEMY_FIRE, 640, 240);
	EnemyFire* enemy_fire2 = (EnemyFire*)App->entities->CreateEntity(EntityType::ENEMY_FIRE, 832, 240);
	*/

	for (int i = 0; i < entities_list.count(); i++)
	{
		entities_list.At(i)->data->Awake(config);
	}
	return true;
}

bool j1EntityManager::Start()
{
	for (int i = 0; i < entities_list.count(); i++){
		entities_list.At(i)->data->Start();
	}
	return true;
}

bool j1EntityManager::PreUpdate()
{


	for (int i = 0; i < entities_list.count(); i++)
	{
		entities_list.At(i)->data->PreUpdate();
	}
	return true;
}

bool j1EntityManager::Update(float dt)
{

	for (int i = 0; i < entities_list.count(); i++)
	{
		entities_list.At(i)->data->Update(dt);
	}
	return true;
}

bool j1EntityManager::PostUpdate()
{
	for (int i = 0; i < entities_list.count(); i++)
	{
		entities_list.At(i)->data->PostUpdate();
	}
	
	/*
	if (App->scene->changelevel == false && enemiesdone1 == false) {
		DestroyEntity(enemy_aigua1);
		DestroyEntity(enemy_aigua2);
		DestroyEntity(enemy_aigua3);
		DestroyEntity(enemy_aigua4);
		DestroyEntity(enemy_fire1);
		DestroyEntity(enemy_fire2);

		EnemyIce* enemy_ice1 = (EnemyIce*)App->entities->CreateEntity(EntityType::ENEMY_ICE, 2144, 208);
		EnemyIce* enemy_ice2 = (EnemyIce*)App->entities->CreateEntity(EntityType::ENEMY_ICE, 2558, 208);
		EnemyIce* enemy_ice3 = (EnemyIce*)App->entities->CreateEntity(EntityType::ENEMY_ICE, 3130, 208);
		EnemyLiana* enemy_liana1 = (EnemyLiana*)App->entities->CreateEntity(EntityType::ENEMY_LIANA, 808, 95);
		EnemyLiana* enemy_liana2 = (EnemyLiana*)App->entities->CreateEntity(EntityType::ENEMY_LIANA, 904, 189);
		EnemyLiana* enemy_liana3 = (EnemyLiana*)App->entities->CreateEntity(EntityType::ENEMY_LIANA, 1032, 96);
		EnemyLiana* enemy_liana4 = (EnemyLiana*)App->entities->CreateEntity(EntityType::ENEMY_LIANA, 1160, 146);
		EnemyLiana* enemy_liana5 = (EnemyLiana*)App->entities->CreateEntity(EntityType::ENEMY_LIANA, 1224, 96);
		enemiesdone1 = true;
	}

	if (App->scene->changelevel == true && enemiesdone2 == false) {
		DestroyEntity(enemy_ice1);
		DestroyEntity(enemy_ice2);
		DestroyEntity(enemy_ice3);
		DestroyEntity(enemy_liana1);
		DestroyEntity(enemy_liana2);
		DestroyEntity(enemy_liana3);
		DestroyEntity(enemy_liana4);
		DestroyEntity(enemy_liana5);

		EnemyAigua* enemy_aigua1 = (EnemyAigua*)App->entities->CreateEntity(EntityType::ENEMY_WATTER, 2420, 64);
		EnemyAigua* enemy_aigua2 = (EnemyAigua*)App->entities->CreateEntity(EntityType::ENEMY_WATTER, 2624, 160);
		EnemyAigua* enemy_aigua3 = (EnemyAigua*)App->entities->CreateEntity(EntityType::ENEMY_WATTER, 3008, 96);
		EnemyAigua* enemy_aigua4 = (EnemyAigua*)App->entities->CreateEntity(EntityType::ENEMY_WATTER, 3008, 224);
		EnemyFire* enemy_fire1 = (EnemyFire*)App->entities->CreateEntity(EntityType::ENEMY_FIRE, 640, 240);
		EnemyFire* enemy_fire2 = (EnemyFire*)App->entities->CreateEntity(EntityType::ENEMY_FIRE, 832, 240);
		enemiesdone2 = true;
	}
	*/

	return true;
}

bool j1EntityManager::CleanUp()
{
	for (int i = entities_list.count() - 1; i >= 0; i--)
	{
		entities_list.del(entities_list.At(i));
	}
	entities_list.clear();
	return true;
}

void j1EntityManager::OnCollision(Collider* c1, Collider* c2) {
	for (int i = 0; i < entities_list.count(); i++)
	{
		entities_list.At(i)->data->OnCollision(c1, c2);
	}
}

bool j1EntityManager::Load(pugi::xml_node& data)
{
	pugi::xml_node data2 = data;
	for (unsigned int i = 0; i < entities_list.count(); i++)
	{
		data2 = data.child(entities_list.At(i)->data->name.GetString());
		while (data2.attribute("id").as_int() != i) {
			data2 = data2.next_sibling(entities_list.At(i)->data->name.GetString());
		};
		entities_list.At(i)->data->Load(data2);
	}
	return true;
}

bool j1EntityManager::Save(pugi::xml_node& data) const
{

	pugi::xml_node data2 = data;
	for (unsigned int i = 0; i < entities_list.count(); i++)
	{
		data2 = data.append_child(entities_list.At(i)->data->name.GetString());
		entities_list.At(i)->data->Save(data2);
		data2.append_attribute("id") = i;
	}

	return true;
}