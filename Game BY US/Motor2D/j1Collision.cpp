#include "j1App.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Player.h"
#include "j1Entity.h"
#include "j1EntityManager.h"
#include "EnemyAigua.h"
#include "EnemyLiana.h"
#include "EnemyIce.h"
#include "EnemyFire.h"
#include "j1Collision.h"

j1Collision::j1Collision()
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[COLLIDER_LIMIT][COLLIDER_LIMIT] = false;
	matrix[COLLIDER_LIMIT][COLLIDER_CAMERA] = true;
	matrix[COLLIDER_LIMIT][COLLIDER_DEATH] = true;
	matrix[COLLIDER_LIMIT][COLLIDER_ACTION] = true;
	matrix[COLLIDER_LIMIT][COLLIDER_PLAYER] = true;

	matrix[COLLIDER_SUELO][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_SUELO][COLLIDER_PORTAL_AGUA] = true;
	matrix[COLLIDER_SUELO][COLLIDER_PORTAL_FUEGO] = true;
	matrix[COLLIDER_SUELO][COLLIDER_PORTAL_PLANTA] = true;
	matrix[COLLIDER_SUELO][COLLIDER_PORTAL_HIELO] = true;
	matrix[COLLIDER_SUELO][COLLIDER_PORTAL_NORMAL1] = true;
	matrix[COLLIDER_SUELO][COLLIDER_PORTAL_NORMAL2] = true;
	matrix[COLLIDER_SUELO][COLLIDER_PORTAL_CHANGESCENE1] = true;
	matrix[COLLIDER_SUELO][COLLIDER_PORTAL_CHANGESCENEFINAL] = true;

	matrix[COLLIDER_CHECKPOINT_SCENE][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_TO_KILL_ENEMY][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_CHECK_ENEMY][COLLIDER_PLAYER] = true;

	matrix[COLLIDER_PLAYER][COLLIDER_CHECK_ENEMY] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_TO_KILL_ENEMY] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_SUELO] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_CHECKPOINT_SCENE] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_LIMIT] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_DEATH] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_DEATH_ENEMY] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_ACTION] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_LIANA] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_CORRIENTE_AGUA] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PORTAL_AGUA] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PORTAL_FUEGO] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PORTAL_PLANTA] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PORTAL_HIELO] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PORTAL_NORMAL1] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PORTAL_NORMAL2] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PORTAL_CHANGESCENE1] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PORTAL_CHANGESCENEFINAL] = true;

	matrix[COLLIDER_DEATH][COLLIDER_SUELO] = true;
	matrix[COLLIDER_DEATH][COLLIDER_LIMIT] = true;
	matrix[COLLIDER_DEATH][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_DEATH][COLLIDER_DEATH] = false;
	matrix[COLLIDER_DEATH][COLLIDER_ACTION] = false;
	matrix[COLLIDER_DEATH][COLLIDER_LIANA] = true;
	matrix[COLLIDER_DEATH][COLLIDER_CORRIENTE_AGUA] = true;
	matrix[COLLIDER_DEATH][COLLIDER_PORTAL_AGUA] = true;
	matrix[COLLIDER_DEATH][COLLIDER_PORTAL_FUEGO] = true;
	matrix[COLLIDER_DEATH][COLLIDER_PORTAL_PLANTA] = true;
	matrix[COLLIDER_DEATH][COLLIDER_PORTAL_HIELO] = true;
	matrix[COLLIDER_DEATH][COLLIDER_PORTAL_NORMAL1] = true;
	matrix[COLLIDER_DEATH][COLLIDER_PORTAL_NORMAL2] = true;
	matrix[COLLIDER_DEATH][COLLIDER_PORTAL_CHANGESCENE1] = true;
	matrix[COLLIDER_DEATH][COLLIDER_PORTAL_CHANGESCENEFINAL] = true;

	matrix[COLLIDER_DEATH_ENEMY][COLLIDER_SUELO] = true;
	matrix[COLLIDER_DEATH_ENEMY][COLLIDER_LIMIT] = true;
	matrix[COLLIDER_DEATH_ENEMY][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_DEATH_ENEMY][COLLIDER_DEATH] = false;
	matrix[COLLIDER_DEATH_ENEMY][COLLIDER_ACTION] = false;
	matrix[COLLIDER_DEATH_ENEMY][COLLIDER_LIANA] = true;
	matrix[COLLIDER_DEATH_ENEMY][COLLIDER_CORRIENTE_AGUA] = true;
	matrix[COLLIDER_DEATH_ENEMY][COLLIDER_PORTAL_AGUA] = true;
	matrix[COLLIDER_DEATH_ENEMY][COLLIDER_PORTAL_FUEGO] = true;
	matrix[COLLIDER_DEATH_ENEMY][COLLIDER_PORTAL_PLANTA] = true;
	matrix[COLLIDER_DEATH_ENEMY][COLLIDER_PORTAL_HIELO] = true;
	matrix[COLLIDER_DEATH_ENEMY][COLLIDER_PORTAL_NORMAL1] = true;
	matrix[COLLIDER_DEATH_ENEMY][COLLIDER_PORTAL_NORMAL2] = true;
	matrix[COLLIDER_DEATH_ENEMY][COLLIDER_PORTAL_CHANGESCENE1] = true;
	matrix[COLLIDER_DEATH_ENEMY][COLLIDER_PORTAL_CHANGESCENEFINAL] = true;

	matrix[COLLIDER_ACTION][COLLIDER_LIMIT] = true;
	matrix[COLLIDER_ACTION][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_ACTION][COLLIDER_DEATH] = true;
	matrix[COLLIDER_ACTION][COLLIDER_ACTION] = false;

	name.create("collision");
}

