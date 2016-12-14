#include "mainMenu.h"
#include "graphics.h"
#include <string>

MainMenu::MainMenu(void)
{
}


MainMenu::~MainMenu(void)
{
}

void MainMenu::initialize(Graphics* graphics, Game* game, Input* input, Audio* audio){

	this->input = input;
	this->game = game;
	this->graphics = graphics;

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
	
	// center
	mainmenu.setX(0);
	mainmenu.setY(0);
	// Off right
	instruction0.setX(GAME_WIDTH);
	instruction0.setY(0);
	instruction1.setX(GAME_WIDTH);
	instruction1.setY(0);
	instruction2.setX(GAME_WIDTH);
	instruction2.setY(0);
	// Off top
	losescreen.setX(0);
	losescreen.setY(-GAME_HEIGHT);
	// Off bottom
	winscreen.setX(0);
	winscreen.setY(GAME_HEIGHT);
	// Off left	
	wavecomplete.setX(-GAME_WIDTH);
	wavecomplete.setY(0);
	loadingscreen.setX(-GAME_WIDTH);
	loadingscreen.setY(0);
	transitionImage.setX(-GAME_WIDTH);
	transitionImage.setY(0);

}

void MainMenu::update(float frameTime){
	switch (gameState->getGamePhase())
	{
		case GameState::intro:
			transitionImage.setVisible(false);
			loadingscreen.setVisible(false);
			wavecomplete.setVisible(false);
			losescreen.setVisible(false);
			winscreen.setVisible(false);
			instruction2.setVisible(false);
			instruction1.setVisible(false);
			instruction0.setVisible(false);
			mainmenu.setVisible(true);

			resetMenu();

			break;
		case GameState::instructions:
			transitionImage.setVisible(false);
			loadingscreen.setVisible(false);
			wavecomplete.setVisible(false);
			losescreen.setVisible(false);
			winscreen.setVisible(false);
			instruction2.setVisible(false);
			instruction1.setVisible(false);
			instruction0.setVisible(true);
			mainmenu.setVisible(true);

			if(instruction0.getX() > 1)
				transition(&instruction0, "right");

			break;
		case GameState::instructions1:
			transitionImage.setVisible(false);
			loadingscreen.setVisible(false);
			wavecomplete.setVisible(false);
			losescreen.setVisible(false);
			winscreen.setVisible(false);
			instruction2.setVisible(false);
			instruction1.setVisible(true);
			instruction0.setVisible(true);
			mainmenu.setVisible(false);

			if(instruction1.getX() > 1)
				transition(&instruction1, "right");
			
			break;
		case GameState::instructions2:
			transitionImage.setVisible(false);
			loadingscreen.setVisible(false);
			wavecomplete.setVisible(false);
			losescreen.setVisible(false);
			winscreen.setVisible(false);
			instruction2.setVisible(true);
			instruction1.setVisible(true);
			instruction0.setVisible(false);
			mainmenu.setVisible(false);

			if(instruction2.getX() > 1)
				transition(&instruction2, "right");

			break;
		case GameState::transition:
			transitionImage.setVisible(true);
			loadingscreen.setVisible(false);
			wavecomplete.setVisible(false);
			losescreen.setVisible(false);
			winscreen.setVisible(false);
			instruction2.setVisible(false);
			instruction1.setVisible(false);
			instruction0.setVisible(false);
			mainmenu.setVisible(false);

			transitionImage.setX(0);
			transitionImage.setY(0);
			break;
		case GameState::won:
			transitionImage.setVisible(false);
			loadingscreen.setVisible(false);
			wavecomplete.setVisible(false);
			losescreen.setVisible(false);
			winscreen.setVisible(true);
			instruction2.setVisible(false);
			instruction1.setVisible(false);
			instruction0.setVisible(false);
			mainmenu.setVisible(false);

			break;
		case GameState::lost:
			transitionImage.setVisible(false);
			loadingscreen.setVisible(false);
			wavecomplete.setVisible(false);
			losescreen.setVisible(true);
			winscreen.setVisible(false);
			instruction2.setVisible(false);
			instruction1.setVisible(false);
			instruction0.setVisible(false);
			mainmenu.setVisible(false);

			break;
		default:
			break;
	}
}

void MainMenu::draw(){
	mainmenu.draw();
	instruction0.draw();
	instruction1.draw();
	instruction2.draw();
	winscreen.draw();
	wavecomplete.draw();
	losescreen.draw();
	loadingscreen.draw();
	transitionImage.draw();
}

void MainMenu::onLostDevice(){
	mainmenuTexture.onLostDevice();
	instruction0Texture.onLostDevice();
	instruction1Texture.onLostDevice();
	instruction2Texture.onLostDevice();
	winscreenTexture.onLostDevice();
	losescreenTexture.onLostDevice();
	wavecompleteTexture.onLostDevice();
	loadingscreenTexture.onLostDevice();
	transitionTexture.onLostDevice();
}

void MainMenu::onResetDevice(){
	mainmenuTexture.onResetDevice();
	instruction0Texture.onResetDevice();
	instruction1Texture.onResetDevice();
	instruction2Texture.onResetDevice();
	winscreenTexture.onResetDevice();
	losescreenTexture.onResetDevice();
	wavecompleteTexture.onResetDevice();
	loadingscreenTexture.onResetDevice();
	transitionTexture.onResetDevice();
}

void MainMenu::transition(Image *image, std::string side){
	if(side == "right"){
		image->setScale(0);
		image->setY(0);
		if(image->getX() > 1){
			float newX = image->getX()-(image->getX()/10);
			image->setX(newX);
			image->setScale(1 - newX/GAME_WIDTH);
		}
		return;
	}else if(side == "left"){
		image->setScale(0);
		image->setY(0);
		if(image->getX() < GAME_WIDTH-1){
			float newX = image->getX()+(image->getX()/10);
			image->setX(newX);
			image->setScale(1 - newX/GAME_WIDTH);
		}
		return;
	}else if(side == "top"){
		image->setScale(0);
		image->setX(0);
		if(image->getY() < GAME_HEIGHT-1){
			float newY = image->getY()-(image->getY()/75);
			image->setY(newY);
			image->setScale(1 - newY/GAME_HEIGHT);
		}
		return;
	}else{
		image->setScale(0);
		image->setX(0);
		if(image->getY() > 1){
			float newY = image->getY()+(image->getY()/75);
			image->setY(newY);
			image->setScale(1 - newY/GAME_HEIGHT);
		}
		return;
	}
}

void MainMenu::resetMenu(){
	// center
	mainmenu.setX(0);
	mainmenu.setY(0);
	// Off right
	instruction0.setX(GAME_WIDTH);
	instruction0.setY(0);
	instruction1.setX(GAME_WIDTH);
	instruction1.setY(0);
	instruction2.setX(GAME_WIDTH);
	instruction2.setY(0);
	// Off top
	losescreen.setX(0);
	losescreen.setY(-GAME_HEIGHT);
	// Off bottom
	winscreen.setX(0);
	winscreen.setY(GAME_HEIGHT);
	// Off left	
	wavecomplete.setX(-GAME_WIDTH);
	wavecomplete.setY(0);
	loadingscreen.setX(-GAME_WIDTH);
	loadingscreen.setY(0);
	transitionImage.setX(-GAME_WIDTH);
	transitionImage.setY(0);
}