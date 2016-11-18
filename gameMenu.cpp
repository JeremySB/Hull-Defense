#include "gameMenu.h"
#include "graphics.h"
#include <string>

GameMenu::GameMenu(void)
{
	scoreFont = new TextDX();
	currencyFont = new TextDX();
	objDescriptionFont = new TextDX();
}


GameMenu::~GameMenu(void)
{
}

void GameMenu::initialize(Graphics* graphics, Game* game, Input* input, Audio* audio){

	this->input = input;
	this->game = game;
	this->graphics = graphics;
	this->audio = audio;

	normalColor = graphicsNS::WHITE;
	scoreFont = new TextDX();
	currencyFont = new TextDX();
	objDescriptionFont = new TextDX();

	if(scoreFont->initialize(graphics, 20, true, false, "Calibri") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing score font"));
	if(currencyFont->initialize(graphics, 20, true, false, "Calibri") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing currency font"));
	if(objDescriptionFont->initialize(graphics, 20, true, false, "Calibri") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing objDescription font"));
	scoreFont->setFontColor(normalColor);
	currencyFont->setFontColor(normalColor);
	objDescriptionFont->setFontColor(normalColor);

	// tower menu
	if (!towermenuTexture.initialize(graphics, TOWERMENU_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tower menu texture"));

	// turret menu
	if (!turretmenuTexture.initialize(graphics, TURRETMENU_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tower menu texture"));

	// wall menu
	if (!wallmenuTexture.initialize(graphics, WALLMENU_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tower menu texture"));

   	// def texture
    if (!defmenuTexture.initialize(graphics,DEFMENU_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing def menu texture"));

	// tower menu
	if (!towerMenu.initialize(graphics, 0, 0, 0, &towermenuTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tower menu"));

	// turret menu
	if (!repairMenu.initialize(graphics, 0, 0, 0, &turretmenuTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing turret menu"));

	// wall menu
	if (!sellMenu.initialize(graphics, 0, 0, 0, &wallmenuTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall menu"));

	// def menu
	if (!defMenu.initialize(graphics, 0, 0, 0, &defmenuTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Default menu"));
	
	towerMenu.setX(0);
	towerMenu.setY(GAME_HEIGHT-towerMenu.getHeight());
	repairMenu.setX(0);
	repairMenu.setY(GAME_HEIGHT-TABS_HEIGHT);
	sellMenu.setX(0);
	sellMenu.setY(GAME_HEIGHT-TABS_HEIGHT);
	defMenu.setX(0);
	defMenu.setY(GAME_HEIGHT-TABS_HEIGHT);

	menuActive = false;

	towerMenu.setVisible(false);
	sellMenu.setVisible(false);
	repairMenu.setVisible(false);
	defMenu.setVisible(true);
}

void GameMenu::update(float frameTime){
	if(menuActive){
		if(input->getMouseLButton()){
			if((input->getMouseX()>0 && input->getMouseX()<GAME_WIDTH/3)&&input->getMouseY()>GAME_HEIGHT-towerMenu.getHeight()){
				// Tower
			}else if((input->getMouseX()>GAME_WIDTH/3 && input->getMouseX()<2*(GAME_WIDTH/3))&&input->getMouseY()>GAME_HEIGHT-towerMenu.getHeight()){
				// Turret
			}else if((input->getMouseX()>2*(GAME_WIDTH/3) && input->getMouseX()<GAME_WIDTH)&&input->getMouseY()>GAME_HEIGHT-towerMenu.getHeight()){
				// Wall
			}
			// build tab
			else if(input->getMouseX()>(0) && input->getMouseX()<(TABS_WIDTH) && input->getMouseY()>(GAME_HEIGHT-towerMenu.getHeight()) && input->getMouseY()<(GAME_HEIGHT-towerMenu.getHeight()+TABS_HEIGHT)){
				towerMenu.setVisible(true);
				repairMenu.setVisible(false);
				defMenu.setVisible(false);
				menuActive = true;
				gameState->setSelectionMode(GameState::normal);
			}
			// sell tab
			else if(input->getMouseX()>(TABS_WIDTH) && input->getMouseX()<(2*TABS_WIDTH) &&  input->getMouseY()>(GAME_HEIGHT-towerMenu.getHeight()) && input->getMouseY()<(GAME_HEIGHT-towerMenu.getHeight()+TABS_HEIGHT)){
				towerMenu.setVisible(false);
				repairMenu.setVisible(false);
				defMenu.setVisible(false);
				menuActive = false;
				gameState->setSelectionMode(GameState::sell);
			}
			// repair tab
			else if(input->getMouseX()>(2*TABS_WIDTH) && input->getMouseX()<(3*TABS_WIDTH) && input->getMouseY()>(GAME_HEIGHT-towerMenu.getHeight()) && input->getMouseY()<(GAME_HEIGHT-towerMenu.getHeight()+TABS_HEIGHT)){
				towerMenu.setVisible(false);
				repairMenu.setVisible(true);
				defMenu.setVisible(false);
				menuActive = false;
				gameState->setSelectionMode(GameState::repair);
			}
		}
	}else{
		if(input->getMouseLButton()){
			// build
			if(input->getMouseX() >(0) && input->getMouseX()<(TABS_WIDTH) && input->getMouseY()>(GAME_HEIGHT-TABS_HEIGHT) && input->getMouseY()<(GAME_HEIGHT)){
				towerMenu.setVisible(true);
				repairMenu.setVisible(false);
				defMenu.setVisible(false);
				menuActive = true;
				gameState->setSelectionMode(GameState::normal);
			}
			// sell
			else if(input->getMouseX()>(TABS_WIDTH) && input->getMouseX()<(2*TABS_WIDTH) && input->getMouseY()>(GAME_HEIGHT-TABS_HEIGHT) && input->getMouseY()<(GAME_HEIGHT)){
				towerMenu.setVisible(false);
				repairMenu.setVisible(false);
				defMenu.setVisible(false);
				menuActive = false;
				gameState->setSelectionMode(GameState::sell);
			}
			// repair
			else if(input->getMouseX()>(2*TABS_WIDTH) && input->getMouseX()<(3*TABS_WIDTH) && input->getMouseY()>(GAME_HEIGHT-TABS_HEIGHT) && input->getMouseY()<(GAME_HEIGHT)){
				towerMenu.setVisible(false);
				repairMenu.setVisible(true);
				defMenu.setVisible(false);
				menuActive = false;
				gameState->setSelectionMode(GameState::repair);
			}
		}
	}

	if(input->getMouseLButton() && input->getMouseY()<GAME_HEIGHT-towerMenu.getHeight()){
		defMenu.setVisible(true);
		towerMenu.setVisible(false);
		repairMenu.setVisible(false);
		menuActive = false;
	}

	if (gameState->getSelectionMode() == GameState::sell) {
		sellMenu.setVisible(true);
		defMenu.setVisible(false);
	}
	else {
		sellMenu.setVisible(false);
		defMenu.setVisible(true);
	}
}

void GameMenu::draw(){
	towerMenu.draw();
	sellMenu.draw();
	repairMenu.draw();
	defMenu.draw();
	display();
}

void GameMenu::onLostDevice(){
	towermenuTexture.onLostDevice();
	turretmenuTexture.onLostDevice();
	wallmenuTexture.onLostDevice();
	defmenuTexture.onLostDevice();
}

void GameMenu::onResetDevice(){
	towermenuTexture.onResetDevice();
	turretmenuTexture.onResetDevice();
	wallmenuTexture.onResetDevice();
	defmenuTexture.onResetDevice();
}

void GameMenu::display(){
	//setCur(+1);
	currencyStr = "Energy: " + std::to_string(gameState->getCurrency()) + " - Base Health: " + std::to_string(gameState->getHealth());
	if(menuActive){
		currencyFont->print(currencyStr,GAME_WIDTH-MENU_RIGHT_WIDTH,GAME_HEIGHT-towerMenu.getHeight());
	}else{
		currencyFont->print(currencyStr,GAME_WIDTH-MENU_RIGHT_WIDTH,GAME_HEIGHT-22);
	}
}
