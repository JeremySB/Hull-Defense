
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
	level1waves = new Waves(&enemyManager);
	level2waves = new Waves(&enemyManager);
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
		enemies = enemyManager.getChildren();

		
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

		enemyManager.setSpawn(VECTOR2(0,GAME_HEIGHT/2));

		for (auto i = enemies.begin(); i != enemies.end(); i++)
		{
			(*i)->setHealth(-1);
		}
		enemyManager.updateChildren(frameTime);
		level1waves->currentWave = 0;
		structureManager.reset();
		structureManager.addBase(950, 10);
		gameState.setCurrency(1500);
		gameState.setGamePhase(GameState::level1Play);
		break;
	case GameState::level1Play:
		structureManager.update(frameTime);
		gameMenu.update(frameTime);
		level1waves->update(frameTime);
		enemyManager.updateChildren(frameTime);
		enemies = enemyManager.getChildren();
		if (structureManager.getPlacedThisFrame()) {
			enemyManager.updateStructures();
			enemyManager.findPaths();
		} 
		if (level1waves->currentWave == 5 && enemyManager.getNumChildren() == 0)
			gameState.setGamePhase(GameState::level2Init);
		if (structureManager.getBaseHealth() <= 0)
			gameState.setGamePhase(GameState::lost);
		break;
	case GameState::level2Init:
		enemies = enemyManager.getChildren();

		
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

		enemyManager.setSpawn(VECTOR2( (enemyManager.getSpawn().x ? 0 : GAME_WIDTH - CELL_WIDTH), GAME_HEIGHT/2));

		for (auto i = enemies.begin(); i != enemies.end(); i++)
		{
			(*i)->setHealth(-1);
		}
		enemyManager.updateChildren(frameTime);
		level2waves->currentWave = 0;
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
		level2waves->update(frameTime);

		enemyManager.updateChildren(frameTime);
		if (structureManager.getPlacedThisFrame()) {
			enemyManager.updateStructures();
			enemyManager.findPaths();
		}
		if (level2waves->currentWave == 5 && enemyManager.getNumChildren() == 0)
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

	//structureManager.update(frameTime);
	//gameMenu.update(frameTime);
	//enemyManager.updateChildren(frameTime);

	/* if(structureManager.getPlacedThisFrame()){
	enemyManager.updateStructures();
	enemyManager.findPaths();
	}*/
	//level1waves->update(frameTime);
	if(input->isKeyDown('R')){
		structureManager.setBaseHealth(structureManager.getBaseHealth() + 1000);
	}
	if(input->isKeyDown('C')){
		gameState.addCurrency(1000);
	}
	// exit on esc
	if(input->isKeyDown(VK_ESCAPE)){
		//exit(1);
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