// Destructor
j1Collision::~j1Collision()
{}

bool j1Collision::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr && colliders[i]->to_delete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	// Calculate collisions
	Collider* c1;
	Collider* c2;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if (colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// avoid checking collisions already checked
		for (uint k = i + 1; k < MAX_COLLIDERS; ++k)
		{
			// skip empty colliders
			if (colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if (c1->CheckCollision(c2->rect) == true)
			{
				if (matrix[c1->type][c2->type] && c1->callback)
					c1->callback->OnCollision(c1, c2);

				if (matrix[c2->type][c1->type] && c2->callback)
					c2->callback->OnCollision(c2, c1);
			}
		}
	}

	return true;
}


bool j1Collision::Update()
{
	DebugDraw();
	return true;
}

void j1Collision::DebugDraw()
{

	if (App->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN)
		debug = !debug;

	if (debug == false)
		return;

	Uint8 alpha = 80;
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
			continue;

		switch (colliders[i]->type)
		{
		case COLLIDER_NONE: // white
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;
		case COLLIDER_LIMIT: // blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			break;
		case COLLIDER_MOVECAM_RIGHT: // blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			break;
		case COLLIDER_MOVECAM_LEFT: // blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			break;
		case COLLIDER_CHECK_ENEMY: // blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 100, alpha);
			break;
		case COLLIDER_PLAYER: // green
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
			break;
		case COLLIDER_LIANA: // green
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
			break;
		case COLLIDER_TO_KILL_ENEMY: // green
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
			break;
		case COLLIDER_DEATH: // red
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;
		case COLLIDER_DEATH_ENEMY: // red
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;
		case COLLIDER_ACTION: // yellow
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
			break;
		case COLLIDER_SUELO: //yellow
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
			break;
		case COLLIDER_PORTAL_AGUA: // blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			break;
		case COLLIDER_PORTAL_FUEGO: // magenta
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
			break;
		case COLLIDER_PORTAL_HIELO: //yellow
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
			break;
		case COLLIDER_PORTAL_PLANTA: //yellow
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
			break;
		case COLLIDER_CHECKPOINT_SCENE: //blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			break;
		case COLLIDER_PORTAL_NORMAL1: //blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			break;
		case COLLIDER_PORTAL_NORMAL2: //blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			break;
		case COLLIDER_PORTAL_CHANGESCENE1: //magenta
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
			break;
		case COLLIDER_PORTAL_CHANGESCENEFINAL: //magenta
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
			break;
		case COLLIDER_CAMERA_LLEFT: //magenta
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
			break;
		case COLLIDER_CAMERA_LRIGHT: //magenta
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
			break;
		case COLLIDER_CORRIENTE_AGUA: //magenta
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
			break;
		case COLLIDER_CAMERA: //blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			break;
		}
	}
}

// Called before quitting
bool j1Collision::CleanUp()
{
	
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if ((colliders[i] != nullptr) && (colliders[i]->type != COLLIDER_PLAYER) && (colliders[i]->type != COLLIDER_CAMERA) && (colliders[i]->type != COLLIDER_CAMERA_LLEFT) && (colliders[i]->type != COLLIDER_CAMERA_LRIGHT) && (colliders[i]->type != COLLIDER_DEATH_ENEMY) && (colliders[i]->type != COLLIDER_CHECK_ENEMY) && (colliders[i]->type != COLLIDER_TO_KILL_ENEMY))
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

// Called before quitting
bool j1Collision::CleanUpEnemies()
{
	int count = 0;
	while (App->entities->entities_list.At(count) != nullptr) {

		int k = 1;

		if (App->entities->entities_list.At(count)->data->type != EntityType::PLAYER)
		{
			App->entities->DestroyEntity(App->entities->entities_list.At(count)->data);
		}
		count++;
	}

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if ((colliders[i] != nullptr) && ((colliders[i]->type == COLLIDER_CHECK_ENEMY) || (colliders[i]->type == COLLIDER_DEATH_ENEMY) || (colliders[i]->type == COLLIDER_CHECK_ENEMY)))
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* j1Collision::AddCollider(SDL_Rect rect, COLLIDER_TYPE type, j1Module* callback)
{
	Collider* ret = nullptr;
	bool candocal = true;

	for (uint j = 1; j < MAX_COLLIDERS; ++j)
	{
		if (colliders[j] != nullptr) {
			if ((colliders[j]->rect.x == rect.x) && (colliders[j]->rect.y == rect.y) && (colliders[j]->rect.w == rect.w) && (colliders[j]->rect.h == rect.h)) {
				candocal = false;
			}
		}
	}

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
			
		if (colliders[i] == nullptr)
		{
			if (candocal == true) {
				ret = colliders[i] = new Collider(rect, type, callback);
				break;
			}
		}
	}
	return ret;
}

bool j1Collision::CleanBackMapPlayer(int x)
{
	for (int k = 0; k < MAX_COLLIDERS; ++k)
	{
		if (colliders[k] != nullptr) {
			if (colliders[k]->rect.x <= x) {
				delete colliders[k];
				colliders[k] = nullptr;
			}
		}
	}
	return true;
}


// -----------------------------------------------------

bool Collider::CheckCollision(const SDL_Rect& r) const
{
	return !(r.x + r.w<rect.x || r.x>rect.x + rect.w || r.y + r.h<rect.y || r.y>rect.y + rect.h);
}



void Collider::SetPos(int x, int y) {
	rect.x = x;
	rect.y = y;
}