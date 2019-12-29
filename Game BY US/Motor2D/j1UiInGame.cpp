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
#include "UIText.h"
#include "j1Menu.h"

j1UiInGame::j1UiInGame() : j1Module()
{

	/////HEART ANIMATION//////
	heart_anim.PushBack({ 0, 0, 20, 20 });
	heart_anim.speed = 0.01f;

	/////HEART ANIMATION//////
	gray_heart_anim.PushBack({ 0, 20, 20, 20 });
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

// Called before the first frame
bool j1UiInGame::Start()
{
	coinstextrect.x = 10;
	coinstextrect.y = 5;
	coinsrect.x = 15;
	coinsrect.y = 15;

	ui_graphics = App->tex->Load("textures/UI/UiInGame.png");

	CreateFirstWorldCoins();

	guielement_coinstext = App->guimanager->CreateUIElement(false, GuiType::TEXT, guielement_coinstext, coinsrect, coinsrect, "0");
	guielement_coinstexttext=App->guimanager->CreateUIElement(false, GuiType::TEXT, guielement_coinstexttext, coinstextrect, coinstextrect, "COINS");

	return true;
}

// Called each loop iteration
bool j1UiInGame::PreUpdate()
{
	guielement_coinstext->RefreshText(stringo.create("%i", App->entities->player->num_coins));
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

	
	if (App->entities->player->lifes <= 0) ret = false;

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

void j1UiInGame::CreateFirstWorldCoins()
{
	
	//NORMAL WORLD 1
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 200, 190), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 290, 180), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 322, 148), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 354, 116), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 386, 100), number_coins++);
							 
							 
	//PLANT WORLD 1			 
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 575, 90), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 605, 80), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 630, 100), number_coins++);

	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 695, 130), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 710, 100), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 725, 130), number_coins++);

	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 800, 100), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 900, 140), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 860, 50), number_coins++);

	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 1010, 40), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 1050, 150), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 1150, 100), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 1250, 30), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 1215, 170), number_coins++);

	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 1270, 100), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 1300, 100), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 1330, 100), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 1360, 100), number_coins++);

	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 1275, 200), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 1300, 180), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 1325, 200), number_coins++);

	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 1415, 230), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 1415, 200), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 1415, 170), number_coins++);
							  
	//NORMAL WORLD 2		  
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 1555, 110), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 1575, 85), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 1605, 85), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 1625, 110), number_coins++);

	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 1705, 80), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 1720, 45), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 1750, 25), number_coins++);

	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 1765, 170), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 1735, 170), number_coins++);

	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 1890, 35), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 1860, 35), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 1860, 65), number_coins++);
							   
	//ICE WORLD 2			   
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 2000, 35), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 2025, 15), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 2045, 45), number_coins++);

	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 2050, 80), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 2080, 80), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 2110, 80), number_coins++);

	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 2050, 190), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 2080, 190), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 2110, 190), number_coins++);

	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 2250, 180), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 2275, 150), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 2300, 130), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 2330, 120), number_coins++);

	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 2440, 210), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 2472, 170), number_coins++);

	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 2565, 210), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 2600, 100), number_coins++);

	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 2695, 210), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 2725, 140), number_coins++);

	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 2820, 200), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 2845, 170), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 2870, 150), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 2900, 140), number_coins++);

	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 2956, 168), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 2981, 138), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 3006, 118), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 3036, 108), number_coins++);

	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 3112, 200), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 3142, 200), number_coins++);

	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 3175, 135), number_coins++);

	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 3267, 100), number_coins++);

	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 3330, 200), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 3360, 200), number_coins++);

	//NORMAL WORLD 3		  
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 3440, 200), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 3470, 200), number_coins++);

	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 3556, 200), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 3588, 168), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 3620, 136), number_coins++);

	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 3716, 136), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 3748, 136), number_coins++);

	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 3880, 136), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 3910, 136), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 3940, 136), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 3970, 136), number_coins++);
	
}

void j1UiInGame::CreateSecondWorldCoins()
{
	/*
	//NORMAL WORLD 1
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 200, 200), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 232, 168), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 264, 136), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 296, 104), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 326, 104), number_coins++);

	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 395, 130), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 395, 160), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 395, 190), number_coins++);

	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 490, 150), number_coins++);

	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 600, 200), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 625, 175), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 655, 155), number_coins++);

	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 700, 200), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 725, 175), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 755, 155), number_coins++);

	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 860, 200), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 875, 170), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 895, 155), number_coins++);

	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 1000, 170), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 1000, 140), number_coins++);

	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 1120, 55), number_coins++);

	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 1235, 80), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 1260, 55), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 1280, 85), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 1290, 120), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 1295, 160), number_coins++);

	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 1370, 200), number_coins++);

	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 1470, 155), number_coins++);

	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 1705, 145), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 1735, 145), number_coins++);

	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 1705, 235), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 1735, 235), number_coins++);

	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 1835, 235), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 1865, 235), number_coins++);

	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 1927, 110), number_coins++);

	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 2025, 110), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 2055, 110), number_coins++);

	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 2025, 235), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 2055, 235), number_coins++);

	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 2140, 200), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 2170, 200), number_coins++);

	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 2240, 70), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 2270, 40), number_coins++);

	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 2395, 150), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 2425, 150), number_coins++);

	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 2500, 65), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 2500, 35), number_coins++);

	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 2600, 35), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 2600, 65), number_coins++);

	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 2745, 90), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 2775, 90), number_coins++);

	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 2745, 217), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 2775, 217), number_coins++);

	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 2920, 217), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 2950, 217), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 2920, 90), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 2950, 90), number_coins++);

	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 3095, 90), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 3125, 90), number_coins++);

	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 3095, 217), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 3125, 217), number_coins++);

	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 3270, 90), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 3270, 217), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 3300, 90), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 3300, 217), number_coins++);

	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 3427, 135), number_coins++);

	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 3580, 170), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 3605, 145), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 3630, 170), number_coins++);

	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 3700, 170), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 3725, 145), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 3750, 130), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 3775, 145), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 3800, 170), number_coins++);

	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 3930, 230), number_coins++);
	coins_array.Insert((Coins*)App->entities->CreateEntity(EntityType::COINS, 3960, 230), number_coins++);
*/
}

bool j1UiInGame::CleanUpCoinsArray() {

	for (int i = coins_array.Count() - 1; i >= 0; i--)
	{
		coins_array[i]->CleanUp();
	}
	coins_array.Clear();
	number_coins = 0;

	return true;
}