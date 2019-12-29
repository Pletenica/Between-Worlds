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
	textdonerect.x = 60;
	textdonerect.y = 300;

	startbuttonrect.x = 25;
	startbuttonrect.y = 80;
	startbuttonrect.w = 85;
	startbuttonrect.h = 26;
	startbuttonrect1.x = 187;
	startbuttonrect1.y = 0;
	startbuttonrect1.w = 85;
	startbuttonrect1.h = 26;
	startbuttonrect2.x = 187;
	startbuttonrect2.y = 26;
	startbuttonrect2.w = 85;
	startbuttonrect2.h = 26;
	startbuttonrect3.x = 187;
	startbuttonrect3.y = 52;
	startbuttonrect3.w = 85;
	startbuttonrect3.h = 26;

	continuebuttonrect.x = 25;
	continuebuttonrect.y = 115;
	continuebuttonrect.w = 130;
	continuebuttonrect.h = 26;
	continuebuttonrect1.x = 463;
	continuebuttonrect1.y = 0;
	continuebuttonrect1.w = 133;
	continuebuttonrect1.h = 26;
	continuebuttonrect2.x = 463;
	continuebuttonrect2.y = 26;
	continuebuttonrect2.w = 133;
	continuebuttonrect2.h = 26;
	continuebuttonrect3.x = 463;
	continuebuttonrect3.y = 52;
	continuebuttonrect3.w = 133;
	continuebuttonrect3.h = 26;


	exitbuttonrect.x = 25;
	exitbuttonrect.y = 185;
	exitbuttonrect.w = 61;
	exitbuttonrect.h = 26;
	exitbuttonrect1.x = 272;
	exitbuttonrect1.y = 0;
	exitbuttonrect1.w = 61;
	exitbuttonrect1.h = 26;
	exitbuttonrect2.x = 272;
	exitbuttonrect2.y = 26;
	exitbuttonrect2.w = 61;
	exitbuttonrect2.h = 26;
	exitbuttonrect3.x = 272;
	exitbuttonrect3.y = 52;
	exitbuttonrect3.w = 61;
	exitbuttonrect3.h = 26;

	settingsbuttonrect.x = 25;
	settingsbuttonrect.y = 150;
	settingsbuttonrect.w = 130;
	settingsbuttonrect.h = 26;
	settingsbuttonrect1.x = 333;
	settingsbuttonrect1.y = 0;
	settingsbuttonrect1.w = 130;
	settingsbuttonrect1.h = 26;
	settingsbuttonrect2.x = 333;
	settingsbuttonrect2.y = 26;
	settingsbuttonrect2.w = 130;
	settingsbuttonrect2.h = 26;
	settingsbuttonrect3.x = 333;
	settingsbuttonrect3.y = 52;
	settingsbuttonrect3.w = 130;
	settingsbuttonrect3.h = 26;

	githubbuttonrect.x = 357;
	githubbuttonrect.y = 25;
	githubbuttonrect.w = 37;
	githubbuttonrect.h = 37;
	githubbuttonrect1.x = 187;
	githubbuttonrect1.y = 78;
	githubbuttonrect1.w = 37;
	githubbuttonrect1.h = 37;
	githubbuttonrect2.x = 224;
	githubbuttonrect2.y = 78;
	githubbuttonrect2.w = 37;
	githubbuttonrect2.h = 37;
	githubbuttonrect3.x = 261;
	githubbuttonrect3.y = 78;
	githubbuttonrect3.w = 37;
	githubbuttonrect3.h = 37;

	creditsbuttonrect.x = 327;
	creditsbuttonrect.y = 5;
	creditsbuttonrect.w = 68;
	creditsbuttonrect.h = 16;
	creditsbuttonrect1.x = 298;
	creditsbuttonrect1.y = 78;
	creditsbuttonrect1.w = 68;
	creditsbuttonrect1.h = 16;
	creditsbuttonrect2.x = 298;
	creditsbuttonrect2.y = 94;
	creditsbuttonrect2.w = 68;
	creditsbuttonrect2.h = 16;
	creditsbuttonrect3.x = 298;
	creditsbuttonrect3.y = 110;
	creditsbuttonrect3.w = 68;
	creditsbuttonrect3.h = 16;

	menubackgroundrect.x = 0;
	menubackgroundrect.y = 0;
	menubackgroundrect.w = 400;
	menubackgroundrect.h = 320;
	

	/////MAIN LOGO ANIMATION//////
	logo_anim.PushBack({ 0, 0, 187, 55 });
	logo_anim.PushBack({ 0, 55, 187, 55 });
	logo_anim.PushBack({ 0, 110, 187, 55 });
	logo_anim.PushBack({ 0, 55, 187, 55 });
	logo_anim.speed = 0.2f;

	idle_player.PushBack({ 400, 0, 400, 320 });
	idle_player.PushBack({ 800, 0, 400, 320 });
	idle_player.PushBack({ 1200, 0, 400, 320 });
	idle_player.speed = 0.1f;

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
	menu_normal_back_graphics = App->tex->Load("textures/UI/MenuBackgroundNormal.png");
	menu_plant_back_graphics = App->tex->Load("textures/UI/MenuBackgroundPlant.png");
	menu_ice_back_graphics = App->tex->Load("textures/UI/MenuBackgroundIce.png");
	menu_fire_back_graphics = App->tex->Load("textures/UI/MenuBackgroundFire.png");
	menu_watter_back_graphics = App->tex->Load("textures/UI/MenuBackgroundWatter.png");

	guielement_startbutton =App->guimanager->CreateUIElement(true, GuiType::BUTTON, guielement_startbutton, startbuttonrect, startbuttonrect1,"", startbuttonrect2, startbuttonrect3);
	guielement_continuebutton = App->guimanager->CreateUIElement(true, GuiType::BUTTON, guielement_continuebutton, continuebuttonrect, continuebuttonrect1, "", continuebuttonrect2, continuebuttonrect3);
	guielement_settingsbutton = App->guimanager->CreateUIElement(true, GuiType::BUTTON, guielement_settingsbutton, settingsbuttonrect, settingsbuttonrect1, "", settingsbuttonrect2, settingsbuttonrect3);
	guielement_exitbutton = App->guimanager->CreateUIElement(true, GuiType::BUTTON, guielement_exitbutton, exitbuttonrect, exitbuttonrect1, "", exitbuttonrect2, exitbuttonrect3);

	guielement_githubbutton = App->guimanager->CreateUIElement(true, GuiType::BUTTON, guielement_githubbutton, githubbuttonrect, githubbuttonrect1, "", githubbuttonrect2, githubbuttonrect3);
	guielement_creditsbutton = App->guimanager->CreateUIElement(true, GuiType::BUTTON, guielement_creditsbutton, creditsbuttonrect, creditsbuttonrect1, "", creditsbuttonrect2, creditsbuttonrect3);


	App->guimanager->CreateUIElement(true, GuiType::TEXT, guielement_textdone, textdonerect, textdonerect, "Game done by Roger Pérez Romera & Josep Sànchez Arbona");
	menu_current_back_graphics = menu_normal_back_graphics;
	return true;
}

