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
    safeDelete(level1waves);
    safeDelete(level2waves);
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void HullDefense::initialize(HWND hwnd)
{
    Game::initialize(hwnd); // throws GameError

	structureManager.initialize(graphics, this, input, &gameState);
	gameMenu.initialize(graphics, this, input, audio);
	gameMenu.setGameState(&gameState);

    enemyManager.initialize(this,structureManager.getGrid(),&gameState,audio);

	gameState.setGamePhase(GameState::intro);

    level1waves = new Waves(&enemyManager);
    level1waves->waves[0].spawnTime = 1;
    level1waves->waves[1].spawnTime = 1;
    level1waves->waves[2].spawnTime = 1;
    level1waves->waves[3].spawnTime = .7;
    level1waves->waves[4].spawnTime = .5;
    level1waves->waves[0].spawnTime = 1;
    level1waves->waves[1].spawnTime = 1;
    level1waves->waves[2].spawnTime = 1;
    level1waves->waves[3].spawnTime = .7;


    for( int i = 0; i < 5; i++){
        level1waves->waves[0].toSpawn.push_back(new MediumEnemy());
        level1waves->waves[1].toSpawn.push_back(new HeavyEnemy());
        level1waves->waves[2].toSpawn.push_back(new LightEnemy());
    }
    for(int i = 0; i < 10; i ++){
        switch(rand()%3){
        case(0):
            level1waves->waves[3].toSpawn.push_back(new LightEnemy());
            level1waves->waves[4].toSpawn.push_back(new MediumEnemy());
            break;
        case(1):
            level1waves->waves[3].toSpawn.push_back(new MediumEnemy());
            level1waves->waves[4].toSpawn.push_back(new HeavyEnemy());
            break;
        case(2):
            level1waves->waves[3].toSpawn.push_back(new HeavyEnemy());
            level1waves->waves[3].toSpawn.push_back(new LightEnemy());
            break;
        }
    }
    level2waves = new Waves(&enemyManager);
    level2waves->waves[0].spawnTime = 1;
    level2waves->waves[1].spawnTime = .7;
    level2waves->waves[2].spawnTime = .7;
    level2waves->waves[3].spawnTime = .5;
    level2waves->waves[4].spawnTime = .6;
    for(int i=0; i < 5; i ++)
        level2waves->waves[0].toSpawn.push_back(new LightEnemy());
    for(int i = 0; i < 10; i ++){
        switch(rand() % 2) {
                case(0):
                    level2waves->waves[1].toSpawn.push_back(new LightEnemy());
                    break;
                case(1):
                    level2waves->waves[1].toSpawn.push_back(new MediumEnemy());
                    break;
      }
    }
    for(int i = 0; i < 15; i++)
        level2waves->waves[2].toSpawn.push_back(new LightEnemy());

    for(int i=0; i < 5; i++)
        level2waves->waves[3].toSpawn.push_back(new HeavyEnemy());
    for (int i = 0; i < 5; i++)
        level2waves->waves[3].toSpawn.push_back(new LightEnemy());
    for (int i = 0; i < 5; i++)
        level2waves->waves[3].toSpawn.push_back(new MediumEnemy());

    for (int i = 0; i < 30; i++) {
        switch (rand() % 3) {
        case(0):
            level2waves->waves[4].toSpawn.push_back(new LightEnemy());
            break;
        case(1):
            level2waves->waves[4].toSpawn.push_back(new MediumEnemy());
            break;
        case(2):
            level2waves->waves[4].toSpawn.push_back(new HeavyEnemy());
            break;
        }
    }
    //enemyManager.addChild(new HeavyEnemy());
    // background texture
    if (!backgroundTexture.initialize(graphics, BACKGROUND_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background texture"));

    // background image
    if (!background.initialize(graphics, 0, 0, 0, &backgroundTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background"));
	//
	// main menu texture
    if (!mainmenuTexture.initialize(graphics, MAIN_MENU))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing main menu texture"));

    // main menu image
    if (!mainmenu.initialize(graphics, 0, 0, 0, &mainmenuTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing main menu"));
	//
	// instruction0 texture
    if (!instruction0Texture.initialize(graphics, INSTRUCTION0))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing instruction0 texture"));

    // background image
    if (!instruction0.initialize(graphics, 0, 0, 0, &instruction0Texture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background"));
	//
	// INSTRUCTION1 texture
    if (!instruction1Texture.initialize(graphics, INSTRUCTION1))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background texture"));

    // background image
    if (!instruction1.initialize(graphics, 0, 0, 0, &instruction1Texture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing instruction1"));

	// INSTRUCTION2 texture
    if (!instruction2Texture.initialize(graphics, INSTRUCTION2))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background texture"));

    // background image
    if (!instruction2.initialize(graphics, 0, 0, 0, &instruction2Texture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing instruction2"));
	////

	// background texture
    if (!winscreenTexture.initialize(graphics, WIN_SCREEN))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background texture"));

    // background image
    if (!winscreen.initialize(graphics, 0, 0, 0, &winscreenTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background"));

	// background texture
    if (!losescreenTexture.initialize(graphics, LOSE_SCREEN))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background texture"));

    // background image
    if (!losescreen.initialize(graphics, 0, 0, 0, &losescreenTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background"));

	// background texture
    if (!wavecompleteTexture.initialize(graphics, WAVE_COMPLETE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background texture"));

    // background image
    if (!wavecomplete.initialize(graphics, 0, 0, 0, &wavecompleteTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background"));

	audio->playCue(BACKGROUND);
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
	gameState.setHealth(structureManager.getBaseHealth());
	GameState::GamePhase phase = gameState.getGamePhase();
	switch (phase)
	{
	case GameState::intro:
		if(input->getMouseLButton()){
			if(input->getMouseX()>GAME_WIDTH/2){
				gameState.setGamePhase(GameState::instructions);
			}else{
				gameState.setGamePhase(GameState::level1Play);
			}
		}
		break;
	case GameState::instructions:
		break;
	case GameState::level1Init:
		break;
	case GameState::level1Build:
		break;
	case GameState::level1Play:
        structureManager.update(frameTime);
        gameMenu.update(frameTime);
        level1waves->update(frameTime);
        enemyManager.updateChildren(frameTime);
        if (structureManager.getPlacedThisFrame()) {
            enemyManager.updateStructures();
            enemyManager.findPaths();
        }
		break;
	case GameState::level2Init:
		break;
	case GameState::level2Build:
		break;
	case GameState::level2Play:
        structureManager.update(frameTime);
        gameMenu.update(frameTime);
        level2waves->update(frameTime);
        enemyManager.updateChildren(frameTime);
        if (structureManager.getPlacedThisFrame()) {
            enemyManager.updateStructures();
            enemyManager.findPaths();
        }
		break;
	case GameState::won:
		break;
	case GameState::lost:
		break;
	default:
		break;
	}
	
	//structureManager.update(frameTime);
	//gameMenu.update(frameTime);
    //enemyManager.updateChildren(frameTime);

   /* if(structureManager.getPlacedThisFrame()){
		enemyManager.updateStructures();
        enemyManager.findPaths();
    }*/
    //level1waves->update(frameTime);
    if(input->isKeyDown('R')){
        auto tmp = structureManager.getStructures();
        while(!tmp.empty()){
            if(tmp.front()->getType() == base){
                tmp.front()->setHealth(1000000000);
                break;
            }
            tmp.pop_front();
        }
    }
    if(input->isKeyDown('C')){
        gameState.addCurrency(100000);
    }
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

	GameState::GamePhase phase = gameState.getGamePhase();
	switch (phase)
	{
	case GameState::intro:
		mainmenu.draw();
		break;
	case GameState::instructions:
		instruction0.draw();
		/*if(input->getMouseLButton() && !mouseWasDown){

		}*/
		break;
	case GameState::level1Init:
		break;
	case GameState::level1Build:
		break;
	case GameState::level1Play:
        level1waves->update(frameTime);
        structureManager.draw();
        enemyManager.draw();
        gameMenu.draw();
		break;
	case GameState::level2Init:
		break;
	case GameState::level2Build:
		break;
	case GameState::level2Play:
        level2waves->update(frameTime);
        structureManager.draw();
        enemyManager.draw();
        gameMenu.draw();
		break;
	case GameState::won:
		break;
	case GameState::lost:
		break;
	default:
		break;
	}
	


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
