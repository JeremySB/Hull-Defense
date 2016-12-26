// Created by Daniel Toney

#pragma once
#include "entity.h"
#include "text.h"
#include "audio.h"
#include "gameState.h"

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

	void setGameState(GameState* in) { gameState = in; }

private:

	TextureManager towermenuTexture, turretmenuTexture, wallmenuTexture, defmenuTexture, healthTexture, energyTexture, tranmenuTexture; // textures

	Image	towerMenu;
	Image	tranMenu;
	Image	repairMenu;
	Image	sellMenu;
	Image	defMenu;
	Image   healthImage;
	Image	energyImage;
	bool menuActive;

	bool lastClickState;

	TextDX *scoreFont;
	TextDX *currencyFont;
	TextDX *objDescriptionFont;
	COLOR_ARGB normalColor;
	Audio *audio;
	
	std::string healthStr;
	std::string energyStr;

	Graphics* graphics;
	Game* game;
	Input* input;
	GameState* gameState;
};

