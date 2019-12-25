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
#include "j1Menu.h"
#include "j1Scene.h"
#include "j1UiInGame.h"
#include "j1GuiManager.h"
#include "j1GuiElement.h"
#include "UIImage.h"

j1Menu::j1Menu() : j1Module()
{

	/////MAIN LOGO ANIMATION//////
	logo_anim.PushBack({ 0, 0, 187, 55 });
	logo_anim.PushBack({ 0, 55, 187, 55 });
	logo_anim.PushBack({ 0, 110, 187, 55 });
	logo_anim.PushBack({ 0, 55, 187, 55 });
	logo_anim.speed = 0.2f;

	name.create("menu");
}

// Destructor
j1Menu::~j1Menu()
{}

// Called before render is available
bool j1Menu::Awake(pugi::xml_node& config)
{
	LOG("Loading Menu");
	bool ret = true;

	return ret;
}



// Called before the first frame
bool j1Menu::Start()
{
	menu_graphics = App->tex->Load("textures/UI/Menu.png");
	textdonerect.x = 60;
	textdonerect.y = 300;

	App->guimanager->CreateUIElement(true, GuiType::TEXT, guielement_textdone, textdonerect, textdonerect, "Game done by Roger Pérez Romera & Josep Sànchez Arbona");

	return true;
}

// Called each loop iteration
bool j1Menu::PreUpdate()
{

	return true;
}

// Called each loop iteration
bool j1Menu::Update(float dt)
{


	return true;
}

// Called each loop iteration
bool j1Menu::PostUpdate()
{
	bool ret = true;

	if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN) {
		App->scene->active = true;
		App->entities->active = true;
		App->uiingame->active = true;
		App->menu->active = false;
		isinmenu = false;
	}


	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = App->entities->player->exitgame = false;

	App->render->Blit(menu_graphics, 15, 10, &(logo_anim.GetCurrentFrame()), 1.0f, 0, 0, 0, SDL_FLIP_NONE);
	
	return ret;
}

// Called before quitting
bool j1Menu::CleanUp()
{
	LOG("Freeing scene");
	App->tex->UnLoad(menu_graphics);
	return true;
}

bool j1Menu::Save(pugi::xml_node& data) const
{
	return true;
}

bool j1Menu::Load(pugi::xml_node& data)
{
	return true;
}