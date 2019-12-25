#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Player.h"
#include "j1EntityManager.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1UiInGame.h"
#include "j1Scene.h"
#include "j1GuiManager.h"
#include "j1GuiElement.h"
#include "UIImage.h"
#include "j1Menu.h"

j1UiInGame::j1UiInGame() : j1Module()
{

	/////HEART ANIMATION//////
	heart_anim.PushBack({ 0, 0, 20, 20 });
	//heart_anim.PushBack({ 20, 0, 20, 20 });
	//heart_anim.PushBack({ 40, 0, 20, 20 });
	heart_anim.speed = 0.01f;

	/////HEART ANIMATION//////
	gray_heart_anim.PushBack({ 0, 20, 20, 20 });
	//gray_heart_anim.PushBack({ 20, 20, 20, 20 });
	//gray_heart_anim.PushBack({ 40, 20, 20, 20 });
	gray_heart_anim.speed = 0.01f;

	name.create("uiingame");
}

// Destructor
j1UiInGame::~j1UiInGame()
{}

// Called before render is available
bool j1UiInGame::Awake(pugi::xml_node& config)
{
	LOG("Loading Menu");
	bool ret = true;

	return ret;
}
SDL_Rect rect;
j1GuiElement* guielement;
// Called before the first frame
bool j1UiInGame::Start()
{
	rect.x = 100;
	rect.y = 100;

	ui_graphics = App->tex->Load("textures/UI/UiInGame.png");

	App->guimanager->CreateUIElement(true, GuiType::TEXT, guielement, rect, rect, "Roger me la chupa crack.");

	return true;
}

// Called each loop iteration
bool j1UiInGame::PreUpdate()
{

	return true;
}

// Called each loop iteration
bool j1UiInGame::Update(float dt)
{


	return true;
}

// Called each loop iteration
bool j1UiInGame::PostUpdate()
{
	bool ret = true;

	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = App->entities->player->exitgame = false;

	
	for (int i = 0; i < 3; i++) {
		App->render->Blit(ui_graphics, 330 + i * 20, 5, &(gray_heart_anim.GetCurrentFrame()), 0.0f, 0, 0, 0, SDL_FLIP_NONE);
	}

	for (int i = 0; i < App->entities->player->lifes; i++) {
		App->render->Blit(ui_graphics, 330 + i * 20, 5, &(heart_anim.GetCurrentFrame()), 0.0f, 0, 0, 0, SDL_FLIP_NONE);
	}
	return ret;
}

// Called before quitting
bool j1UiInGame::CleanUp()
{
	LOG("Freeing scene");
	App->tex->UnLoad(ui_graphics);
	return true;
}

bool j1UiInGame::Save(pugi::xml_node& data) const
{
	return true;
}

bool j1UiInGame::Load(pugi::xml_node& data)
{
	return true;
}