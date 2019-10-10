#include "j1App.h"
#include "j1Textures.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Audio.h"
#include "j1Collision.h"
#include "j1Player.h"
#include "j1Scene.h"
#include "j1Objects.h"
#include "SDL/include/SDL_timer.h"

j1Objects::j1Objects()
{

	/////FIRE PORTAL ANIMATION//////
	fire_portal.PushBack({ 0, 0, 50, 64 });
	fire_portal.PushBack({ 50, 0, 50, 64 });
	fire_portal.PushBack({ 100, 0, 50, 64 });
	fire_portal.PushBack({ 50, 0, 50, 64 });
	fire_portal.speed = 0.008f;

	/////PLANT PORTAL ANIMATION//////
	plant_portal.PushBack({ 0, 64, 50, 64 });
	plant_portal.PushBack({ 50, 64, 50, 64 });
	plant_portal.PushBack({ 100, 64, 50, 64 });
	plant_portal.PushBack({ 50, 64, 50, 64 });
	plant_portal.speed = 0.008f;

	/////SNOW PORTAL ANIMATION//////
	ice_portal.PushBack({ 0, 128, 50, 64 });
	ice_portal.PushBack({ 50, 128, 50, 64 });
	ice_portal.PushBack({ 100, 128, 50, 64 });
	ice_portal.PushBack({ 50, 128, 50, 64 });
	ice_portal.speed = 0.008f;

	/////WATTER PORTAL ANIMATION//////
	watter_portal.PushBack({ 0, 192, 50, 64 });
	watter_portal.PushBack({ 50, 192, 50, 64 });
	watter_portal.PushBack({ 100, 192, 50, 64 });
	watter_portal.PushBack({ 50, 192, 50, 64 });
	watter_portal.speed = 0.008f;

	/////NORMAL PORTAL ANIMATION//////
	normal_portal.PushBack({ 0, 256, 50, 64 });
	normal_portal.PushBack({ 50, 256, 50, 64 });
	normal_portal.PushBack({ 100, 256, 50, 64 });
	normal_portal.PushBack({ 50, 256, 50, 64 });
	normal_portal.speed = 0.008f;

	/////FIRE RING ANIMATION//////
	fire_ring_portal.PushBack({ 150, 0, 55, 80 });
	fire_ring_portal.PushBack({ 150, 80, 55, 80 });
	fire_ring_portal.speed = 0.008f;
}

j1Objects::~j1Objects()
{}


// Load assets
bool j1Objects::Start()
{
	//// Load All CONDITIONS //// 
	position.x = 0;
	position.y = 0;

	//// Load All Graphics //// 
	objects_graphics = App->tex->Load("textures/Objects.png");
	plantportal = App->collision->AddCollider({ 70,200,50,64 }, COLLIDER_PORTAL_PLANTA, this);
	return true;
}

//Clean Up
bool j1Objects::CleanUp() {
	App->tex->UnLoad(objects_graphics);

	return true;
}


bool j1Objects::PreUpdate() {

	return true;
}


// Update: draw background
bool j1Objects::Update()
{

	return true;
}

bool j1Objects::PostUpdate() {

	App->render->Blit(objects_graphics, 70, 130, &(plant_portal.GetCurrentFrame()), 0.0f, 0, 0, 0, flip);

	return true;
}


void j1Objects::OnCollision(Collider* object, Collider* other) {

}