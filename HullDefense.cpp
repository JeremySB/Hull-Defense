
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

	structureManager.initialize(graphics, this, input, &gameState, &particleManager);
	particleManager.initialize(graphics, this);
	gameMenu.initialize(graphics, this, input, audio);
	gameMenu.setGameState(&gameState);

	enemyManager.initialize(this,structureManager.getGrid(),&gameState,audio);

	gameState.setGamePhase(GameState::intro);

	waves.initialize(&enemyManager);
	
	audio->playCue(BACKGROUND);
	// background1 texture
	if (!backgroundTexture.initialize(graphics, BACKGROUND_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background texture"));

	// background1 image
	if (!background.initialize(graphics, 0, 0, 0, &backgroundTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background"));
	//
	// background2 texture
	if (!background2Texture.initialize(graphics, BACKGROUND_IMAGE2))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background2 texture"));

	// background2 image
	if (!background2.initialize(graphics, 0, 0, 0, &background2Texture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background2"));
	//
	// background3 texture
	if (!background3Texture.initialize(graphics, BACKGROUND_IMAGE3))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background3 texture"));

	// background3 image
	if (!background3.initialize(graphics, 0, 0, 0, &background3Texture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background3"));
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

	// transition texture
	if (!transitionTexture.initialize(graphics, TRANSITION_SCREEN))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background texture"));
	
	// transition menu image
	if (!transitionImage.initialize(graphics, 0, 0, 0, &transitionTexture))
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
    //float frameTime = this->frameTime * 2;
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
		structureManager.loadLevel(1);
		particleManager.reset();
		gameState.setCurrency(1500);
        enemyManager.reset();
		gameState.setGamePhase(GameState::level1Play);
		break;

	case GameState::level1Play:
		structureManager.update(frameTime);
		particleManager.update(frameTime);
		gameMenu.update(frameTime);
		
		waves.update(frameTime);

		enemyManager.updateChildren(frameTime);
		enemies = enemyManager.getChildren();
		if (structureManager.getPlacedThisFrame()) {
			enemyManager.findPaths();
		} 
		if (waves.complete() && enemyManager.getNumChildren() == 0)
			gameState.setGamePhase(GameState::transition);
		if (structureManager.getBaseHealth() <= 0)
			gameState.setGamePhase(GameState::lost);
		break;

	case GameState::level2Init:
		enemies = enemyManager.getChildren();
		waves.loadWaves(LEVEL2WAVEFILE);
		structureManager.loadLevel(2);
		particleManager.reset();
		gameState.setCurrency(1500);
		gameState.setGamePhase(GameState::level2Play);
		enemyManager.reset();
		break;

	case GameState::level2Play:
		structureManager.update(frameTime);
		particleManager.update(frameTime);
		gameMenu.update(frameTime);
		waves.update(frameTime);

		enemyManager.updateChildren(frameTime);
		if (structureManager.getPlacedThisFrame()) {
			enemyManager.findPaths();
		}
		if (waves.complete() && enemyManager.getNumChildren() == 0)
			gameState.setGamePhase(GameState::transition);
		if (structureManager.getBaseHealth() <= 0)
			gameState.setGamePhase(GameState::lost);
		break;

	case GameState::level3Init:
		enemies = enemyManager.getChildren();
		waves.loadWaves(LEVEL3WAVEFILE);
		structureManager.reset();
		particleManager.reset();
		gameState.setCurrency(1500);
		structureManager.addBase(400, 200);
        enemyManager.reset();
		gameState.setGamePhase(GameState::level3Play);
		break;

	case GameState::level3Play:
		structureManager.update(frameTime);
		particleManager.update(frameTime);
		gameMenu.update(frameTime);
		waves.update(frameTime);

		enemyManager.updateChildren(frameTime);
		if (structureManager.getPlacedThisFrame()) {
			enemyManager.findPaths();
		}
		if (waves.complete() && enemyManager.getNumChildren() == 0)
			gameState.setGamePhase(GameState::won);
		if (structureManager.getBaseHealth() <= 0)
			gameState.setGamePhase(GameState::lost);
		break;

	case GameState::transition:
		
		if(!input->getMouseLButton() && lastClickState && (input->getMouseX()>0 && input->getMouseX()<GAME_WIDTH/3)){
			gameState.setGamePhase(GameState::level1Init);
		}else if(!input->getMouseLButton() && lastClickState && (input->getMouseX()>(GAME_WIDTH/3) && input->getMouseX()<2*(GAME_WIDTH/3))){
			gameState.setGamePhase(GameState::level2Init);
		}else if(!input->getMouseLButton() && lastClickState && (input->getMouseX()>2*(GAME_WIDTH/3) && input->getMouseX()<GAME_WIDTH)){
			gameState.setGamePhase(GameState::level3Init);
		}
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

	dxFont->setFontColor(graphicsNS::ORANGE);

	GameState::GamePhase phase = gameState.getGamePhase();
	switch (phase){
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

	case GameState::level1Play:
		background.draw();
		waves.update(frameTime);
		structureManager.draw();
		enemyManager.draw();
		particleManager.draw();
		gameMenu.draw();
		break;

	case GameState::level2Init:
		loadingscreen.draw();
		break;

	case GameState::level2Play:
		background2.draw();
		structureManager.draw();
		enemyManager.draw();
		particleManager.draw();
		gameMenu.draw();
		break;

	case GameState::level3Init:
		loadingscreen.draw();
		break;

	case GameState::level3Play:
		background3.draw();
		structureManager.draw();
		enemyManager.draw();
		particleManager.draw();
		gameMenu.draw();
		break;

	case GameState::transition:
		transitionImage.draw();
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
	particleManager.onLostDevice();
	gameMenu.onLostDevice();
	enemyManager.onLostDevice();
	loadingscreenTexture.onLostDevice();
	
	towermenuTexture.onLostDevice();
	turretmenuTexture.onLostDevice(); 
	wallmenuTexture.onLostDevice();
	defmenuTexture.onLostDevice();
	mainmenuTexture.onLostDevice();
	instruction0Texture.onLostDevice();
	instruction1Texture.onLostDevice();
	instruction2Texture.onLostDevice();
	
	winscreenTexture.onLostDevice();
	losescreenTexture.onLostDevice();
	wavecompleteTexture.onLostDevice();
	backgroundTexture.onLostDevice();
	background2Texture.onLostDevice();
	background3Texture.onLostDevice();

	transitionTexture.onLostDevice();

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
	particleManager.onResetDevice();
	gameMenu.onResetDevice();
	enemyManager.onResetDevice();
	loadingscreenTexture.onResetDevice();

	towermenuTexture.onResetDevice();
	turretmenuTexture.onResetDevice(); 
	wallmenuTexture.onResetDevice();
	defmenuTexture.onResetDevice();
	mainmenuTexture.onResetDevice();
	instruction0Texture.onResetDevice();
	instruction1Texture.onResetDevice();
	instruction2Texture.onResetDevice();
	
	winscreenTexture.onResetDevice();
	losescreenTexture.onResetDevice();
	wavecompleteTexture.onResetDevice();
	backgroundTexture.onResetDevice();
	background2Texture.onResetDevice();
	background3Texture.onResetDevice();

	transitionTexture.onResetDevice();

	Game::resetAll();
	return;
}
