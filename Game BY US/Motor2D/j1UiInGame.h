#ifndef __j1UIINGAME_H__
#define __j1UIINGAME_H__

#include "j1Module.h"
#include "j1Animation.h"
#include "p2DynArray.h"
#include "Coins.h"
#include "j1GuiManager.h"
#include <string>

struct SDL_Texture;
struct Collider;

class j1UiInGame : public j1Module
{
public:
	j1UiInGame();
	virtual ~j1UiInGame();

	bool Awake(pugi::xml_node& config);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;

	void CreateFirstWorldCoins();
	void CreateSecondWorldCoins();
	bool CleanUpCoinsArray();

public:
	int number_coins = 0;
	p2DynArray<Coins*> coins_array;
	SDL_Texture* ui_graphics = nullptr;
	Animation heart_anim;
	Animation gray_heart_anim;

	SDL_Rect coinsrect;
	j1GuiElement* guielement_coinstext;

	SDL_Rect coinstextrect;
	j1GuiElement* guielement_coinstexttext;

private:
	p2SString stringo="0";
	std::string realstring = "0";
};

#endif // __j1UIINGAME_H__