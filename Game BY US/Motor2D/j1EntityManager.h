#ifndef _ENTITY_MANAGER_H_
#define _ENTITY_MANAGER_H_

#include "j1Module.h"
#include "p2Point.h"
#include "p2List.h"
#include "j1Animation.h"
#include "j1Entity.h"
#include "j1Player.h"


class j1EntityManager : public j1Module
{
public:
	j1Player* player;
	p2List<j1Entity*> entities_list;
	pugi::xml_node config;
	bool enemiesdone2 = false;
	bool enemiesdone1 = false;
	EnemyIce* enemy_ice1;
	EnemyIce* enemy_ice2;
	EnemyIce* enemy_ice3;
	EnemyLiana* enemy_liana1;
	EnemyLiana* enemy_liana2;
	EnemyLiana* enemy_liana3;
	EnemyLiana* enemy_liana4;
	EnemyLiana* enemy_liana5;

	EnemyAigua* enemy_aigua1;
	EnemyAigua* enemy_aigua2;
	EnemyAigua* enemy_aigua3;
	EnemyAigua* enemy_aigua4;
	EnemyFire* enemy_fire1;
	EnemyFire * enemy_fire2;



public:

	j1EntityManager();
	~j1EntityManager();

	bool Awake(pugi::xml_node& config);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);
	bool Load(pugi::xml_node& data);
	bool Save(pugi::xml_node& data)const;

	j1Entity* CreateEntity(EntityType type, int posx=0, int posy=0);
	virtual void DestroyEntity(j1Entity* delete_entity);


};

#endif // !_ENTITY_MANAGER_H_