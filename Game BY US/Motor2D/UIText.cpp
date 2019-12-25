#include "UIText.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Fonts.h"
#include "j1GuiManager.h"
#include "j1GuiElement.h"
#include "j1Menu.h"

TextUI::TextUI(bool ismenu,GuiType type, j1GuiElement* p, SDL_Rect r, p2SString str, bool d) :j1GuiElement(type, r, p, d) {
	name.create("TextUI");
	stri = str;
	int w, h;
	boolmenu = ismenu;
}

bool TextUI::PostUpdate() {
	SDL_Rect rect = { 0,0,0,0 };
	iPoint dif_sprite = { 0,0 };
	SDL_QueryTexture(App->fonts->Print(stri.GetString()), NULL, NULL, &rect.w, &rect.h);
	SDL_Rect sprite = j1GuiElement::Check_Printable_Rect(rect, dif_sprite);
	if (boolmenu == App->menu->isinmenu) {
		App->render->Blit(App->fonts->Print(stri.GetString()), GetScreenPos().x + dif_sprite.x, GetScreenPos().y + dif_sprite.y, &sprite, 0.0f, 0, 0, 0, SDL_FLIP_NONE);
	}
	return true;
}