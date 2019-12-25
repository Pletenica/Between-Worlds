#include "UIImage.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1GuiManager.h"
#include "j1GuiElement.h"
#include "j1Menu.h"

ImageUI::ImageUI(bool ismenu, GuiType type, j1GuiElement* p, SDL_Rect r, SDL_Rect sprite, bool d) :j1GuiElement(type, r, p, d) {
	name.create("ImageUI");
	sprite1 = sprite;
	boolmenu = ismenu;
}

bool ImageUI::PostUpdate() {
	iPoint dif_sprite = { 0,0 };
	if (boolmenu == App->menu->isinmenu) {
		SDL_Rect sprite = j1GuiElement::Check_Printable_Rect(sprite1, dif_sprite);
		App->render->Blit((SDL_Texture*)App->guimanager->GetAtlas(), GetScreenPos().x + dif_sprite.x, GetScreenPos().y + dif_sprite.y, &sprite, 0.0f, 0, 0, 0, SDL_FLIP_NONE);
	}
	return true;
}