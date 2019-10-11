#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Collision.h"
#include "j1Player.h"
#include "j1Map.h"
#include "j1Scene.h"

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

	name.create("scene");

}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	App->map->Load("Scene01.tmx");
	movecamright = App->collision->AddCollider({ 200,0,20,350 }, COLLIDER_MOVECAM_RIGHT, this);
	movecamleft = App->collision->AddCollider({ 100,0,20,350 }, COLLIDER_MOVECAM_LEFT, this);
	camleftlim = App->collision->AddCollider({ -20,0,20,350 }, COLLIDER_CAMERA_LLEFT, this);
	camrightlim = App->collision->AddCollider({ 4064,0,20,350 }, COLLIDER_CAMERA_LRIGHT, this);
	cameralimit01 = App->collision->AddCollider({ 0,0,20,350 }, COLLIDER_CAMERA, this);
	cameralimit02 = App->collision->AddCollider({ 380,0,20,350 }, COLLIDER_CAMERA, this);
	objects_graphics = App->tex->Load("textures/Objects.png");
	plantportal = App->collision->AddCollider({ 440,100,50,64 }, COLLIDER_PORTAL_PLANTA, this);
	normalportal01 = App->collision->AddCollider({ 1455,100,50,64 }, COLLIDER_PORTAL_NORMAL1, this);
	iceportal = App->collision->AddCollider({ 1920,5,50,64 }, COLLIDER_PORTAL_HIELO, this);
	iceportal = App->collision->AddCollider({ 3390,165,40,64 }, COLLIDER_PORTAL_NORMAL1, this);
	finalportal = App->collision->AddCollider({ 4000,100,40,64 }, COLLIDER_PORTAL_CHANGESCENE1, this);

	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	if(App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		App->LoadGame();

	if(App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		App->SaveGame();

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) {
		if (App->player->body->CheckCollision(movecamleft->rect) == true) {
			if (App->scene->cameralimit01->CheckCollision(camleftlim->rect) == false) {
				App->render->camera.x += App->player->speed_player*3;
				movecamleft->rect.x -= App->player->speed_player;
				movecamright->rect.x -= App->player->speed_player;
				cameralimit01->rect.x -= App->player->speed_player;
				cameralimit02->rect.x -= App->player->speed_player;
			}
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) {
		if (App->player->body->CheckCollision(movecamright->rect) == true) {
			if (App->scene->cameralimit02->CheckCollision(camrightlim->rect) == false) {
				App->render->camera.x -= App->player->speed_player*3;
				movecamright->rect.x += App->player->speed_player;
				movecamleft->rect.x += App->player->speed_player;
				cameralimit01->rect.x += App->player->speed_player;
				cameralimit02->rect.x += App->player->speed_player;
			}
		}
	}

	//App->render->Blit(img, 0, 0);
	App->map->Draw();

	p2SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d",
					App->map->data.width, App->map->data.height,
					App->map->data.tile_width, App->map->data.tile_height,
					App->map->data.tilesets.count());

	//HOMEWORK App->win->SetTitle(title.GetString());
	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;


	App->render->Blit(objects_graphics, 440, 100, &(plant_portal.GetCurrentFrame()), 1.0f, 0, 0, 0, flip);
	App->render->Blit(objects_graphics, 1455, 100, &(normal_portal.GetCurrentFrame()), 1.0f, 0, 0, 0, flip);
	App->render->Blit(objects_graphics, 1920, 5, &(ice_portal.GetCurrentFrame()), 1.0f, 0, 0, 0, flip);
	App->render->Blit(objects_graphics, 3380, 165, &(normal_portal.GetCurrentFrame()), 1.0f, 0, 0, 0, flip);
	App->render->Blit(objects_graphics, 4010, 100, &(final_portal.GetCurrentFrame()), 1.0f, 0, 0, 0, flip);

	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");
	App->map->CleanUp();
	return true;
}

