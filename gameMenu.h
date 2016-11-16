#pragma once
#include "entity.h"

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

private:
	TextureManager towermenuTexture, turretmenuTexture, wallmenuTexture, defmenuTexture; // textures
	Image	towerMenu;
	Image	turretMenu;
	Image	wallMenu;
	Image	defMenu;
	bool menuActive;

	Graphics* graphics;
	Game* game;
	Input* input;
};

