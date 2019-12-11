#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1EntityManager.h"
#include "j1Map.h"
#include "j1App.h"
#include "j1Player.h"
#include "j1Collision.h"
#include "j1Scene.h"
#include "../Game/Brofiler/Brofiler.h"
#include <math.h>

int gidcollgroundone;
int gidcollgroundtwo;
int gidcollgroundthree;
int gidcollgroundwall;
int gidcollgroundiceone;
int gidcollgroundicetwo;
int gidcollgroundicethree;
int gidcollgroundicewall;
int gidcolldeath;
int gidcollliana;
int gidcorrienteagua;
int gidpathfinding;
int gidenemyliana;
int gidenemyfire;
int gidenemywatter;
int gidenemyice;
int gidplayer;

j1Map::j1Map() : j1Module(), map_loaded(false)
{
	name.create("map");
}

// Destructor
j1Map::~j1Map()
{}

// Called before render is available
bool j1Map::Awake(pugi::xml_node& config)
{
	LOG("Loading Map Parser");
	bool ret = true;

	folder.create(config.child("folder").child_value());
	gidcollgroundone = config.child("colliderground").attribute("one").as_int();
	gidcollgroundtwo = config.child("colliderground").attribute("two").as_int();
	gidcollgroundthree = config.child("colliderground").attribute("three").as_int();
	gidcollgroundwall = config.child("colliderground").attribute("wall").as_int();
	gidcollgroundiceone = config.child("collidergroundice").attribute("one").as_int();
	gidcollgroundicetwo = config.child("collidergroundice").attribute("two").as_int();
	gidcollgroundicethree = config.child("collidergroundice").attribute("three").as_int();
	gidcollgroundicewall = config.child("collidergroundice").attribute("wall").as_int();
	gidcollliana = config.child("othercolliders").attribute("liana").as_int();
	gidcolldeath = config.child("othercolliders").attribute("death").as_int();
	gidcorrienteagua = config.child("othercolliders").attribute("corriente").as_int();
	gidpathfinding = config.child("pathfinding").attribute("id").as_int();
	gidenemyliana = config.child("enemies").attribute("liana").as_int();
	gidenemyfire = config.child("enemies").attribute("fire").as_int();
	gidenemywatter = config.child("enemies").attribute("watter").as_int();
	gidenemyice = config.child("enemies").attribute("ice").as_int();
	gidplayer= config.child("enemies").attribute("player").as_int();

	return ret;
}