// Called each loop iteration
bool j1Menu::PreUpdate()
{
	if (guielement_startbutton->over == true) menu_current_back_graphics = menu_plant_back_graphics;
	else if (guielement_continuebutton->over == true) menu_current_back_graphics = menu_ice_back_graphics;
	else if (guielement_settingsbutton->over == true) menu_current_back_graphics = menu_fire_back_graphics;
	else if (guielement_exitbutton->over == true) menu_current_back_graphics = menu_watter_back_graphics;
	else menu_current_back_graphics = menu_normal_back_graphics;
	
	return true;
}

// Called each loop iteration
bool j1Menu::Update(float dt)
{
	if (guielement_startbutton->pushed == true) {
		App->scene->active = true;
		App->entities->active = true;
		App->uiingame->active = true;
		App->menu->active = false;
		isinmenu = false;
	}

	if (guielement_exitbutton->pushed == true) {
		return false;
	}

	if (guielement_githubbutton->pushed == true) {
		ShellExecuteA(NULL, "open", "https://pletenica.github.io/Between-Worlds/", NULL , NULL , SW_SHOWNORMAL);
	}

	App->render->Blit(menu_current_back_graphics, 0, 0, &menubackgroundrect, 1.0f, 0, 0, 0, SDL_FLIP_NONE);

	App->render->Blit(menu_graphics, 15, 10, &(logo_anim.GetCurrentFrame()), 1.0f, 0, 0, 0, SDL_FLIP_NONE);
	App->render->Blit(menu_current_back_graphics, 0, 0, &(idle_player.GetCurrentFrame()), 1.0f, 0, 0, 0, SDL_FLIP_NONE);
	return true;
}

// Called each loop iteration
bool j1Menu::PostUpdate()
{
	bool ret = true;


	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = App->entities->player->exitgame = false;


	
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