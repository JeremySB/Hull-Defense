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
	gameMenu.initialize(graphics, this, input);
    enemyManager.initialize(this,structureManager.getGrid());
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


    //Enemy * tmp = new Enemy();
    //if(!tmp->initialize(this, 0, 0, 0, &enemyTexture))
    //    throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy"));
	//tmp->setX(0);
    //tmp->setY(GAME_HEIGHT/2);
    
    //if (!bob->initialize(this, 0, 0, 0, &enemyTexture))
    //    throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy"));

    //bob->setX(GAME_WIDTH/2);
    //bob->setY(GAME_HEIGHT/2);

    //tmp->setTarget(bob);
    //enemyManager.setGrid(structureManager.getGrid());
    

	//tmp->setTarget(structureManager.getStructures().front());//t1);

    //enemyManager.findPaths();
    return;
}

//=============================================================================
// Update all game items
//=============================================================================
void HullDefense::update()
{
    structureManager.update(frameTime);
	gameMenu.update(frameTime);
    if(structureManager.getPlacedThisFrame()){
        enemyManager.findPaths();
    }
	enemyManager.updateChildren(frameTime);
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
	Enemy** enemies = enemyManager.getChildren();
	int test = sizeof(Enemy*);
	std::list<Enemy*> enemyList(enemies, enemies + MAX_ENEMIES);
	structureManager.collisions(enemyList);
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
