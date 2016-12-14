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
#include "gameState.h"
#include "particleManager.h"
#include "mainMenu.h"

//=============================================================================
// This class is the core of the game
//=============================================================================
class HullDefense : public Game
{
private:
    // game items
	// menu textures
    TextureManager towermenuTexture, turretmenuTexture, wallmenuTexture, defmenuTexture;
	// other screen textures
	TextureManager backgroundTexture, background2Texture, background3Texture; // textures
	StructureManager structureManager;
	ParticleManager particleManager;
    Waves waves;
    float waveTimeout;
    float timeIntoTimeout;
    EnemyManager enemyManager;
	GameMenu gameMenu;
	MainMenu mainMenu;
    Image   background;         // background image

    TextDX  *dxFont;            // DirectX font

	GameState gameState;

	bool lastClickState;

public:
    // Constructor
    HullDefense();
    // Destructor
    virtual ~HullDefense();

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
