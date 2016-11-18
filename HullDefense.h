// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// HULLDEFENSE.h

#ifndef _HULLDEFENSE_H           // Prevent multiple definitions if this 
#define _HULLDEFENSE_H           // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <string>
#include <sstream>
#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "textDX.h"
#include "structureManager.h"
#include "gameMenu.h"
#include "enemyManager.h"
#include "Waves.h"

//=============================================================================
// This class is the core of the game
//=============================================================================
class HullDefense : public Game
{
private:
    // game items
    TextureManager menuTexture, backgroundTexture, towermenuTexture, turretmenuTexture, wallmenuTexture, defmenuTexture; // textures
	StructureManager structureManager;
    Waves* waves;
    EnemyManager enemyManager;
	GameMenu gameMenu;
    Image   background;         // background image
    TextDX  *dxFont;            // DirectX font

	GameState gameState;
	int currency;

public:
    // Constructor
    HullDefense();
    // Destructor
    virtual ~HullDefense();

	int getCurrency() { return currency; }
	void setCurrency(int in) { currency = in; }
	void addCurrency(int in) { currency += in; }

	GameState getGameState() { return gameState; }
	void setGameState(GameState in) { gameState = in; }

    // Initialize the game
    void initialize(HWND hwnd);
    void update();      // must override pure virtual from Game
    void ai();          // "
    void collisions();  // "
    void render();      // "
    void releaseAll();
    void resetAll();
};

#endif
