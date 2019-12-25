#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Collision.h"
#include "j1PathFinding.h"
#include "j1Player.h"
#include "j1EntityManager.h"
#include "j1Map.h"
#include "EnemyAigua.h"
#include "EnemyLiana.h"
#include "EnemyIce.h"
#include "EnemyFire.h"
#include "j1Scene.h"
#include "j1UiInGame.h"
#include "j1Menu.h"

j1Scene::j1Scene() : j1Module()
{
	
	/////PLANT PORTAL ANIMATION//////
	plant_portal.PushBack({ 0, 64, 50, 64 });
	plant_portal.PushBack({ 50, 64, 50, 64 });
	plant_portal.PushBack({ 100, 64, 50, 64 });
	plant_portal.PushBack({ 50, 64, 50, 64 });
	plant_portal.speed = 0.08f;

	/////SNOW PORTAL ANIMATION//////
	ice_portal.PushBack({ 0, 128, 50, 64 });
	ice_portal.PushBack({ 50, 128, 50, 64 });
	ice_portal.PushBack({ 100, 128, 50, 64 });
	ice_portal.PushBack({ 50, 128, 50, 64 });
	ice_portal.speed = 0.08f;

	/////NORMAL PORTAL ANIMATION//////
	normal_portal.PushBack({ 0, 256, 50, 64 });
	normal_portal.PushBack({ 50, 256, 50, 64 });
	normal_portal.PushBack({ 100, 256, 50, 64 });
	normal_portal.PushBack({ 50, 256, 50, 64 });
	normal_portal.speed = 0.08f;

	/////FINAL PORTAL ANIMATION//////
	final_portal.PushBack({ 0, 320, 50, 64 });
	final_portal.PushBack({ 50, 320, 50, 64 });
	final_portal.PushBack({ 100, 320, 50, 64 });
	final_portal.PushBack({ 50, 320, 50, 64 });
	final_portal.speed = 0.08f;

	/////FIRE PORTAL ANIMATION//////
	fire_portal.PushBack({ 0, 0, 50, 64 });
	fire_portal.PushBack({ 50, 0, 50, 64 });
	fire_portal.PushBack({ 100, 0, 50, 64 });
	fire_portal.PushBack({ 50, 0, 50, 64 });
	fire_portal.speed = 0.08f;

	/////WATTER PORTAL ANIMATION//////
	watter_portal.PushBack({ 0, 192, 50, 64 });
	watter_portal.PushBack({ 50, 192, 50, 64 });
	watter_portal.PushBack({ 100, 192, 50, 64 });
	watter_portal.PushBack({ 50, 192, 50, 64 });
	watter_portal.speed = 0.08f;

	/////FIRE RING ANIMATION//////
	fire_ring_anim.PushBack({ 150, 0, 55, 80 });
	fire_ring_anim.PushBack({ 150, 80, 55, 80 });
	fire_ring_anim.speed = 0.08f;

	/////WATTER WAVE ANIMATION//////
	watter_wave_anim.PushBack({ 150, 160, 96, 64 });
	watter_wave_anim.PushBack({ 150, 224, 96, 64 });
	watter_wave_anim.PushBack({ 150, 288, 96, 64 });
	watter_wave_anim.speed = 0.08f;

	/////PLANT PORTAL ANIMATION//////
	checkpoint_flag.PushBack({ 0, 0, 25, 26 });
	checkpoint_flag.PushBack({ 0, 26, 25, 26 });
	checkpoint_flag.speed = 0.08f;


	name.create("scene");

}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");
	bool ret = true;

	/////// SCENE 1 PORTALS ///////
	plantportalx = config.child("plantportal").attribute("x").as_int();
	plantportaly = config.child("plantportal").attribute("y").as_int();
	iceportalx = config.child("iceportal").attribute("x").as_int();
	iceportaly = config.child("iceportal").attribute("y").as_int();
	finalportalx = config.child("finalportal").attribute("x").as_int();
	finalportaly = config.child("finalportal").attribute("y").as_int();
	normal1portalx = config.child("normalportal1").attribute("x").as_int();
	normal1portaly = config.child("normalportal1").attribute("y").as_int();
	normal2portalx = config.child("normalportal2").attribute("x").as_int();
	normal2portaly = config.child("normalportal2").attribute("y").as_int();

	/////// SCENE 2 PORTALS ///////
	fireportalx = config.child("fireportal").attribute("x").as_int();
	fireportaly = config.child("fireportal").attribute("y").as_int();
	watterportalx = config.child("watterportal").attribute("x").as_int();
	watterportaly = config.child("watterportal").attribute("y").as_int();
	normal3portalx = config.child("normalportal3").attribute("x").as_int();
	normal3portaly = config.child("normalportal3").attribute("y").as_int();
	normal4portalx = config.child("normalportal4").attribute("x").as_int();
	normal4portaly = config.child("normalportal4").attribute("y").as_int();
	endportalx = config.child("endportal").attribute("x").as_int();
	endportaly = config.child("endportal").attribute("y").as_int();
	firering1x = config.child("firering1").attribute("x").as_int();
	firering1y = config.child("firering1").attribute("y").as_int();
	firering2x = config.child("firering2").attribute("x").as_int();
	firering2y = config.child("firering2").attribute("y").as_int();
	firering3x = config.child("firering3").attribute("x").as_int();
	firering3y = config.child("firering3").attribute("y").as_int();
	firering4x = config.child("firering4").attribute("x").as_int();
	firering4y = config.child("firering4").attribute("y").as_int();
	firering5x = config.child("firering5").attribute("x").as_int();
	firering5y = config.child("firering5").attribute("y").as_int();
	firering6x = config.child("firering6").attribute("x").as_int();
	firering6y = config.child("firering6").attribute("y").as_int();

	checkpointscene1x = config.child("checkpointscene1").attribute("x").as_int();
	checkpointscene1y = config.child("checkpointscene1").attribute("y").as_int();
	checkpointscene2x = config.child("checkpointscene2").attribute("x").as_int();
	checkpointscene2y = config.child("checkpointscene2").attribute("y").as_int();

	/////// PLAYER AND CAMERA VARIABLES ///////
	camlimitleft = config.child("camlimits").attribute("left").as_int();
	camlimitright = config.child("camlimits").attribute("right").as_int();
	positionplayerinitx = config.child("positionplayerinit").attribute("x").as_int();
	positionplayerinity = config.child("positionplayerinit").attribute("y").as_int();
	//App->player->position.x = positionplayerinitx;
	//App->player->position.y = positionplayerinity;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	App->map->Load("Scene01.tmx");
	objects_graphics = App->tex->Load("textures/Objects.png");
	checkpoint_done_graphics = App->tex->Load("textures/CheckPoint_NONE.png");
	checkpoint_none_graphics = App->tex->Load("textures/CheckPoint_DONE.png");

	///// CAMERA COLLISIONS /////
	cameralimit01 = App->collision->AddCollider({ 0,0,20,350 }, COLLIDER_CAMERA, this);
	cameralimit02 = App->collision->AddCollider({ 380,0,20,350 }, COLLIDER_CAMERA, this);
	camleftlim = App->collision->AddCollider({ camlimitleft,0,20,350 }, COLLIDER_CAMERA_LLEFT, this);
	camrightlim = App->collision->AddCollider({ camlimitright,0,20,350 }, COLLIDER_CAMERA_LRIGHT, this);

	App->SaveGame();
	App->entities->player->dimensionhielo = false;
	App->audio->PlayMusic("audio/music/back.ogg");

	//Pathinding
	if (App->map->Load("Scene01.tmx") == true)
	{
		int w, h;
		uchar* data = NULL;
		if (App->map->CreateWalkabilityMap(w, h, &data))
			App->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);
	}

	pathfinding_tex = App->tex->Load("maps/path2.png");


	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{


	if (changelevel == false && donecollidersscene1 == false) {
		//App->SaveGame();
		///// PORTAL COLLLIDERS SCENE 1/////
		plantportal = App->collision->AddCollider({ plantportalx + 30,plantportaly,20,64 }, COLLIDER_PORTAL_PLANTA, this);
		normalportal01 = App->collision->AddCollider({ normal1portalx + 30,normal1portaly,20,64 }, COLLIDER_PORTAL_NORMAL1, this);
		iceportal = App->collision->AddCollider({ iceportalx + 30,iceportaly,20,64 }, COLLIDER_PORTAL_HIELO, this);
		normalportal02 = App->collision->AddCollider({ normal2portalx + 30,normal2portaly,20,64 }, COLLIDER_PORTAL_NORMAL1, this);
		finalportal = App->collision->AddCollider({ finalportalx + 30,finalportaly,20,64 }, COLLIDER_PORTAL_CHANGESCENE1, this);

		checkpointcol_scene1 = App->collision->AddCollider({ checkpointscene1x,checkpointscene1y,25,26 }, COLLIDER_CHECKPOINT_SCENE, this);
		App->map->DoEnemies();
		donecollidersscene1 = true;

}

	if (changelevel == true && donecollidersscene2 == false) {
		//App->SaveGame();
		///// PORTAL COLLLIDERS SCENE 2/////
		firering11 = App->collision->AddCollider({ firering1x -17,firering1y+23,15,10 }, COLLIDER_DEATH, this);
		firering11 = App->collision->AddCollider({ firering1x -80,firering1y + 23,10,10 }, COLLIDER_DEATH, this);
		firering21 = App->collision->AddCollider({ firering2x + 23,firering2y,3,5 }, COLLIDER_DEATH, this);
		firering21 = App->collision->AddCollider({ firering2x + 23,firering2y +75,3,5 }, COLLIDER_DEATH, this);
		firering31 = App->collision->AddCollider({ firering3x + 23,firering3y,3,5 }, COLLIDER_DEATH, this);
		firering31 = App->collision->AddCollider({ firering3x + 23,firering3y + 75,3,5 }, COLLIDER_DEATH, this);
		firering41 = App->collision->AddCollider({ firering4x + 23,firering4y,3,5 }, COLLIDER_DEATH, this);
		firering41 = App->collision->AddCollider({ firering4x + 23,firering4y + 75,3,5 }, COLLIDER_DEATH, this);
		firering51 = App->collision->AddCollider({ firering5x - 17,firering5y + 23,10,10 }, COLLIDER_DEATH, this);
		firering51 = App->collision->AddCollider({ firering5x - 80,firering5y + 23,10,10 }, COLLIDER_DEATH, this);
		firering61 = App->collision->AddCollider({ firering6x + 23,firering6y,3,5 }, COLLIDER_DEATH, this);
		firering61 = App->collision->AddCollider({ firering6x + 23,firering6y + 75,3,5 }, COLLIDER_DEATH, this);
		fireportal = App->collision->AddCollider({ fireportalx + 30,fireportaly,20,64 }, COLLIDER_PORTAL_FUEGO, this);
		normalportal03 = App->collision->AddCollider({ normal3portalx + 30,normal3portaly,20,64 }, COLLIDER_PORTAL_NORMAL2, this);
		watterportal = App->collision->AddCollider({ watterportalx + 30,watterportaly,20,64 }, COLLIDER_PORTAL_AGUA, this);
		normalportal04 = App->collision->AddCollider({ normal4portalx + 30,normal4portaly,20,64 }, COLLIDER_PORTAL_NORMAL2, this);
		endportal = App->collision->AddCollider({ endportalx + 30,endportaly,20,64 }, COLLIDER_PORTAL_CHANGESCENEFINAL, this);

		checkpointcol_scene2 = App->collision->AddCollider({ checkpointscene2x,checkpointscene2y,25,26 }, COLLIDER_CHECKPOINT_SCENE, this);
		App->map->DoEnemies();
		donecollidersscene2 = true;

	}
	if (App->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
		App->LoadGame();

	if (App->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN)
		ResetCurrentLevel(changelevel);

	if (App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
		App->SaveGame();

	if (App->input->GetKey(SDL_SCANCODE_F11) == KEY_DOWN) {
		if (App->fpsCapON == true) {
			App->fpsCapON = false;
		}
		else {
			App->fpsCapON = true;
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		App->entities->player->ChangeToLevel1();

	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
		App->entities->player->ChangeToLevel2();

	// debug pathfing ------------------
	static iPoint origin;
	static bool origin_selected = false;

	int x, y;
	App->input->GetMousePosition(x, y);
	iPoint p = App->render->ScreenToWorld(x, y);
	p = App->map->WorldToMap(p.x, p.y);

	/*
	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		if (origin_selected == true)
		{
			App->pathfinding->CreatePath(origin, p);
			origin_selected = false;
		}
		else
		{
			origin = p;
			origin_selected = true;
		}
	}
	*/
	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	if ((App->entities->player->dimensionhielo)&&(App->entities->player->ice_right == true)&& (App->entities->player->right == false)) {
		cameraxinvert += App->entities->player->speed_player_ice*1.12;
	}
	App->map->Draw();
	if (App->entities->player->position.x > cameraxinvert + 200) {
		if ((((App->entities->player->stop_right == false)) && (cameralimit02->CheckCollision(camrightlim->rect) == false))|| (App->entities->player->ice_right == true)) {
			cameraxinvert = App->entities->entities_list.start->data->position.x - 200;
		}
	}

	App->render->camera.x = -2 * cameraxinvert;
	cameralimit01->rect.x = cameraxinvert;
	cameralimit02->rect.x = cameraxinvert + 380;

	int x, y;
	App->input->GetMousePosition(x, y);
	iPoint map_coordinates = App->map->WorldToMap(x - App->render->camera.x, y - App->render->camera.y);

	// Debug pathfinding ------------------------------
	//int x, y;
	if (App->collision->debug == true) {
		App->input->GetMousePosition(x, y);
		iPoint p = App->render->ScreenToWorld(x, y);
		p = App->map->WorldToMap(p.x, p.y);
		p = App->map->MapToWorld(p.x, p.y);

		App->render->Blit(pathfinding_tex, p.x, p.y, NULL, 1.0f, 0, INT_MAX, INT_MAX, SDL_FLIP_NONE);

		const p2DynArray<iPoint>* path = App->pathfinding->GetLastPath();

		for (uint i = 0; i < path->Count(); ++i)
		{
			iPoint pos = App->map->MapToWorld(path->At(i)->x, path->At(i)->y);
			App->render->Blit(pathfinding_tex, pos.x, pos.y, NULL, 1.0f, 0, INT_MAX, INT_MAX, SDL_FLIP_NONE);
		}
	}


	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;

	if (App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN) {
		App->scene->active = false;
		App->entities->active = false;
		App->uiingame->active = false;
		App->collision->CleanUp();
		App->menu->active = true;
	}

	if (changelevel == false) {
		App->render->Blit(objects_graphics, plantportalx, plantportaly, &(plant_portal.GetCurrentFrame()), 1.0f, 0, 0, 0, flip);
		App->render->Blit(objects_graphics, normal1portalx, normal1portaly, &(normal_portal.GetCurrentFrame()), 1.0f, 0, 0, 0, flip);
		App->render->Blit(objects_graphics, iceportalx, iceportaly, &(ice_portal.GetCurrentFrame()), 1.0f, 0, 0, 0, flip);
		App->render->Blit(objects_graphics, normal2portalx, normal2portaly, &(normal_portal.GetCurrentFrame()), 1.0f, 0, 0, 0, flip);
		App->render->Blit(objects_graphics, finalportalx, finalportaly, &(final_portal.GetCurrentFrame()), 1.0f, 0, 0, 0, flip);
		if (justtouchcheckpoint == true) {
		App->render->Blit(checkpoint_none_graphics, checkpointscene1x, checkpointscene1y, &(checkpoint_flag.GetCurrentFrame()), 1.0f, 0, 0, 0, SDL_FLIP_NONE);
		}
		if (justtouchcheckpoint == false) {
			App->render->Blit(checkpoint_done_graphics, checkpointscene1x, checkpointscene1y, &(checkpoint_flag.GetCurrentFrame()), 1.0f, 0, 0, 0, SDL_FLIP_NONE);
		}
	}
	else {
		if (App->entities->player->dimensionfuego) {
			App->render->Blit(objects_graphics, firering1x, firering1y, &(fire_ring_anim.GetCurrentFrame()), 1.0f, 90, 0, 0, flip);
			App->render->Blit(objects_graphics, firering2x, firering2y, &(fire_ring_anim.GetCurrentFrame()), 1.0f, 0, 0, 0, flip);
			App->render->Blit(objects_graphics, firering3x, firering3y, &(fire_ring_anim.GetCurrentFrame()), 1.0f, 0, 0, 0, flip);
			App->render->Blit(objects_graphics, firering4x, firering4y, &(fire_ring_anim.GetCurrentFrame()), 1.0f, 0, 0, 0, flip);
			App->render->Blit(objects_graphics, firering5x, firering5y, &(fire_ring_anim.GetCurrentFrame()), 1.0f, 90, 0, 0, flip);
			App->render->Blit(objects_graphics, firering6x, firering6y, &(fire_ring_anim.GetCurrentFrame()), 1.0f, 0, 0, 0, flip);
		}
		if (App->entities->player->dimensionagua) {
			App->render->Blit(objects_graphics, 2464, 192, &(watter_wave_anim.GetCurrentFrame()), 1.0f, 180, 0, 0, flip);
			App->render->Blit(objects_graphics, 2816, 256, &(watter_wave_anim.GetCurrentFrame()), 1.0f, 180, 0, 0, flip);
			App->render->Blit(objects_graphics, 2816, 128, &(watter_wave_anim.GetCurrentFrame()), 1.0f, 180, 0, 0, flip);
			App->render->Blit(objects_graphics, 3168, 256, &(watter_wave_anim.GetCurrentFrame()), 1.0f, 180, 0, 0, flip);
			App->render->Blit(objects_graphics, 3168, 128, &(watter_wave_anim.GetCurrentFrame()), 1.0f, 180, 0, 0, flip);
		}
		App->render->Blit(objects_graphics, fireportalx, fireportaly, &(fire_portal.GetCurrentFrame()), 1.0f, 0, 0, 0, flip);
		App->render->Blit(objects_graphics, normal3portalx, normal3portaly, &(normal_portal.GetCurrentFrame()), 1.0f, 0, 0, 0, flip);
		App->render->Blit(objects_graphics, watterportalx, watterportaly, &(watter_portal.GetCurrentFrame()), 1.0f, 0, 0, 0, flip);
		App->render->Blit(objects_graphics, normal4portalx, normal4portaly, &(normal_portal.GetCurrentFrame()), 1.0f, 0, 0, 0, flip);
		App->render->Blit(objects_graphics, endportalx, endportaly, &(final_portal.GetCurrentFrame()), 1.0f, 0, 0, 0, flip);
		if (justtouchcheckpoint == true) {
			App->render->Blit(checkpoint_none_graphics, checkpointscene2x, checkpointscene2y, &(checkpoint_flag.GetCurrentFrame()), 1.0f, 0, 0, 0, SDL_FLIP_NONE);
		}
		if (justtouchcheckpoint == false) {
			App->render->Blit(checkpoint_done_graphics, checkpointscene2x, checkpointscene2y, &(checkpoint_flag.GetCurrentFrame()), 1.0f, 0, 0, 0, SDL_FLIP_NONE);
		}
	}


	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = App->entities->player->exitgame = false;

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");
	App->map->CleanUp();
	App->tex->UnLoad(objects_graphics);
	return true;
}

bool j1Scene::Save(pugi::xml_node& data) const
{

	data.append_child("scene");
	data.child("scene").append_attribute("camx") = cameraxinvert;
	data.child("scene").append_attribute("real_camx") = App->render->camera.x;
	data.child("scene").append_attribute("actualscene") = changelevel;

	return true;
}

bool j1Scene::Load(pugi::xml_node& data)
{
	bool changeyet = false;
	App->render->camera.x = data.child("scene").attribute("real_camx").as_float();
	cameraxinvert = data.child("scene").attribute("camx").as_float();
	if (changelevel != data.child("scene").attribute("actualscene").as_bool()) {
		if (changelevel == false) {
			App->entities->player->ChangeToLevel2();
			changelevel = data.child("scene").attribute("actualscene").as_bool();
			changeyet = true;
		}
		if (changelevel == true) {
			if (changeyet == false) {
				App->entities->player->ChangeToLevel1();
				changelevel = data.child("scene").attribute("actualscene").as_bool();
			}
		}
	}

	cameralimit01->rect.x = cameraxinvert;
	cameralimit02->rect.x = cameraxinvert + 380;
	return true;
}

void j1Scene::ResetCurrentLevel(bool current_level)
{
	if (current_level == true) {
		App->entities->player->ChangeToLevel2();
	}
	else if (current_level == false) {
		App->entities->player->ChangeToLevel1();
	}
}

void j1Scene::OnCollision(Collider* player, Collider* object)
{
	if (player->type == COLLIDER_PLAYER) {
		if (object->type == COLLIDER_CHECKPOINT_SCENE) {
			App->scene->justtouchcheckpoint = true;
			if (App->scene->justtouchcheckpoint == true) {
				App->SaveGame();
			}
		}
	}
}
