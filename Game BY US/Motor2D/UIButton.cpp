#include "UIButton.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1GuiManager.h"
#include "j1GuiElement.h"
#include "j1Menu.h"


ButtonUI::ButtonUI(bool ismenu, GuiType type, j1GuiElement* p, SDL_Rect r, SDL_Rect sprite, SDL_Rect spriten2, SDL_Rect spriten3, bool d) :j1GuiElement(type, r, p, d) {
	name.create("ButtonUI");
	sprite1 = sprite;
	sprite2 = spriten2;
	sprite3 = spriten3;
	over = false;
	pushed = false;
	boolmenu = ismenu;
}

bool ButtonUI::PostUpdate() {
	SDL_Rect sprite;
	iPoint dif_sprite = { 0,0 };
	if (boolmenu == App->menu->isinmenu) {
		if (pushed == true) {
			sprite = j1GuiElement::Check_Printable_Rect(sprite3, dif_sprite);
		}
		else if (over == true) {
			sprite = j1GuiElement::Check_Printable_Rect(sprite2, dif_sprite);
		}
		else {
			sprite = j1GuiElement::Check_Printable_Rect(sprite1, dif_sprite);
		}
		App->render->Blit((SDL_Texture*)App->menu->menu_graphics, GetScreenPos().x + dif_sprite.x, GetScreenPos().y + dif_sprite.y, &sprite, 0.0f, 0, 0, 0, SDL_FLIP_NONE);

	}
	return true;
}

bool ButtonUI::PreUpdate() {
	int x, y;
	if (boolmenu == App->menu->isinmenu) {
		App->input->GetMousePosition(x, y);
		if (x >= GetScreenPos().x && x <= GetScreenPos().x + GetScreenRect().w && y >= GetScreenPos().y && y <= GetScreenPos().y + GetScreenRect().h)
			over = true;
		else over = false;
		bool button = false;
		if (App->input->GetMouseButtonDown(1) == KEY_DOWN || App->input->GetMouseButtonDown(1) == KEY_REPEAT)
			button = true;
		if (over == true && button == true)
			pushed = true;
		else pushed = false;
	}
	j1GuiElement::PreUpdate();

	return true;
}