void j1Map::Draw()
{
	if (map_loaded == false)
		return;

	p2List_item<MapLayer*>* item = data.layers.start;
	p2List_item<TileSet*>* coord_tileset = data.tilesets.start;
	int number_of_layers = data.layers.count();
	int count_layers = 0;
	for (; item != NULL; item = item->next)
	{
		count_layers++;
		MapLayer* layer = item->data;

		//if(layer->properties.Get("Nodraw") != 0)
			//continue;

		for (int y = 0; y < data.height; ++y)
		{
			for (int x = 0; x < data.width; ++x)
			{
				int tile_id = layer->Get(x, y);
				if (tile_id > 0)
				{
					if ((x * 32 < App->entities->player->position.x + 400) && (x * 32 > App->entities->player->position.x - 550)) {
						TileSet* tileset = GetTilesetFromTileId(tile_id);

						SDL_Rect r = tileset->GetTileRect(tile_id);
						iPoint pos = MapToWorld(x, y);
						SDL_Rect rect;

						//CreateEnemies(tile_id);

						if (tile_id == gidcollgroundone) {//1 NORMAL
							App->collision->AddCollider({ pos.x,pos.y + 12,32,20 }, COLLIDER_SUELO, this);
						}
						if (tile_id == gidcollgroundtwo) {//2 NORMAL
							App->collision->AddCollider({ pos.x,pos.y + 12,32,52 }, COLLIDER_SUELO, this);
						}
						if (tile_id == gidcollgroundthree) {//3 NORMAL
							App->collision->AddCollider({ pos.x,pos.y + 12,32,84 }, COLLIDER_SUELO, this);
						}
						if (tile_id == gidcollgroundwall) { //W NORMAL
							App->collision->AddCollider({ pos.x,pos.y + 12,32,188 }, COLLIDER_SUELO, this);
						}
						if (tile_id == gidcollliana) { //W HIELO
							App->collision->AddCollider({ pos.x,pos.y,32,32 }, COLLIDER_LIANA, this);
						}
						if (tile_id == gidcorrienteagua) { //CORRIENTE AGUA
							App->collision->AddCollider({ pos.x,pos.y,32,32 }, COLLIDER_CORRIENTE_AGUA, this);
						}
						if (tile_id == gidcolldeath) {
							App->collision->AddCollider({ pos.x,pos.y + 10,32,32 }, COLLIDER_DEATH, this);
						}

						if (tile_id != gidpathfinding && tile_id != gidenemyfire && tile_id != gidenemywatter && tile_id != gidenemyice && tile_id != gidenemyliana && tile_id != gidplayer) {
							if (App->scene->changelevel == false) {
								if (App->entities->player->dimensionnormal == true) {
									if (count_layers < 6) {
										if (count_layers == 0 || count_layers == 1) {
											App->render->Blit(tileset->texture, pos.x, pos.y, &r, 0.96f, 0, NULL, NULL, SDL_FLIP_NONE);
										}
										else {
											App->render->Blit(tileset->texture, pos.x, pos.y, &r, 1.0f, 0, NULL, NULL, SDL_FLIP_NONE);
										}
									}
								}
								if ((App->entities->player->dimensionplanta == true) || (App->entities->player->dimensionhielo == true)) {
									if (count_layers >= 6) {
										if (count_layers == 6 || count_layers == 8 || count_layers == 9) {
											App->render->Blit(tileset->texture, pos.x, pos.y, &r, 0.96f, 0, NULL, NULL, SDL_FLIP_NONE);
										}
										else {
											App->render->Blit(tileset->texture, pos.x, pos.y, &r, 1.0f, 0, NULL, NULL, SDL_FLIP_NONE);
										}
									}
								}
							}

							if (App->scene->changelevel == true) {
								if (App->entities->player->dimensionnormal == true) {
									if (count_layers < 5) {
										if (count_layers == 0) {
											App->render->Blit(tileset->texture, pos.x, pos.y, &r, 0.96f, 0, NULL, NULL, SDL_FLIP_NONE);
										}
										else {
											App->render->Blit(tileset->texture, pos.x, pos.y, &r, 1.0f, 0, NULL, NULL, SDL_FLIP_NONE);
										}
									}
								}
								if ((App->entities->player->dimensionfuego == true) || (App->entities->player->dimensionagua == true)) {
									if (count_layers >= 5) {
										if (count_layers == 5) {
											App->render->Blit(tileset->texture, pos.x, pos.y, &r, 0.96f, 0, NULL, NULL, SDL_FLIP_NONE);
										}
										else {
											App->render->Blit(tileset->texture, pos.x, pos.y, &r, 1.0f, 0, NULL, NULL, SDL_FLIP_NONE);
										}
									}
								}
							}

						}
					}
					if (x * 32 < App->entities->player->position.x - 400) {
						App->collision->CleanBackMapPlayer(x * 32);
					}
				}
			}
		}
	}
}

int Properties::Get(const char* value, int default_value) const
{
	p2List_item<Property*>* item = list.start;

	while (item)
	{
		if (item->data->name == value)
			return item->data->value;
		item = item->next;
	}

	return default_value;
}

TileSet* j1Map::GetTilesetFromTileId(int id) const
{
	p2List_item<TileSet*>* item = data.tilesets.start;
	TileSet* set = item->data;

	while (item)
	{
		if (id < item->data->firstgid)
		{
			set = item->prev->data;
			break;
		}
		set = item->data;
		item = item->next;
	}

	return set;
}

