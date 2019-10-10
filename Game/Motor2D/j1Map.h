#ifndef __j1MAP_H__
#define __j1MAP_H__

#include "PugiXml/src/pugixml.hpp"
#include "p2List.h"
#include "p2Point.h"
#include "j1Module.h"

// TODO 1: Create a struct for the map layer
// ----------------------------------------------------

struct MapLayer {
	p2SString name = "Name_Null";
	uint width = 0u;
	uint height = 0u;
	uint* gid = nullptr;
	// TODO 6: Short function to get the value of x,y
	inline uint Get(int x, int y) const {
		return (y * width) + x;
	}
};


// ----------------------------------------------------
struct TileSet
{
	// TODO 7: Create a method that receives a tile id and returns it's Rect

	p2SString			name;
	int					firstgid;
	int					margin;
	int					spacing;
	int					tile_width;
	int					tile_height;
	SDL_Texture*		texture;
	int					tex_width;
	int					tex_height;
	int					num_tiles_width;
	int					num_tiles_height;
	int					offset_x;
	int					offset_y;
	SDL_Rect GetRect(int id) {
		int n = id - firstgid;
		int x = n % num_tiles_width;
		x = ((x * tile_width) + (x * spacing)) + margin;
		int y = n / num_tiles_width;
		y = ((y * tile_height) + (y * spacing)) + margin;
		return { x,y,tile_width,tile_height };
	}
};

enum MapTypes
{
	MAPTYPE_UNKNOWN = 0,
	MAPTYPE_ORTHOGONAL,
	MAPTYPE_ISOMETRIC,
	MAPTYPE_STAGGERED
};
// ----------------------------------------------------
struct MapData
{
	int					width;
	int					height;
	int					tile_width;
	int					tile_height;
	SDL_Color			background_color;
	MapTypes			type;
	p2List<TileSet*>	tilesets;
	p2List<MapLayer*>	layers;
	// TODO 2: Add a list/array of layers to the map!
};

// ----------------------------------------------------
class j1Map : public j1Module
{
public:

	j1Map();

	// Destructor
	virtual ~j1Map();

	// Called before render is available
	bool Awake(pugi::xml_node& conf);

	// Called each loop iteration
	void Draw();

	// Called before quitting
	bool CleanUp();

	// Load new map
	bool Load(const char* path);

	// TODO 8: Create a method that translates x,y coordinates from map positions to world positions
	void Translate_Coord(int* x, int* y) {
		*x *= data.tile_width;
		*y *= data.tile_height;
	}

private:

	bool LoadMap();
	bool LoadTilesetDetails(pugi::xml_node& tileset_node, TileSet* set);
	bool LoadTilesetImage(pugi::xml_node& tileset_node, TileSet* set);
	// TODO 3: Create a method that loads a single laye
	bool LoadLayer(pugi::xml_node& node, MapLayer* layer);

public:

	MapData data;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	bool collidersdone=false;
private:

	pugi::xml_document	map_file;
	p2SString			folder;
	bool				map_loaded;
};

#endif // __j1MAP_H__