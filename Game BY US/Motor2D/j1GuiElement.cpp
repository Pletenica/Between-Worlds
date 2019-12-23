#include "UIText.h"
#include "UIWindow.h"
#include "UIButton.h"
#include "UIImage.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Fonts.h"
#include "j1GuiManager.h"
#include "j1GuiElement.h"
#include "j1Window.h"

j1GuiElement::j1GuiElement(GuiType type, SDL_Rect r, j1GuiElement* p, bool d) {
	name.create("UI");
	drageable = d;
	screen_rect = { r.x,r.y,r.w,r.h };
	parent = p;
	if (parent != nullptr) {
		local_rect = { screen_rect.x - parent->screen_rect.x, screen_rect.y - parent->screen_rect.y, screen_rect.w, screen_rect.h };
	}
	else {
		local_rect = screen_rect;
	}
	mask_rect = screen_rect;
}

bool j1GuiElement::PreUpdate() {
	j1GuiElement* ui = this;

	screen_rect.x = local_rect.x;
	screen_rect.y = local_rect.y;
	while (ui->parent != nullptr) {
		screen_rect.x += ui->parent->local_rect.x;
		screen_rect.y += ui->parent->local_rect.y;
		ui = ui->parent;
	}

	uint win_x, win_y;
	App->win->GetWindowSize(win_x, win_y);
	mask_rect = screen_rect;

	if (parent != nullptr) {
		if (mask_rect.x < parent->mask_rect.x) {
			mask_rect.x += parent->mask_rect.x - mask_rect.x;
			mask_rect.w -= parent->mask_rect.x - mask_rect.x;
		}
		else if (mask_rect.x + mask_rect.w > parent->mask_rect.x + parent->mask_rect.w) {
			mask_rect.w -= mask_rect.x + mask_rect.w - parent->mask_rect.x - parent->mask_rect.w;
		}
		if (mask_rect.y < parent->mask_rect.y) {
			mask_rect.y += parent->mask_rect.y - mask_rect.y;
			mask_rect.h -= parent->mask_rect.y - mask_rect.y;
		}
		else if (mask_rect.y + mask_rect.h > parent->mask_rect.y + parent->mask_rect.h) {
			mask_rect.h -= mask_rect.y + mask_rect.h - parent->mask_rect.y - parent->mask_rect.h;
		}
	}
	else {
		if (mask_rect.x < 0) {
			mask_rect.w -= mask_rect.x;
			mask_rect.x = 0;
		}
		else if (mask_rect.x + mask_rect.w > win_x) {
			mask_rect.w -= mask_rect.x + mask_rect.w - win_x;
		}
		if (mask_rect.y < 0) {
			mask_rect.h -= mask_rect.y;
			mask_rect.y = 0;
		}
		else if (mask_rect.y + mask_rect.h > win_y) {
			mask_rect.h -= mask_rect.y + mask_rect.h - win_y;
		}
	}
	return true;
}

SDL_Rect j1GuiElement::GetScreenRect() {
	return screen_rect;
}
SDL_Rect j1GuiElement::GetLocalRect() {
	return local_rect;
}
iPoint j1GuiElement::GetScreenPos() {
	return { screen_rect.x,screen_rect.y };
}
iPoint j1GuiElement::GetLocalPos() {
	return { local_rect.x,local_rect.y };
}
void j1GuiElement::SetLocalPos(iPoint pos) {
	iPoint r = { -local_rect.x + pos.x,-local_rect.y + pos.y };
	local_rect.x = pos.x;
	local_rect.y = pos.y;
	screen_rect.x += r.x;
	screen_rect.y += r.y;
}

bool j1GuiElement::CheckMouse() {
	if (drageable == true) {
		int x, y;
		App->input->GetMousePosition(x, y);
		if (x >= screen_rect.x && x <= screen_rect.x + screen_rect.w && y >= screen_rect.y && y <= screen_rect.y + screen_rect.h)
			return true;
	}
	return false;
}

bool j1GuiElement::Move() {
	int x, y;
	App->input->GetMouseMotion(x, y);
	local_rect.x += x;
	local_rect.y += y;
	return true;
}

SDL_Rect j1GuiElement::Check_Printable_Rect(SDL_Rect sprite, iPoint& dif_sprite) {
	if (mask_rect.x > screen_rect.x) {
		dif_sprite.x = mask_rect.x - screen_rect.x;
		sprite.x += dif_sprite.x;
		sprite.w -= dif_sprite.x;
	}
	else if (mask_rect.w < screen_rect.w) {
		sprite.w -= screen_rect.w - mask_rect.w;
	}
	if (mask_rect.y > screen_rect.y) {
		dif_sprite.y = mask_rect.y - screen_rect.y;
		sprite.y += dif_sprite.y;
		sprite.h -= dif_sprite.y;
	}
	else if (mask_rect.h < screen_rect.h) {
		sprite.h -= screen_rect.h - mask_rect.h;
	}
	return sprite;
}