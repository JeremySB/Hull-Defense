// created by Daniel Toney

#pragma once
#include "entity.h"
#include "text.h"
#include "audio.h"
#include "gameState.h"

class MainMenu
{
public:
	MainMenu(void);
	~MainMenu(void);

	void update(float frameTime);
	void initialize(Graphics* graphics, Game* game, Input* input, Audio* audio);
	void draw();
	void onLostDevice();
	void onResetDevice();

	void setGameState(GameState* in) { gameState = in; }
	void transition(Image *image, std::string side);
	void resetMenu();

private:
	// instruction textures
	TextureManager instruction0Texture, instruction1Texture, instruction2Texture;
	// menu textures
    TextureManager menuTexture, mainmenuTexture;
	// other screen textures
	TextureManager winscreenTexture,losescreenTexture,wavecompleteTexture, loadingscreenTexture, transitionTexture; // textures


	Image   mainmenu;
	Image   instruction0;
	Image   instruction1;
	Image   instruction2;
	Image   transitionImage;
	Image   winscreen;
	Image   losescreen;
	Image   wavecomplete;
	Image	loadingscreen;

	Graphics* graphics;
	Game* game;
	Input* input;
	GameState* gameState;

	float timer;
};

