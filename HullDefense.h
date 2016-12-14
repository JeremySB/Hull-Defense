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

//=============================================================================
// This class is the core of the game
//=============================================================================
class HullDefense : public Game
{
private:
    // game items
	// menu textures
    TextureManager menuTexture, towermenuTexture, turretmenuTexture, wallmenuTexture, defmenuTexture, mainmenuTexture;
	// instruction textures
	TextureManager instruction0Texture, instruction1Texture, instruction2Texture;
	// other screen textures
	TextureManager winscreenTexture,losescreenTexture,wavecompleteTexture, backgroundTexture, loadingscreenTexture, transitionTexture; // textures
	StructureManager structureManager;
	ParticleManager particleManager;
    Waves waves;
    float waveTimeout;
    float timeIntoTimeout;
    EnemyManager enemyManager;
	GameMenu gameMenu;
    Image   background;         // background image
	Image   mainmenu;
	Image   instruction0;
	Image   instruction1;
	Image   instruction2;
	Image   transitionImage;
	Image   winscreen;
	Image   losescreen;
	Image   wavecomplete;
	Image	loadingscreen;

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
