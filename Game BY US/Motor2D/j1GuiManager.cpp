#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1GuiManager.h"

j1GuiManager::j1GuiManager() : j1Module()
{
	name.create("GuiManager");
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
	return true;
}

// Called after all Updates
bool j1GuiManager::PostUpdate()
{
	return true;
}

// Called before quitting
bool j1GuiManager::CleanUp()
{
	LOG("Freeing GUI");

	return true;
}

// const getter for atlas
const SDL_Texture* j1GuiManager::GetAtlas() const
{
	return atlas;
}