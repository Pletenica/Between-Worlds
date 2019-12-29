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
#include "Coins.h"
#include "p2Log.h"

#include "SDL/include/SDL_timer.h"
#include "../Game/Brofiler/Brofiler.h"

Coins::Coins() :j1Entity(EntityType::COINS)
{
	type = EntityType::COINS;


	/////IDLE ANIMATION//////
	idle.PushBack({ 0, 40, 20, 20 });
	idle.PushBack({ 20, 40, 20, 20 });
	idle.PushBack({ 40, 40, 20, 20 });
	idle.PushBack({ 60, 40, 20, 20 });
	idle.PushBack({ 40, 40, 20, 20 });
	idle.PushBack({ 20, 40, 20, 20 });
	idle.speed = 0.07f;

	texture = App->tex->Load("textures/UI/UiInGame.png");
	//body = 
	coinsound= App->audio->LoadFx("audio/fx/CoinSound.wav");

	name.create("Coins");
}

Coins::~Coins()
{
	this->body->to_delete = true;
	App->tex->UnLoad(this->texture);
	have_to_destroy = true;
}


bool Coins::PostUpdate() {
	BROFILER_CATEGORY("EnemiesPreUpdate", Profiler::Color::Chartreuse)

	App->render->Blit(texture, (int)position.x, (int)position.y, &(idle.GetCurrentFrame()), 1.0f, 0, 0, 0, flip);
	isincoltoplayer = false;
	//OnCollisionCoin(body, App->entities->player->body);
	return true;
}


void Coins::OnCollision(Collider* coin, Collider* player) {

	BROFILER_CATEGORY("PlayerOnCollision", Profiler::Color::MediumAquaMarine)
	if (coin->type == COLLIDER_COINS) {
		if (player->type == COLLIDER_PLAYER && have_to_destroy==false) {
			App->audio->PlayFx(coinsound, -1);
			App->entities->player->num_coins++;
			Coins::~Coins();
		}
	}
}