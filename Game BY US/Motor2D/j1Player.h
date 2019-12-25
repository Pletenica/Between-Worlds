#ifndef __j1PLAYER_H__
#define __j1PLAYER_H__

#include "j1Module.h"
#include "j1Animation.h"
#include "p2Point.h"
#include "j1Entity.h"

struct SDL_Texture;
struct Mix_Chunk;
struct Collider;

class j1Player : public j1Entity
{
public:
	j1Player();
	virtual ~j1Player();

	bool Awake(pugi::xml_node&config);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();
	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;
	void OnCollision(Collider*, Collider*);
	void ChangeToLevel1();
	void ChangeToLevel2();

public:
	SDL_Texture* current_graphics = nullptr;
	SDL_Texture* watter_graphics = nullptr;
	SDL_Texture* fire_graphics = nullptr;
	SDL_Texture* plant_graphics = nullptr;
	SDL_Texture* ice_graphics = nullptr;
	SDL_Texture* normal_graphics = nullptr;
	Animation Current_Animation;
	Animation idle;
	Animation walk;
	Animation jump;
	Animation liana;
	Animation dead;
	SDL_Rect rectplayer;
	SDL_Rect rectoli;

	float positionxinit;
	float positionyinit;
	int mult;
	int jump_max = 80;
	//Collider* body;
	Collider*movecamright;
	float Ginit;
	float G = Ginit;
	float jump_vel;
	float G_max;
	float speed_player;
	float speed_player_aux;
	float speed_player_ice;
	float speed_player_ice_aux;
	float speed_player_jump;
	float speed_player_jump_aux;
	int limit_liana = 0;
	int limit_watter = 0;
	int limit_wave_watter = 0;
	int limit_ice = 0;
	float G_aux = G;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	bool insidedeath = false;
	bool insideportal = false;
	bool insidewalk = false;
	bool dimensionnormal = true;
	bool dimensionagua = false;
	bool dimensionfuego = false;
	bool dimensionhielo = false;
	bool dimensionplanta = false;
	bool right = false;
	bool left = false;
	bool ice_right = false;
	bool ice_left = false;
	bool godmode = false;
	bool isinair = true;
	bool isjumping = false;
	bool isdoublejumping = false;
	bool isinice = false;
	bool stop_right = false;
	bool stop_left = false;
	bool stop_jump = false;
	bool stop_up = false;
	bool deadbool = false;
	bool isinliana = false;
	bool exitgame = true;
	bool deadsounddone = true;

	unsigned int walkingsound;
	unsigned int portalsound;
	unsigned int jumpingsound;
	unsigned int deathsound;

	int lifes = 3;
	int num_coins = 0;
};

#endif