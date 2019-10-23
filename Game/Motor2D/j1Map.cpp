#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Map.h"
#include "j1Collision.h"
#include "j1Input.h"
#include "j1Window.h"
#include "j1Player.h"
#include "j1Scene.h"
//
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

	return ret;
}

void j1Map::Draw()
{
	if(map_loaded == false)
		return;

	bool ret = false;
	int number_of_layers = data.layers.count();
	p2List_item<MapLayer*>* coord_layer = data.layers.start;
	p2List_item<TileSet*>* coord_tileset = data.tilesets.start;

	// TODO 5: Prepare the loop to iterate all the tiles in a layer

	int colliderCounter = 0;
	for (int layer_counter = 0; layer_counter < number_of_layers; layer_counter++) {
		for (int i = 0; i < coord_layer->data->height; i++) {
			for (int j = 0; j < coord_layer->data->width; j++) {
				int n = coord_layer->data->Get(j, i);
				int gid = coord_layer->data->gid[n];
				//if ((j * 32  < App->player->position.x + 350) && (j*32 > App->player->position.x - 250)) {
					if (gid != 0) {
						while (ret == false) {
							if (coord_tileset->next != NULL && coord_tileset->next->data->firstgid <= gid) coord_tileset = coord_tileset->next;
							else if (coord_tileset->prev != NULL && coord_tileset->data->firstgid > gid)coord_tileset = coord_tileset->prev;
							else ret = true;
						}
						ret = false;
						SDL_Rect rect = coord_tileset->data->GetRect(coord_layer->data->gid[n]);
						int x = j;
						int y = i;
						Translate_Coord(&x, &y);
						
							if (gid == gidcollgroundone && collidersdone == false) {//1 NORMAL
								App->collision->AddCollider({ x,y + 12,32,20 }, COLLIDER_SUELO, this);
							}
							if (gid == gidcollgroundtwo && collidersdone == false) {//2 NORMAL
								App->collision->AddCollider({ x,y + 12,32,52 }, COLLIDER_SUELO, this);
							}
							if (gid == gidcollgroundthree && collidersdone == false) {//3 NORMAL
								App->collision->AddCollider({ x,y + 12,32,84 }, COLLIDER_SUELO, this);
							}
							if (gid == gidcollgroundwall && collidersdone == false) { //W NORMAL
								App->collision->AddCollider({ x,y + 12,32,188 }, COLLIDER_SUELO, this);
							}
							if (gid == gidcollliana && collidersdone == false) { //W HIELO
								App->collision->AddCollider({ x,y,32,32 }, COLLIDER_LIANA, this);
							}
							if (gid == gidcorrienteagua && collidersdone == false) { //CORRIENTE AGUA
								App->collision->AddCollider({ x,y,32,32 }, COLLIDER_CORRIENTE_AGUA, this);
							}
							if (gid == gidcolldeath && collidersdone == false) {
								App->collision->AddCollider({ x,y + 10,32,32 }, COLLIDER_DEATH, this);
							}

							if ((App->player->dimensionplanta == true) || (App->player->dimensionhielo == true)) {
								if (layer_counter >= 6) {
									if (gid != gidcolldeath && gid != gidcollliana && gid != gidcollgroundicewall && gid != gidcollgroundicethree && gid != gidcollgroundicetwo && gid != gidcollgroundiceone && gid != gidcollgroundone && gid != gidcollgroundtwo && gid != gidcollgroundthree && gid != gidcollgroundwall) {
										if ((layer_counter == 6) || (layer_counter == 8) || (layer_counter == 9)) {
											App->render->Blit(coord_tileset->data->texture, x, y, &rect, 0.7F, 0, 0, 0, flip);
										}
										else {
											App->render->Blit(coord_tileset->data->texture, x, y, &rect, 1.0F, 0, 0, 0, flip);
										}
										
										App->render->Blit(coord_tileset->data->texture, x, y, &rect, 1.0F, 0, 0, 0, flip);
									}
								}
							}

							if ((App->player->dimensionfuego == true) || (App->player->dimensionagua == true)) {
								if (layer_counter >= 5) {
									if (gid != gidcolldeath && gid != gidcollliana && gid != gidcollgroundicewall && gid != gidcollgroundicethree && gid != gidcollgroundicetwo && gid != gidcollgroundiceone && gid != gidcollgroundone && gid != gidcollgroundtwo && gid != gidcollgroundthree && gid != gidcollgroundwall && gid != gidcorrienteagua) {
										if (layer_counter == 5) {
											App->render->Blit(coord_tileset->data->texture, x, y, &rect, 0.7F, 0, 0, 0, flip);
										}
										else {
											App->render->Blit(coord_tileset->data->texture, x, y, &rect, 1.0F, 0, 0, 0, flip);
										}
									}
								}
							}
							if ((App->player->dimensionplanta == false) && (App->player->dimensionhielo == false) && (App->player->dimensionfuego == false) && (App->player->dimensionagua == false)) {
								if (App->scene->changelevel == false) {
									if (layer_counter < 6) {
										if (gid != gidcolldeath && gid != gidcollliana && gid != gidcollgroundicewall && gid != gidcollgroundicethree && gid != gidcollgroundicetwo && gid != gidcollgroundiceone && gid != gidcollgroundone && gid != gidcollgroundtwo && gid != gidcollgroundthree && gid != gidcollgroundwall && gid != gidcorrienteagua) {
											if ((layer_counter == 0) || (layer_counter == 1)) {
											App->render->Blit(coord_tileset->data->texture, x, y, &rect, 0.7F, 0, 0, 0, flip);
											}
											else {
												App->render->Blit(coord_tileset->data->texture, x, y, &rect, 1.0F, 0, 0, 0, flip);
											}
										}
									}
								}
								else {
									if (layer_counter < 5) {
										if (gid != gidcolldeath && gid != gidcollliana && gid != gidcollgroundicewall && gid != gidcollgroundicethree && gid != gidcollgroundicetwo && gid != gidcollgroundiceone && gid != gidcollgroundone && gid != gidcollgroundtwo && gid != gidcollgroundthree && gid != gidcollgroundwall && gid != gidcorrienteagua) {
											if (layer_counter == 0) {
												App->render->Blit(coord_tileset->data->texture, x, y, &rect, 0.7F, 0, 0, 0, flip);
											}
											else {
												App->render->Blit(coord_tileset->data->texture, x, y, &rect, 1.0F, 0, 0, 0, flip);
											}
										}
									}
								}
							}
					}
				//}
			}
		}

		
		
		coord_layer = coord_layer->next;
	}

	collidersdone = true;
}


