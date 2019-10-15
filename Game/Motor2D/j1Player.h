#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

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
	SDL_Texture* current_graphics = nullptr;
	SDL_Texture* watter_graphics = nullptr;
	SDL_Texture* fire_graphics = nullptr;
	SDL_Texture* plant_graphics = nullptr;
	SDL_Texture* ice_graphics = nullptr;
	SDL_Texture* normal_graphics = nullptr;
	Mix_Chunk *walksound;
	Mix_Chunk *jumpsound;
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
	int Ginit = 2;
	int G = Ginit;
	int jump_vel = 17;
	int G_max = 25;
	int speed_player = 2;
	int speed_player_jump = 2;
	int limit_liana = 0;

	SDL_RendererFlip flip = SDL_FLIP_NONE;
	bool godmode = false;
	bool isinair = true;
	bool isjumping = false;
	bool isinice = false;
	bool stop_right = false;
	bool stop_left = false;
	bool stop_jump = false;
	//bool deadbool = false;
	bool isinliana = false;
	bool changeplantmap = false;
	bool changeicemap = false;
	bool changewattermap = false;
	bool changenormalmap = false;
	bool changefiremap = false;

public:
	j1Player();
	~j1Player();


	bool Start();
	bool Awake();
	bool PreUpdate();
	bool Update();
	bool PostUpdate();
	bool CleanUp();
	void OnCollision(Collider*, Collider*);

};

#endif