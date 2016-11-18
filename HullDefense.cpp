// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// HullDefense.cpp v1.1
// This class is the core of the game

#include "HullDefense.h"

//=============================================================================
// Constructor
//=============================================================================
HullDefense::HullDefense() : Game()
{
    waveTimeout = 2;
    timeIntoTimeout = 0;
    dxFont = new TextDX();  // DirectX font
}

//=============================================================================
// Destructor
//=============================================================================
HullDefense::~HullDefense()
{
    releaseAll();           // call onLostDevice() for every graphics item
    safeDelete(dxFont);
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void HullDefense::initialize(HWND hwnd)
{
    Game::initialize(hwnd); // throws GameError

	structureManager.initialize(graphics, this, input);
	gameMenu.initialize(graphics, this, input, audio);
    enemyManager.initialize(this,structureManager.getGrid());
    waves = new Waves(&enemyManager);
    //enemyManager.addChild(new HeavyEnemy());
    // background texture
    if (!backgroundTexture.initialize(graphics, BACKGROUND_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background texture"));

    // background image
    if (!background.initialize(graphics, 0, 0, 0, &backgroundTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background"));


    // initialize DirectX font
    // 18 pixel high Arial
    if(dxFont->initialize(graphics, 18, true, false, "Arial") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));
    return;
}

//=============================================================================
// Update all game items
//=============================================================================
void HullDefense::update()
{
    structureManager.update(frameTime);
	gameMenu.update(frameTime);
    enemyManager.updateChildren(frameTime);
    if(structureManager.getPlacedThisFrame()){
		enemyManager.updateStructures();
        enemyManager.findPaths();
    }
    waves->update(frameTime);
    if((timeIntoTimeout += frameTime) >= waveTimeout)
        waves->startWave();
	// exit on esc
	if(input->isKeyDown(VK_ESCAPE)){
		exit(1);
	}
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void HullDefense::ai()
{}

//=============================================================================
// Handle collisions
//=============================================================================
void HullDefense::collisions()
{
	//Enemy** enemies = enemyManager.getChildren();
	//int test = sizeof(Enemy*);
	//std::list<Enemy*> enemyList(enemies, enemies + MAX_ENEMIES);
	//structureManager.collisions(enemyList);
    structureManager.collisions(enemyManager.getChildren());
}

//=============================================================================
// Render game items
//=============================================================================
void HullDefense::render()
{
    graphics->spriteBegin();                // begin drawing sprites

    background.draw();
    dxFont->setFontColor(graphicsNS::ORANGE);
	
	structureManager.draw();
    enemyManager.draw();
	gameMenu.draw();
    graphics->spriteEnd();                  // end drawing sprites

}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void HullDefense::releaseAll()
{
    dxFont->onLostDevice();
    menuTexture.onLostDevice();
	structureManager.onLostDevice();
	gameMenu.onLostDevice();
    enemyManager.onLostDevice();
    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void HullDefense::resetAll()
{
    menuTexture.onResetDevice();
    dxFont->onResetDevice();
	structureManager.onResetDevice();
	gameMenu.onResetDevice();
    enemyManager.onResetDevice();
    Game::resetAll();
    return;
}