// Called before quitting
bool j1Map::CleanUp()
{
	LOG("Unloading map");

	// Remove all tilesets
	p2List_item<TileSet*>* item;
	item = data.tilesets.start;

	while(item != NULL)
	{
		RELEASE(item->data);
		item = item->next;
	}
	data.tilesets.clear();

	// TODO 2: clean up all layer data
	// Remove all layers
	p2List_item<MapLayer*>* iteml;
	iteml = data.layers.start;
	while (item != NULL)
	{
		RELEASE(iteml->data->gid);
		RELEASE(iteml->data);
		iteml = iteml->next;
	}
	data.layers.clear();

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

	if(result == NULL)
	{
		LOG("Could not load map xml file %s. pugi error: %s", file_name, result.description());
		ret = false;
	}

	// Load general info ----------------------------------------------
	if(ret == true)
	{
		ret = LoadMap();
	}

	// Load all tilesets info ----------------------------------------------
	pugi::xml_node tileset;
	for(tileset = map_file.child("map").child("tileset"); tileset && ret; tileset = tileset.next_sibling("tileset"))
	{
		TileSet* set = new TileSet();

		if(ret == true)
		{
			ret = LoadTilesetDetails(tileset, set);
		}

		if(ret == true)
		{
			ret = LoadTilesetImage(tileset, set);
		}

		data.tilesets.add(set);
	}

	// TODO 4: Iterate all layers and load each of them
	// Load layer info ----------------------------------------------
	pugi::xml_node layer;
	for (layer = map_file.child("map").child("layer"); layer && ret; layer = layer.next_sibling("layer"))
	{
		MapLayer* set = new MapLayer();

		if (ret == true)
		{
			ret = LoadLayer(layer, set);
		}
		data.layers.add(set);
	}

	if(ret == true)
	{
		LOG("Successfully parsed map XML file: %s", file_name);
		LOG("width: %d height: %d", data.width, data.height);
		LOG("tile_width: %d tile_height: %d", data.tile_width, data.tile_height);

		p2List_item<TileSet*>* item = data.tilesets.start;
		while(item != NULL)
		{
			TileSet* s = item->data;
			LOG("Tileset ----");
			LOG("name: %s firstgid: %d", s->name.GetString(), s->firstgid);
			LOG("tile width: %d tile height: %d", s->tile_width, s->tile_height);
			LOG("spacing: %d margin: %d", s->spacing, s->margin);
			item = item->next;
		}

		// TODO 4: Add info here about your loaded layers
		// Adapt this code with your own variables
		
		p2List_item<MapLayer*>* item_layer = data.layers.start;
		while(item_layer != NULL)
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

	if(map == NULL)
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

		if(bg_color.Length() > 0)
		{
			p2SString red, green, blue;
			bg_color.SubString(1, 2, red);
			bg_color.SubString(3, 4, green);
			bg_color.SubString(5, 6, blue);

			int v = 0;

			sscanf_s(red.GetString(), "%x", &v);
			if(v >= 0 && v <= 255) data.background_color.r = v;

			sscanf_s(green.GetString(), "%x", &v);
			if(v >= 0 && v <= 255) data.background_color.g = v;

			sscanf_s(blue.GetString(), "%x", &v);
			if(v >= 0 && v <= 255) data.background_color.b = v;
		}

		p2SString orientation(map.attribute("orientation").as_string());

		if(orientation == "orthogonal")
		{
			data.type = MAPTYPE_ORTHOGONAL;
		}
		else if(orientation == "isometric")
		{
			data.type = MAPTYPE_ISOMETRIC;
		}
		else if(orientation == "staggered")
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

	if(offset != NULL)
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

	if(image == NULL)
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

		if(set->tex_width <= 0)
		{
			set->tex_width = w;
		}

		set->tex_height = image.attribute("height").as_int();

		if(set->tex_height <= 0)
		{
			set->tex_height = h;
		}

		set->num_tiles_width = set->tex_width / set->tile_width;
		set->num_tiles_height = set->tex_height / set->tile_height;
	}

	return ret;
}

// TODO 3: Create the definition for a function that loads a single layer
bool j1Map::LoadLayer(pugi::xml_node& node, MapLayer* layer)
{
	bool ret = true;
	layer->name = node.child("layer").attribute("name").as_string();
	if (strcmp(layer->name.GetString(), "Name_Null") == 0) {
		LOG("Error geting layer name");
		return false;
	}
	else {
		LOG("OK");
	}
	layer->width = node.attribute("width").as_uint();
	if (layer->width == 0) {
		LOG("Error geting layer width");
		return false;
	}
	layer->height = node.attribute("height").as_uint();
	if (layer->height == 0) {
		LOG("Error geting layer height");
		return false;
	}
	uint total_gid = layer->width * layer->height;
	layer->gid = new uint[total_gid];
	memset(layer->gid, 0, total_gid*sizeof(uint));
	pugi::xml_node tile = node.child("data").child("tile");
	int i = 0;
	while (tile && strcmp(tile.name(),"tile")==0) {
		layer->gid[i] = tile.attribute("gid").as_uint();
		i++;
		tile = tile.next_sibling("tile");
	}
	return ret;
}