iPoint j1Map::MapToWorld(int x, int y) const
{
	iPoint ret;

	if (data.type == MAPTYPE_ORTHOGONAL)
	{
		ret.x = x * data.tile_width;
		ret.y = y * data.tile_height;
	}
	else if (data.type == MAPTYPE_ISOMETRIC)
	{
		ret.x = (x - y) * (data.tile_width * 0.5f);
		ret.y = (x + y) * (data.tile_height * 0.5f);
	}
	else
	{
		LOG("Unknown map type");
		ret.x = x; ret.y = y;
	}

	return ret;
}

iPoint j1Map::WorldToMap(int x, int y) const
{
	iPoint ret(0, 0);

	if (data.type == MAPTYPE_ORTHOGONAL)
	{
		ret.x = x / data.tile_width;
		ret.y = y / data.tile_height;
	}
	else if (data.type == MAPTYPE_ISOMETRIC)
	{

		float half_width = data.tile_width * 0.5f;
		float half_height = data.tile_height * 0.5f;
		ret.x = int((x / half_width + y / half_height) / 2) - 1;
		ret.y = int((y / half_height - (x / half_width)) / 2);
	}
	else
	{
		LOG("Unknown map type");
		ret.x = x; ret.y = y;
	}

	return ret;
}

SDL_Rect TileSet::GetTileRect(int id) const
{
	int relative_id = id - firstgid;
	SDL_Rect rect;
	rect.w = tile_width;
	rect.h = tile_height;
	rect.x = margin + ((rect.w + spacing) * (relative_id % num_tiles_width));
	rect.y = margin + ((rect.h + spacing) * (relative_id / num_tiles_width));
	return rect;
}

// Called before quitting
bool j1Map::CleanUp()
{
	LOG("Unloading map");

	// Remove all tilesets
	p2List_item<TileSet*>* item;
	item = data.tilesets.start;

	while (item != NULL)
	{
		RELEASE(item->data);
		item = item->next;
	}
	data.tilesets.clear();

	// Remove all layers
	p2List_item<MapLayer*>* item2;
	item2 = data.layers.start;

	while (item2 != NULL)
	{
		RELEASE(item2->data);
		item2 = item2->next;
	}
	data.layers.clear();

	// Clean up the pugui tree
	map_file.reset();
	App->collision->CleanUp();
	return true;
}

// Load new map
bool j1Map::Load(const char* file_name)
{
	bool ret = true;
	p2SString tmp("%s%s", folder.GetString(), file_name);

	pugi::xml_parse_result result = map_file.load_file(tmp.GetString());

	if (result == NULL)
	{
		LOG("Could not load map xml file %s. pugi error: %s", file_name, result.description());
		ret = false;
	}

	// Load general info ----------------------------------------------
	if (ret == true)
	{
		ret = LoadMap();
	}

	// Load all tilesets info ----------------------------------------------
	pugi::xml_node tileset;
	for (tileset = map_file.child("map").child("tileset"); tileset && ret; tileset = tileset.next_sibling("tileset"))
	{
		TileSet* set = new TileSet();

		if (ret == true)
		{
			ret = LoadTilesetDetails(tileset, set);
		}

		if (ret == true)
		{
			ret = LoadTilesetImage(tileset, set);
		}

		data.tilesets.add(set);
	}

	// Load layer info ----------------------------------------------
	pugi::xml_node layer;
	for (layer = map_file.child("map").child("layer"); layer && ret; layer = layer.next_sibling("layer"))
	{
		MapLayer* lay = new MapLayer();

		ret = LoadLayer(layer, lay);

		if (ret == true)
			data.layers.add(lay);
	}

	if (ret == true)
	{
		LOG("Successfully parsed map XML file: %s", file_name);
		LOG("width: %d height: %d", data.width, data.height);
		LOG("tile_width: %d tile_height: %d", data.tile_width, data.tile_height);

		p2List_item<TileSet*>* item = data.tilesets.start;
		while (item != NULL)
		{
			TileSet* s = item->data;
			LOG("Tileset ----");
			LOG("name: %s firstgid: %d", s->name.GetString(), s->firstgid);
			LOG("tile width: %d tile height: %d", s->tile_width, s->tile_height);
			LOG("spacing: %d margin: %d", s->spacing, s->margin);
			item = item->next;
		}

		p2List_item<MapLayer*>* item_layer = data.layers.start;
		while (item_layer != NULL)
		{
			MapLayer* l = item_layer->data;
			LOG("Layer ----");
			LOG("name: %s", l->name.GetString());
			LOG("tile width: %d tile height: %d", l->width, l->height);
			item_layer = item_layer->next;
		}
	}

	map_loaded = ret;

	return ret;
}

