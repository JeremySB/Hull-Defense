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
	TextureManager towermenuTexture, turretmenuTexture, wallmenuTexture, defmenuTexture; // textures
	Image	towerMenu;
	Image	repairMenu;
	Image	sellMenu;
	Image	defMenu;
	bool menuActive;

	bool lastClickState;

	TextDX *scoreFont;
	TextDX *currencyFont;
	TextDX *objDescriptionFont;
	COLOR_ARGB normalColor;
	Audio *audio;

	//TextDX ckfont;
	
	std::string currencyStr;

	Graphics* graphics;
	Game* game;
	Input* input;
	GameState* gameState;
};

