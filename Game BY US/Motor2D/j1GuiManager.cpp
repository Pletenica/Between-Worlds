#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Window.h"
#include "j1GuiManager.h"

#include "UIText.h"
#include "UIWindow.h"
#include "UIButton.h"
#include "UIImage.h"

j1GuiManager::j1GuiManager() : j1Module()
{
	name.create("gui");
}

// Destructor
j1GuiManager::~j1GuiManager()
{}

// Called before render is available
bool j1GuiManager::Awake(pugi::xml_node& conf)
{
	LOG("Loading GUI atlas");
	bool ret = true;

	atlas_file_name = conf.child("atlas").attribute("file").as_string("");

	return ret;
}

// Called before the first frame
bool j1GuiManager::Start()
{
	atlas = App->tex->Load(atlas_file_name.GetString());

	return true;
}

// Update all guis
bool j1GuiManager::PreUpdate()
{
	bool mouse = false;
	int count = 0;
	if (App->input->GetMouseButtonDown(1) == KEY_DOWN || App->input->GetMouseButtonDown(1) == KEY_REPEAT) {
		for (int i = gui_element_list.count() - 1; i >= 0 && mouse == false; i--) {
			mouse = gui_element_list.At(i)->data->CheckMouse();
			if (mouse == true)count = i;
		}
	}
	if (mouse == true) {
		gui_element_list.At(count)->data->Move();
	}
	for (int i = 0; i < gui_element_list.count(); i++) {
		gui_element_list.At(i)->data->PreUpdate();
	}
	return true;
}

// Called after all Updates
bool j1GuiManager::PostUpdate()
{
	for (int i = 0; i < gui_element_list.count(); i++) {
		gui_element_list.At(i)->data->PostUpdate();
	}
	return true;
}

// Called before quitting
bool j1GuiManager::CleanUp()
{
	LOG("Freeing GUI");

	for (int i = gui_element_list.count() - 1; i >= 0; i--)
	{
		gui_element_list.At(i)->data->CleanUp();
		gui_element_list.del(gui_element_list.At(i));
	}
	gui_element_list.clear();
	return true;
}

// const getter for atlas
const SDL_Texture* j1GuiManager::GetAtlas() const
{
	return atlas;
}

// class Gui ---------------------------------------------------

j1GuiElement* j1GuiManager::CreateUIElement(GuiType type, j1GuiElement* p, SDL_Rect r, SDL_Rect sprite, p2SString str, SDL_Rect sprite2, SDL_Rect sprite3)
{
	j1GuiElement* ui;
	switch (type)
	{
	case GuiType::BUTTON:
		ui = new ButtonUI(GuiType::BUTTON, p, r, sprite, sprite2, sprite3, true);
		break;
	case GuiType::IMAGE:
		ui = new ImageUI(GuiType::IMAGE, p, r, sprite, true);
		break;
	case GuiType::WINDOW:
		ui = new WindowUI(GuiType::WINDOW, p, r, sprite, true);
		break;
	case GuiType::TEXT:
		ui = new TextUI(GuiType::TEXT, p, r, str, false);
		break;
	}
	gui_element_list.add(ui);
	return ui;
}

bool j1GuiManager::DeleteUIElement(j1GuiElement* ui) {
	int n = gui_element_list.find(ui);
	if (n == -1)return false;
	else
	{
		gui_element_list.At(n)->data->CleanUp();
		gui_element_list.del(gui_element_list.At(n));
		return true;
	}
}