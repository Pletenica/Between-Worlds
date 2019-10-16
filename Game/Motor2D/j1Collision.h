#ifndef __j1Collision_H__
#define __j1Collision_H__

#define MAX_COLLIDERS 50000

#include "j1Module.h"
#include "SDL/include/SDL_rect.h"

enum COLLIDER_TYPE
{
	COLLIDER_NONE = -1,
	COLLIDER_ACTION,
	COLLIDER_LIMIT,
	COLLIDER_SUELO,
	COLLIDER_LIANA,
	COLLIDER_AGUA,
	COLLIDER_PLAYER,
	COLLIDER_DEATH,
	COLLIDER_PORTAL_AGUA,
	COLLIDER_PORTAL_FUEGO,
	COLLIDER_PORTAL_HIELO,
	COLLIDER_PORTAL_PLANTA,
	COLLIDER_PORTAL_NORMAL1,
	COLLIDER_PORTAL_NORMAL2,
	COLLIDER_PORTAL_CHANGESCENE1,
	COLLIDER_PORTAL_CHANGESCENEFINAL,
	COLLIDER_CAMERA,
	COLLIDER_CAMERA_LRIGHT,
	COLLIDER_CAMERA_LLEFT,
	COLLIDER_MOVECAM_RIGHT,
	COLLIDER_MOVECAM_LEFT,
	COLLIDER_MAX
};

struct Collider
{
	SDL_Rect rect;
	bool to_delete = false;
	COLLIDER_TYPE type;
	j1Module* callback = nullptr;

	Collider(SDL_Rect rectangle, COLLIDER_TYPE type, j1Module* callback = nullptr) :
		rect(rectangle),
		type(type),
		callback(callback)
	{}

	void SetPos(int, int);

	bool CheckCollision(const SDL_Rect& r) const;

};

class j1Collision : public j1Module
{
public:

	j1Collision();
	~j1Collision();

	bool Start() { return true; };
	bool Awake();
	bool PreUpdate();
	bool Update();
	bool PostUpdate() { DebugDraw(); return true; };
	bool CleanUp();

	Collider* AddCollider(SDL_Rect rect, COLLIDER_TYPE type, j1Module* callback = nullptr);
	void DebugDraw();

private:

	Collider* colliders[MAX_COLLIDERS];
	bool matrix[COLLIDER_MAX][COLLIDER_MAX];
	bool debug = false;
};

#endif // __ModuleCollision_H__