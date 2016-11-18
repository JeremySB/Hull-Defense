// Created by Daniel Toney

#pragma once
#include "entity.h"
#include "text.h"
#include "audio.h"

class GameMenu 
{
public:
	GameMenu(void);
	~GameMenu(void);

	void update(float frameTime);
	void initialize(Graphics* graphics, Game* game, Input* input, Audio* audio);
	void draw();
	void onLostDevice();
	void onResetDevice();
	void display();
	void setCurrency(int in) { currency = in; }
	void setHealth(int in) { baseHealth = in; }

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
	Audio *audio;

	//TextDX ckfont;

	int currency;
	int baseHealth;
	
	std::string currencyStr;

	Graphics* graphics;
	Game* game;
	Input* input;
};

