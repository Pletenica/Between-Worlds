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
			App->render->camera.x += 3;
			movecamleft->rect.x -= 1;
			movecamright->rect.x -= 1;
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) {
		if (App->player->body->CheckCollision(movecamright->rect) == true) {
			App->render->camera.x -= 3;
			movecamright->rect.x += 1;
			movecamleft->rect.x += 1;
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
