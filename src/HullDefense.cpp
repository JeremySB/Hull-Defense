
#include "HullDefense.h"

//=============================================================================
// Constructor
//=============================================================================
HullDefense::HullDefense() : Game()
{
	loseTimeout = -1;
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
	mainMenu.setGameState(&gameState);
	mainMenu.initialize(graphics, this, input, audio);

	enemyManager.initialize(this, structureManager.getGrid(), &gameState, audio, &particleManager);

	gameState.setGamePhase(GameState::intro);

	waves.initialize(&enemyManager);
	
	audio->playCue(BACKGROUND_CUE);
	// background1 texture
	if (!backgroundTexture.initialize(graphics, BACKGROUND_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background texture"));

	// background image
	if (!background.initialize(graphics, 0, 0, 0, &backgroundTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background"));
	//
	// background2 texture
	if (!background2Texture.initialize(graphics, BACKGROUND_IMAGE2))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background2 texture"));
	
	//
	// background3 texture
	if (!background3Texture.initialize(graphics, BACKGROUND_IMAGE3))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background3 texture"));
	
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
	//float frameTime = this->frameTime * 2;
	switch (gameState.getGamePhase())
	{
	case GameState::intro:
		if(!input->getMouseLButton() && lastClickState){
			if(input->getMouseX()>GAME_WIDTH/2){
				gameState.setGamePhase(GameState::instructions);
			}else{
				//gameState.setGamePhase(GameState::level1Init);
				gameState.setGamePhase(GameState::transition);
			}
		}
		if(input->isKeyDown('1')){
			gameState.setGamePhase(GameState::level1Init);
		}
		if (input->isKeyDown('2')) {
			gameState.setGamePhase(GameState::level2Init);
		}
		if (input->isKeyDown('3')) {
			gameState.setGamePhase(GameState::level3Init);
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
		waves.loadWaves(LEVEL1WAVEFILE);
		structureManager.loadLevel(1);
		particleManager.reset();
		gameState.setCurrency(1000);
		enemyManager.reset();

		if (!background.initialize(graphics, 0, 0, 0, &backgroundTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background"));

		gameState.setGamePhase(GameState::play);//GameState::level1Play);
		break;

	case GameState::level2Init:
		waves.loadWaves(LEVEL2WAVEFILE);
		structureManager.loadLevel(2);
		particleManager.reset();
		gameState.setCurrency(1000);
		enemyManager.reset();

		if (!background.initialize(graphics, 0, 0, 0, &background2Texture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background"));

		gameState.setGamePhase(GameState::play);//GameState::level2Play);
		break;

	case GameState::level3Init:
		waves.loadWaves(LEVEL3WAVEFILE);
		structureManager.loadLevel(3);
		gameState.setCurrency(1200);
		particleManager.reset();
		enemyManager.reset();

		if (!background.initialize(graphics, 0, 0, 0, &background3Texture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background"));

		gameState.setGamePhase(GameState::play);//GameState::level3Play);
		break;
	case GameState::play:
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
		if (structureManager.getBaseHealth() <= 0 && loseTimeout <= 0)
			loseTimeout = 0.7;

		// pause on base death
		if (loseTimeout > 0)
		{
			loseTimeout -= frameTime;
			if (loseTimeout <= 0)
			{
				gameState.setGamePhase(GameState::lost);
				loseTimeout = -1;
			}
		}

		break;

	case GameState::transition:
		if(!input->getMouseLButton() && lastClickState){
			float mouseX = input->getMouseX();
			float mouseY = input->getMouseY();
			if(mouseX > 0 && mouseX < 55 && mouseY > 0 && mouseY < 25)
				gameState.setGamePhase(GameState::intro);
			else if(mouseX > 0 && mouseX < GAME_WIDTH/3)
				gameState.setGamePhase(GameState::level1Init);
			else if(mouseX > (GAME_WIDTH/3) && mouseX < 2*(GAME_WIDTH/3))
				gameState.setGamePhase(GameState::level2Init);
			else if(input->getMouseX() > 2*(GAME_WIDTH/3) && input->getMouseX() < GAME_WIDTH)
				gameState.setGamePhase(GameState::level3Init);
			
			}
		break;

	case GameState::won:
		if (!input->getMouseLButton() && lastClickState) {
			gameState.setGamePhase(GameState::transition);
		}
		break;

	case GameState::lost:
		if (!input->getMouseLButton() && lastClickState) {
			gameState.setGamePhase(GameState::transition);
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

	mainMenu.update(frameTime);
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
		//mainmenu.draw();
		break;

	case GameState::instructions:
		//instruction0.draw();
		break;

	case GameState::instructions1:
		//instruction1.draw();
		break;

	case GameState::instructions2:
		//instruction2.draw();
		break;

	case GameState::level1Init:
		//loadingscreen.draw();
		break;

	case GameState::level2Init:
		//loadingscreen.draw();
		break;

	case GameState::level3Init:
		//loadingscreen.draw();
		break;

	case GameState::play:
		background.draw();
		structureManager.draw();
		enemyManager.draw();
		particleManager.draw();
		gameMenu.draw();
		break;

	case GameState::transition:
		background.draw();
		structureManager.draw();
		enemyManager.draw();
		particleManager.draw();
		gameMenu.draw();
		break;

	case GameState::won:
		background.draw();
		structureManager.draw();
		enemyManager.draw();
		particleManager.draw();
		gameMenu.draw();
		break;

	case GameState::lost:
		background.draw();
		structureManager.draw();
		enemyManager.draw();
		particleManager.draw();
		gameMenu.draw();
		break;

	default:
		break;
	}

	mainMenu.draw();

	graphics->spriteEnd();                  // end drawing sprites

}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void HullDefense::releaseAll()
{
	dxFont->onLostDevice();
	//menuTexture.onLostDevice();
	structureManager.onLostDevice();
	particleManager.onLostDevice();
	gameMenu.onLostDevice();
	enemyManager.onLostDevice();
    mainMenu.onLostDevice();
	//loadingscreenTexture.onLostDevice();
	
	towermenuTexture.onLostDevice();
	turretmenuTexture.onLostDevice(); 
	wallmenuTexture.onLostDevice();
	defmenuTexture.onLostDevice();
	//mainmenuTexture.onLostDevice();
	//instruction0Texture.onLostDevice();
	//instruction1Texture.onLostDevice();
	//instruction2Texture.onLostDevice();
	
	//winscreenTexture.onLostDevice();
	//losescreenTexture.onLostDevice();
	//wavecompleteTexture.onLostDevice();
	backgroundTexture.onLostDevice();
	background2Texture.onLostDevice();
	background3Texture.onLostDevice();

	//transitionTexture.onLostDevice();

	Game::releaseAll();
	return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void HullDefense::resetAll()
{
	//menuTexture.onResetDevice();
	dxFont->onResetDevice();
	structureManager.onResetDevice();
	particleManager.onResetDevice();
	gameMenu.onResetDevice();
	enemyManager.onResetDevice();
    mainMenu.onResetDevice();
	//loadingscreenTexture.onResetDevice();

	towermenuTexture.onResetDevice();
	turretmenuTexture.onResetDevice(); 
	wallmenuTexture.onResetDevice();
	defmenuTexture.onResetDevice();
	//mainmenuTexture.onResetDevice();
	//instruction0Texture.onResetDevice();
	//instruction1Texture.onResetDevice();
	//instruction2Texture.onResetDevice();
	
	//winscreenTexture.onResetDevice();
	//losescreenTexture.onResetDevice();
	//wavecompleteTexture.onResetDevice();
	backgroundTexture.onResetDevice();
	background2Texture.onResetDevice();
	background3Texture.onResetDevice();

	//transitionTexture.onResetDevice();

	Game::resetAll();
	return;
}
