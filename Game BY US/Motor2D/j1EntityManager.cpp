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
		player = (j1Player*)entity;
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
	case EntityType::COINS:
		entity = new Coins();
		entity->body= App->collision->AddCollider({ (int)posx,(int)posy,20,20 }, COLLIDER_COINS, this);
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
	
	for (int i = 0; i < entities_list.count(); i++)
	{
		if (entities_list.At(i) != nullptr) entities_list.At(i)->data->Awake(config);
	}
	return true;
}

bool j1EntityManager::Start()
{
	coins_array.Insert((Coins*)CreateEntity(EntityType::COINS, 200, 190), number_coins++);
	coins_array.Insert((Coins*)CreateEntity(EntityType::COINS, 290, 180), number_coins++);
	coins_array.Insert((Coins*)CreateEntity(EntityType::COINS, 322, 148), number_coins++);
	coins_array.Insert((Coins*)CreateEntity(EntityType::COINS, 354, 116), number_coins++);
	coins_array.Insert((Coins*)CreateEntity(EntityType::COINS, 386, 100), number_coins++);

	coins_array.Insert((Coins*)CreateEntity(EntityType::COINS, 575, 90), number_coins++);
	coins_array.Insert((Coins*)CreateEntity(EntityType::COINS, 605, 80), number_coins++);
	coins_array.Insert((Coins*)CreateEntity(EntityType::COINS, 630, 100), number_coins++);

	coins_array.Insert((Coins*)CreateEntity(EntityType::COINS, 695, 130), number_coins++);
	coins_array.Insert((Coins*)CreateEntity(EntityType::COINS, 710, 100), number_coins++);
	coins_array.Insert((Coins*)CreateEntity(EntityType::COINS, 725, 130), number_coins++);

	coins_array.Insert((Coins*)CreateEntity(EntityType::COINS, 800, 100), number_coins++);
	coins_array.Insert((Coins*)CreateEntity(EntityType::COINS, 900, 140), number_coins++);
	coins_array.Insert((Coins*)CreateEntity(EntityType::COINS, 860, 50), number_coins++);

	for (int i = 0; i < entities_list.count(); i++){
		if (entities_list.At(i) != nullptr) entities_list.At(i)->data->Start();
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
		if (entities_list.At(i)!=nullptr) entities_list.At(i)->data->Update(dt);
	}
	return true;
}

bool j1EntityManager::PostUpdate()
{
	for (int i = 0; i < entities_list.count(); i++)
	{
		if (entities_list.At(i) != nullptr) entities_list.At(i)->data->PostUpdate();
	}
	
	return true;
}

bool j1EntityManager::CleanUp()
{
	for (int i = entities_list.count() - 1; i >= 0; i--)
	{
		if (entities_list.At(i) != nullptr) entities_list.At(i)->data->CleanUp();
	}
	entities_list.clear();
	return true;
}

void j1EntityManager::OnCollision(Collider* c1, Collider* c2) {
	for (uint i = 0; i < entities_list.count(); ++i)
		if (entities_list.At(i)->data != nullptr && entities_list.At(i)->data->body == c1)
			entities_list.At(i)->data->OnCollision(c1, c2);
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
		if (entities_list.At(i) != nullptr) entities_list.At(i)->data->Load(data2);
	}
	return true;
}

bool j1EntityManager::Save(pugi::xml_node& data) const
{

	pugi::xml_node data2 = data;
	for (unsigned int i = 0; i < entities_list.count(); i++)
	{
		data2 = data.append_child(entities_list.At(i)->data->name.GetString());
		if (entities_list.At(i) != nullptr) entities_list.At(i)->data->Save(data2);
		data2.append_attribute("id") = i;
	}

	return true;
}