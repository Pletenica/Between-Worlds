#ifndef __j1PLAYER_H__
#define __j1PLAYER_H__

#include "j1Module.h"
#include "j1Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Mix_Chunk;
struct Collider;

#define INPUTSOUTS 8

enum state {
	A_NONE = 0,
	A_IDLE,
	A_WALK_RIGHT,
	A_WALK_LEFT,
	A_JUMP_NEUTRAL,
	A_JUMP_RIGHT,
	A_JUMP_LEFT,
	A_CROUCH,
	A_ACTION
};

enum inputin {
	S_NONE = 0,
	S_LEFT_DOWN,
	S_RIGHT_DOWN,
	S_LEFT_AND_RIGHT, //delete with gamepad
	S_JUMP,
	S_JUMP_RIGHT,
	S_JUMP_LEFT,
	S_T,
	S_T_LEFT,
	S_T_RIGHT,
	S_T_JUMP,
	S_T_JUMP_RIGHT,
	S_T_JUMP_LEFT,
	S_TR,
	S_TR_LEFT,
	S_TR_RIGHT,
	S_TR_JUMP,
	S_TR_JUMP_RIGHT,
	S_TR_JUMP_LEFT,
	S_R,
	S_R_LEFT,
	S_R_RIGHT,
	S_R_JUMP,
	S_R_JUMP_RIGHT,
	S_R_JUMP_LEFT,
	S_Y,
	S_Y_LEFT,
	S_Y_RIGHT,
	S_Y_JUMP,
	S_Y_JUMP_RIGHT,
	S_Y_JUMP_LEFT,
	S_U,
	S_U_LEFT,
	S_U_RIGHT,
	S_U_JUMP,
	S_U_JUMP_RIGHT,
	S_U_JUMP_LEFT,
	S_YU,
	S_YU_LEFT,
	S_YU_RIGHT,
	S_YU_JUMP,
	S_YU_JUMP_RIGHT,
	S_YU_JUMP_LEFT,
	S_ACTION,
};

enum inputout {
	SO_NONE = 0,
	SO_LEFT_UP,
	SO_RIGHT_UP,
	SO_JUMP_FINISH,
	SO_ACTION_FINISH
};

class j1Player : public j1Module
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


	iPoint position;
	int mult;
	int jump_max = 80;
	state actual;
	inputin inputstate[60];
	inputout inputstateout[INPUTSOUTS];
	Collider* body;
	Collider*movecamright;
	int Ginit;
	int G = Ginit;
	int jump_vel;
	int G_max;
	int speed_player;
	int speed_player_ice;
	int speed_player_jump;
	int limit_liana = 0;
	int limit_watter = 0;
	int limit_wave_watter = 0;
	int limit_ice = 0;

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


};

#endif