// Load map general properties
bool j1Map::LoadMap()
{
	bool ret = true;
	pugi::xml_node map = map_file.child("map");

	if (map == NULL)
	{
		LOG("Error parsing map xml file: Cannot find 'map' tag.");
		ret = false;
	}
	else
	{
		data.width = map.attribute("width").as_int();
		data.height = map.attribute("height").as_int();
		data.tile_width = map.attribute("tilewidth").as_int();
		data.tile_height = map.attribute("tileheight").as_int();
		p2SString bg_color(map.attribute("backgroundcolor").as_string());

		data.background_color.r = 0;
		data.background_color.g = 0;
		data.background_color.b = 0;
		data.background_color.a = 0;

		if (bg_color.Length() > 0)
		{
			p2SString red, green, blue;
			bg_color.SubString(1, 2, red);
			bg_color.SubString(3, 4, green);
			bg_color.SubString(5, 6, blue);

			int v = 0;

			sscanf_s(red.GetString(), "%x", &v);
			if (v >= 0 && v <= 255) data.background_color.r = v;

			sscanf_s(green.GetString(), "%x", &v);
			if (v >= 0 && v <= 255) data.background_color.g = v;

			sscanf_s(blue.GetString(), "%x", &v);
			if (v >= 0 && v <= 255) data.background_color.b = v;
		}

		p2SString orientation(map.attribute("orientation").as_string());

		if (orientation == "orthogonal")
		{
			data.type = MAPTYPE_ORTHOGONAL;
		}
		else if (orientation == "isometric")
		{
			data.type = MAPTYPE_ISOMETRIC;
		}
		else if (orientation == "staggered")
		{
			data.type = MAPTYPE_STAGGERED;
		}
		else
		{
			data.type = MAPTYPE_UNKNOWN;
		}
	}

	return ret;
}

bool j1Map::LoadTilesetDetails(pugi::xml_node& tileset_node, TileSet* set)
{
	bool ret = true;
	set->name.create(tileset_node.attribute("name").as_string());
	set->firstgid = tileset_node.attribute("firstgid").as_int();
	set->tile_width = tileset_node.attribute("tilewidth").as_int();
	set->tile_height = tileset_node.attribute("tileheight").as_int();
	set->margin = tileset_node.attribute("margin").as_int();
	set->spacing = tileset_node.attribute("spacing").as_int();
	pugi::xml_node offset = tileset_node.child("tileoffset");

	if (offset != NULL)
	{
		set->offset_x = offset.attribute("x").as_int();
		set->offset_y = offset.attribute("y").as_int();
	}
	else
	{
		set->offset_x = 0;
		set->offset_y = 0;
	}

	return ret;
}

bool j1Map::LoadTilesetImage(pugi::xml_node& tileset_node, TileSet* set)
{
	bool ret = true;
	pugi::xml_node image = tileset_node.child("image");

	if (image == NULL)
	{
		LOG("Error parsing tileset xml file: Cannot find 'image' tag.");
		ret = false;
	}
	else
	{
		set->texture = App->tex->Load(PATH(folder.GetString(), image.attribute("source").as_string()));
		int w, h;
		SDL_QueryTexture(set->texture, NULL, NULL, &w, &h);
		set->tex_width = image.attribute("width").as_int();

		if (set->tex_width <= 0)
		{
			set->tex_width = w;
		}

		set->tex_height = image.attribute("height").as_int();

		if (set->tex_height <= 0)
		{
			set->tex_height = h;
		}

		set->num_tiles_width = set->tex_width / set->tile_width;
		set->num_tiles_height = set->tex_height / set->tile_height;
	}

	return ret;
}

