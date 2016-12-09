
#include "HullDefense.h"

//=============================================================================
// Constructor
//=============================================================================
HullDefense::HullDefense() : Game()
{
	waveTimeout = 2;
	timeIntoTimeout = 0;
	dxFont = new TextDX();  // DirectX font
	lastClickState = false;
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

	structureManager.initialize(graphics, this, input, &gameState);
	gameMenu.initialize(graphics, this, input, audio);
	gameMenu.setGameState(&gameState);

	enemyManager.initialize(this,structureManager.getGrid(),&gameState,audio);

	gameState.setGamePhase(GameState::intro);

	waves.initialize(&enemyManager);
	
	audio->playCue(BACKGROUND);
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
	
	if (!loadingscreenTexture.initialize(graphics, LOADING_SCREEN))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing loading screen texture"));

	// main menu image
	if (!loadingscreen.initialize(graphics, 0, 0, 0, &loadingscreenTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing loading screen"));

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
	std::list<Enemy*> enemies;

	gameState.setHealth(structureManager.getBaseHealth());

	switch (gameState.getGamePhase())
	{
	case GameState::intro:
		if(!input->getMouseLButton() && lastClickState){
			if(input->getMouseX()>GAME_WIDTH/2){
				gameState.setGamePhase(GameState::instructions);
			}else{
				gameState.setGamePhase(GameState::level1Init);
			}
		}
		break;

	case GameState::instructions:
		if(!input->getMouseLButton() && lastClickState){
			gameState.setGamePhase(GameState::instructions1);
		}
		break;

	case GameState::instructions1:
		if (!input->getMouseLButton() && lastClickState) {
			gameState.setGamePhase(GameState::instructions2);
		}
		break;

	case GameState::instructions2:
		if (!input->getMouseLButton() && lastClickState) {
			gameState.setGamePhase(GameState::intro);
		}
		break;

	case GameState::level1Init:
		gameState.setSelectionMode(GameState::photonCannonSelection);
		enemies = enemyManager.getChildren();
		waves.loadWaves(LEVEL1WAVEFILE);
		enemyManager.setSpawn(VECTOR2(0,GAME_HEIGHT/2));

		for (auto i = enemies.begin(); i != enemies.end(); i++)
		{
			(*i)->setHealth(-1);
		}
		enemyManager.updateChildren(frameTime);
		structureManager.reset();
		structureManager.addBase(950, 10);
		gameState.setCurrency(1500);
		gameState.setGamePhase(GameState::level1Play);
		break;

	case GameState::level1Play:
		structureManager.update(frameTime);
		gameMenu.update(frameTime);
		
		waves.update(frameTime);

		enemyManager.updateChildren(frameTime);
		enemies = enemyManager.getChildren();
		if (structureManager.getPlacedThisFrame()) {
			enemyManager.updateStructures();
			enemyManager.findPaths();
		} 
		if (waves.complete() && enemyManager.getNumChildren() == 0)
			gameState.setGamePhase(GameState::level2Init);
		if (structureManager.getBaseHealth() <= 0)
			gameState.setGamePhase(GameState::lost);
		break;

	case GameState::level2Init:
		enemies = enemyManager.getChildren();
		waves.loadWaves(LEVEL1WAVEFILE);

		enemyManager.setSpawn(VECTOR2( (enemyManager.getSpawn().x ? 0 : GAME_WIDTH - CELL_WIDTH), GAME_HEIGHT/2));

		for (auto i = enemies.begin(); i != enemies.end(); i++)
		{
			(*i)->setHealth(-1);
		}
		enemyManager.updateChildren(frameTime);
		structureManager.reset();
		gameState.setCurrency(1500);
		structureManager.addBase(400, 200);
		gameState.setGamePhase(GameState::level2Play);
		break;

	case GameState::level2Build:
		break;

	case GameState::level2Play:
		structureManager.update(frameTime);
		gameMenu.update(frameTime);
		waves.update(frameTime);

		enemyManager.updateChildren(frameTime);
		if (structureManager.getPlacedThisFrame()) {
			enemyManager.updateStructures();
			enemyManager.findPaths();
		}
		if (waves.complete() && enemyManager.getNumChildren() == 0)
			gameState.setGamePhase(GameState::won);
		if (structureManager.getBaseHealth() <= 0)
			gameState.setGamePhase(GameState::lost);
		break;

	case GameState::won:
		if (!input->getMouseLButton() && lastClickState) {
			gameState.setGamePhase(GameState::intro);
		}
		break;

	case GameState::lost:
		if (!input->getMouseLButton() && lastClickState) {
			gameState.setGamePhase(GameState::intro);
		}
		break;

	default:
		break;
	}

	if(input->isKeyDown('R')){
		structureManager.setBaseHealth(structureManager.getBaseHealth() + 1000);
	}
	
	if(input->isKeyDown('C')){
		gameState.addCurrency(1000);
	}

	// exit on esc
	if(input->isKeyDown(VK_ESCAPE)){
		exitGame();
	}
	
	if (input->getMouseLButton()) lastClickState = true;
	
	else lastClickState = false;
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
		break;
	case GameState::instructions1:
		instruction1.draw();
		break;
	case GameState::instructions2:
		instruction2.draw();
		break;
	case GameState::level1Init:
		loadingscreen.draw();
		break;
	case GameState::level1Build:
		break;
	case GameState::level1Play:
		waves.update(frameTime);
		structureManager.draw();
		enemyManager.draw();
		gameMenu.draw();
		break;
	case GameState::level2Init:
		loadingscreen.draw();
		break;
	case GameState::level2Build:
		break;
	case GameState::level2Play:
		waves.update(frameTime);
		structureManager.draw();
		enemyManager.draw();
		gameMenu.draw();
		break;
	case GameState::won:
		winscreen.draw();
		break;
	case GameState::lost:
		losescreen.draw();
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
	loadingscreenTexture.onLostDevice();
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
	loadingscreenTexture.onResetDevice();
	Game::resetAll();
	return;
}
