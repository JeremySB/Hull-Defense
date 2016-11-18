// Created by Daniel Toney

#pragma once
#include "entity.h"
#include "text.h"

class GameMenu : public Entity
{
public:
	GameMenu(void);
	~GameMenu(void);

	void update(float frameTime);
	void initialize(Graphics* graphics, Game* game, Input* input);
	void draw();
	void onLostDevice();
	void onResetDevice();
	void setCur(int cur);
	void render();
	void display();
	int getCur();

private:
	TextureManager towermenuTexture, turretmenuTexture, wallmenuTexture, defmenuTexture; // textures
	Image	towerMenu;
	Image	turretMenu;
	Image	wallMenu;
	Image	defMenu;
	bool menuActive;

	TextDX *scoreFont;
	TextDX *currencyFont;
	TextDX *objDescriptionFont;
	COLOR_ARGB normalColor;

	//TextDX ckfont;

	int currency;
	std::string currencyStr;

	Graphics* graphics;
	Game* game;
	Input* input;
};

