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

    // background texture
    if (!backgroundTexture.initialize(graphics, BACKGROUND_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background texture"));

	// tower menu
	if (!towermenuTexture.initialize(graphics, TOWERMENU_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tower menu texture"));

	// turret menu
	if (!turretmenuTexture.initialize(graphics, TURRETMENU_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tower menu texture"));

	// wall menu
	if (!wallmenuTexture.initialize(graphics, WALLMENU_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tower menu texture"));

    // menu texture
    if (!menuTexture.initialize(graphics,MENU_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu texture"));

	// def texture
    if (!defmenuTexture.initialize(graphics,DEFMENU_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing def menu texture"));

    // background image
    if (!background.initialize(graphics, 0, 0, 0, &backgroundTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background"));

	// tower menu
	if (!towerMenu.initialize(graphics, 0, 0, 0, &towermenuTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tower menu"));

	// turret menu
	if (!turretMenu.initialize(graphics, 0, 0, 0, &turretmenuTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing turret menu"));

	// wall menu
	if (!wallMenu.initialize(graphics, 0, 0, 0, &wallmenuTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall menu"));

	// def menu
	if (!defMenu.initialize(graphics, 0, 0, 0, &defmenuTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Default menu"));

    // menu image
    if (!menu.initialize(graphics,0,0,0,&menuTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu"));

    // initialize DirectX font
    // 18 pixel high Arial
    if(dxFont->initialize(graphics, 18, true, false, "Arial") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));

    menu.setDegrees(300);
    menu.setScale(0.002861f);

	towerMenu.setX(0);
	towerMenu.setY(GAME_HEIGHT-TABS_HEIGHT);
	turretMenu.setX(0);
	turretMenu.setY(GAME_HEIGHT-TABS_HEIGHT);
	wallMenu.setX(0);
	wallMenu.setY(GAME_HEIGHT-TABS_HEIGHT);
	defMenu.setX(0);
	defMenu.setY(GAME_HEIGHT-TABS_HEIGHT);

	menuActive = false;

	towerMenu.setVisible(false);
	wallMenu.setVisible(false);
	turretMenu.setVisible(false);
	defMenu.setVisible(true);

    return;
}

//=============================================================================
// Update all game items
//=============================================================================
void HullDefense::update()
{
    static float delay = 0;
    delay += frameTime;

	structureManager.update(frameTime);
	
	//if(input->getMouseLButton()){
	if(menuActive){
		towerMenu.setX(0);
		towerMenu.setY(GAME_HEIGHT-towerMenu.getHeight());
		turretMenu.setX(0);
		turretMenu.setY(GAME_HEIGHT-turretMenu.getHeight());
		wallMenu.setX(0);
		wallMenu.setY(GAME_HEIGHT-wallMenu.getHeight());

		if(input->getMouseLButton()){
			if(input->getMouseX()>(0) && input->getMouseX()<(TABS_WIDTH) && input->getMouseY()>(GAME_HEIGHT-towerMenu.getHeight()) && input->getMouseY()<(GAME_HEIGHT-towerMenu.getHeight()+TABS_HEIGHT)){
				towerMenu.setVisible(true);
				wallMenu.setVisible(false);
				turretMenu.setVisible(false);
				defMenu.setVisible(false);
			}else if(input->getMouseX()>(TABS_WIDTH) && input->getMouseX()<(2*TABS_WIDTH) && input->getMouseY()>(GAME_HEIGHT-towerMenu.getHeight()) && input->getMouseY()<(GAME_HEIGHT-towerMenu.getHeight()+TABS_HEIGHT)){
				towerMenu.setVisible(false);
				wallMenu.setVisible(true);
				turretMenu.setVisible(false);
				defMenu.setVisible(false);
			}else if(input->getMouseX()>(2*TABS_WIDTH) && input->getMouseX()<(3*TABS_WIDTH) && input->getMouseY()>(GAME_HEIGHT-towerMenu.getHeight()) && input->getMouseY()<(GAME_HEIGHT-towerMenu.getHeight()+TABS_HEIGHT)){
				towerMenu.setVisible(false);
				wallMenu.setVisible(false);
				turretMenu.setVisible(true);
				defMenu.setVisible(false);
			}
		}
	}else{
		defMenu.setVisible(true);
		towerMenu.setVisible(false);
		wallMenu.setVisible(false);
		turretMenu.setVisible(false);
		
		if(input->getMouseLButton()){
			if(input->getMouseX() >(0) && input->getMouseX()<(TABS_WIDTH) && input->getMouseY()>(GAME_HEIGHT-TABS_HEIGHT) && input->getMouseY()<(GAME_HEIGHT)){
				towerMenu.setVisible(true);
				wallMenu.setVisible(false);
				turretMenu.setVisible(false);
				defMenu.setVisible(false);
				menuActive = true;
			}else if(input->getMouseX()>(TABS_WIDTH) && input->getMouseX()<(2*TABS_WIDTH) && input->getMouseY()>(GAME_HEIGHT-TABS_HEIGHT) && input->getMouseY()<(GAME_HEIGHT)){
				towerMenu.setVisible(false);
				wallMenu.setVisible(true);
				turretMenu.setVisible(false);
				defMenu.setVisible(false);
				menuActive = true;
			}else if(input->getMouseX()>(2*TABS_WIDTH) && input->getMouseX()<(3*TABS_WIDTH) && input->getMouseY()>(GAME_HEIGHT-TABS_HEIGHT) && input->getMouseY()<(GAME_HEIGHT)){
				towerMenu.setVisible(false);
				wallMenu.setVisible(false);
				turretMenu.setVisible(true);
				defMenu.setVisible(false);
				menuActive = true;
			}
		}
	}

	if(input->getMouseLButton() && input->getMouseY()<GAME_HEIGHT-towerMenu.getHeight()){
		menuActive = false;
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
{}

//=============================================================================
// Render game items
//=============================================================================
void HullDefense::render()
{
    graphics->spriteBegin();                // begin drawing sprites

    background.draw(graphicsNS::ALPHA50);
    //menu.draw();
    dxFont->setFontColor(graphicsNS::ORANGE);
	towerMenu.draw();
	turretMenu.draw();
	wallMenu.draw();
	defMenu.draw();
	structureManager.draw();

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
	towermenuTexture.onLostDevice();
	turretmenuTexture.onLostDevice();
	wallmenuTexture.onLostDevice();
	defmenuTexture.onLostDevice();
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
	towermenuTexture.onResetDevice();
	turretmenuTexture.onResetDevice();
	wallmenuTexture.onResetDevice();
	defmenuTexture.onResetDevice();
    Game::resetAll();
    return;
}