bool j1Map::LoadLayer(pugi::xml_node& node, MapLayer* layer)
{
	bool ret = true;

	layer->name = node.attribute("name").as_string();
	layer->width = node.attribute("width").as_int();
	layer->height = node.attribute("height").as_int();
	LoadProperties(node, layer->properties);
	pugi::xml_node layer_data = node.child("data");

	if (layer_data == NULL)
	{
		LOG("Error parsing map xml file: Cannot find 'layer/data' tag.");
		ret = false;
		RELEASE(layer);
	}
	else
	{
		layer->data = new uint[layer->width*layer->height];
		memset(layer->data, 0, layer->width*layer->height);

		int i = 0;
		for (pugi::xml_node tile = layer_data.child("tile"); tile; tile = tile.next_sibling("tile"))
		{
			layer->data[i++] = tile.attribute("gid").as_int(0);
		}
	}

	return ret;
}

// Load a group of properties from a node and fill a list with it
bool j1Map::LoadProperties(pugi::xml_node& node, Properties& properties)
{
	bool ret = false;

	pugi::xml_node data = node.child("properties");

	if (data != NULL)
	{
		pugi::xml_node prop;

		for (prop = data.child("property"); prop; prop = prop.next_sibling("property"))
		{
			Properties::Property* p = new Properties::Property();

			p->name = prop.attribute("name").as_string();
			p->value = prop.attribute("value").as_int();

			properties.list.add(p);
		}
	}

	return ret;
}

bool j1Map::CreateWalkabilityMap(int& width, int& height, uchar** buffer) const
{
	bool ret = false;
	p2List_item<MapLayer*>* item;
	item = data.layers.start;

	for (item = data.layers.start; item != NULL; item = item->next)
	{
		MapLayer* layer = item->data;

		if (layer->properties.Get("Navigation", 0) == 0)
			continue;

		uchar* map = new uchar[layer->width*layer->height];
		memset(map, 1, layer->width*layer->height);

		for (int y = 0; y < data.height; ++y)
		{
			for (int x = 0; x < data.width; ++x)
			{
				int i = (y*layer->width) + x;

				int tile_id = layer->Get(x, y);
				TileSet* tileset = (tile_id > 0) ? GetTilesetFromTileId(tile_id) : NULL;

				if (tileset != NULL)
				{
					map[i] = (tile_id - tileset->firstgid) > 0 ? 0 : 1;
					/*TileType* ts = tileset->GetTileType(tile_id);
					if(ts != NULL)
					{
						map[i] = ts->properties.Get("walkable", 1);
					}*/
				}
			}
		}

		*buffer = map;
		width = data.width;
		height = data.height;
		ret = true;

		break;
	}

	return ret;
}

void j1Map::CreateEnemies(int gid, float x, float y) {
	if (gid == gidenemyliana) {
		App->entities->CreateEntity(EntityType::ENEMY_LIANA, x, y);
	}
	if (gid == gidenemyfire) {
		App->entities->CreateEntity(EntityType::ENEMY_FIRE, x, y);
	}
	if (gid == gidenemywatter) {
		App->entities->CreateEntity(EntityType::ENEMY_WATTER, x, y);
	}
	if (gid == gidenemyice) {
		App->entities->CreateEntity(EntityType::ENEMY_ICE, x, y);
	}
	/*
	if (gid == gidplayer) {
		App->entities->CreateEntity(EntityType::PLAYER, x, y);
	}
	*/
}

void j1Map::DoEnemies()
{
	if (map_loaded == false)
		return;

	p2List_item<MapLayer*>* item = data.layers.start;

	for (; item != NULL; item = item->next)
	{
		MapLayer* layer = item->data;
		for (int y = 0; y < data.height; ++y)
		{
			for (int x = 0; x < data.width; ++x)
			{
				int tile_id = layer->Get(x, y);
				if (tile_id > 0)
				{
					CreateEnemies(tile_id, x*32, y*32);
				}
			}
		}
	}
}