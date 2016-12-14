#include "gameMenu.h"
#include "graphics.h"
#include <string>

GameMenu::GameMenu(void)
{
	scoreFont = new TextDX();
	currencyFont = new TextDX();
	objDescriptionFont = new TextDX();
	lastClickState = false;
}


GameMenu::~GameMenu(void)
{
    delete scoreFont;
    delete currencyFont;
    delete objDescriptionFont;
}

void GameMenu::initialize(Graphics* graphics, Game* game, Input* input, Audio* audio){

	this->input = input;
	this->game = game;
	this->graphics = graphics;
	this->audio = audio;

	normalColor = graphicsNS::WHITE;

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

	// def texture
    if (!healthTexture.initialize(graphics,HEALTH_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing health texture"));

	// def texture
    if (!energyTexture.initialize(graphics,ENERGY_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing energy texture"));

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

	// def menu
	if (!energyImage.initialize(graphics, 0, 0, 0, &energyTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Default energy"));

	// def menu
	if (!healthImage.initialize(graphics, 0, 0, 0, &healthTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Default health"));
	
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

	energyImage.setScale(.11);
	healthImage.setScale(.20);
}

void GameMenu::update(float frameTime){
	if(gameState->getSelectionMode() == GameState::build){
		if(!input->getMouseLButton() && lastClickState){
			if((input->getMouseX()>0 && input->getMouseX()<GAME_WIDTH/4)&&input->getMouseY()>GAME_HEIGHT-towerMenu.getHeight()){
				// Photon Cannon
				gameState->setSelectionMode(GameState::photonCannonSelection);
			}else if((input->getMouseX()>GAME_WIDTH/4 && input->getMouseX()<2*(GAME_WIDTH/4))&&input->getMouseY()>GAME_HEIGHT-towerMenu.getHeight()){
				// Tower
				gameState->setSelectionMode(GameState::towerSelection);
			}else if((input->getMouseX()>2*(GAME_WIDTH/4) && input->getMouseX()<3*(GAME_WIDTH/4))&&input->getMouseY()>GAME_HEIGHT-towerMenu.getHeight()){
				// Turret
				gameState->setSelectionMode(GameState::turretSelection);
			}else if((input->getMouseX()>3*(GAME_WIDTH/4) && input->getMouseX()<GAME_WIDTH)&&input->getMouseY()>GAME_HEIGHT-towerMenu.getHeight()){
				// Wall
				gameState->setSelectionMode(GameState::wallSelection);
			}
			// build tab
			else if(input->getMouseX()>(0) && input->getMouseX()<(TABS_WIDTH) && input->getMouseY()>(GAME_HEIGHT-towerMenu.getHeight()) && input->getMouseY()<(GAME_HEIGHT-towerMenu.getHeight()+TABS_HEIGHT)){
				towerMenu.setVisible(true);
				repairMenu.setVisible(false);
				defMenu.setVisible(false);
				menuActive = true;
				gameState->setSelectionMode(GameState::build);
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
		if(!input->getMouseLButton() && lastClickState){
			// build
			if(input->getMouseX() >(0) && input->getMouseX()<(TABS_WIDTH) && input->getMouseY()>(GAME_HEIGHT-TABS_HEIGHT) && input->getMouseY()<(GAME_HEIGHT)){
				towerMenu.setVisible(true);
				repairMenu.setVisible(false);
				defMenu.setVisible(false);
				menuActive = true;
				gameState->setSelectionMode(GameState::build);
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

	/*if(input->getMouseLButton() && input->getMouseY()<GAME_HEIGHT-towerMenu.getHeight()){
		defMenu.setVisible(true);
		towerMenu.setVisible(false);
		repairMenu.setVisible(false);
		sellMenu.setVisible(false);
		menuActive = false;
	}*/

	if (gameState->getSelectionMode() == GameState::build) {
		towerMenu.setVisible(true);
		repairMenu.setVisible(false);
		sellMenu.setVisible(false);
		defMenu.setVisible(false);
		menuActive = true;
	}
	else if (gameState->getSelectionMode() == GameState::sell) {
		towerMenu.setVisible(false);
		repairMenu.setVisible(false);
		sellMenu.setVisible(true);
		defMenu.setVisible(false);
		menuActive = false;
	}
	else if (gameState->getSelectionMode() == GameState::repair) {
		towerMenu.setVisible(false);
		repairMenu.setVisible(true);
		sellMenu.setVisible(false);
		defMenu.setVisible(false);
		menuActive = false;
	}else if (gameState->getSelectionMode() == GameState::transition) {
		tranMenu.setVisible(true);
		towerMenu.setVisible(false);
		repairMenu.setVisible(false);
		sellMenu.setVisible(false);
		defMenu.setVisible(false);
		menuActive = false;
	}
	else {
		towerMenu.setVisible(false);
		repairMenu.setVisible(false);
		sellMenu.setVisible(false);
		defMenu.setVisible(true);
		menuActive = false;
	}

	if (input->getMouseLButton()) lastClickState = true;
	else lastClickState = false;
}

void GameMenu::draw(){
	towerMenu.draw();
	sellMenu.draw();
	repairMenu.draw();
	defMenu.draw();
	healthImage.draw();
	energyImage.draw();
	display();
}

void GameMenu::onLostDevice(){
	towermenuTexture.onLostDevice();
	turretmenuTexture.onLostDevice();
	wallmenuTexture.onLostDevice();
	defmenuTexture.onLostDevice();
	healthTexture.onLostDevice();
	energyTexture.onLostDevice();
}

void GameMenu::onResetDevice(){
	towermenuTexture.onResetDevice();
	turretmenuTexture.onResetDevice();
	wallmenuTexture.onResetDevice();
	defmenuTexture.onResetDevice();
	healthTexture.onResetDevice();
	energyTexture.onResetDevice();
}

void GameMenu::display(){
	//setCur(+1);
	energyStr = std::to_string(gameState->getCurrency());
	healthStr = std::to_string(gameState->getHealth());

	if(menuActive){
		healthImage.setX(GAME_WIDTH-MENU_RIGHT_WIDTH+10);
		healthImage.setY(GAME_HEIGHT-towerMenu.getHeight()+4);
		energyImage.setX(GAME_WIDTH-MENU_RIGHT_WIDTH + 125);
		energyImage.setY(GAME_HEIGHT-towerMenu.getHeight()+3);
		currencyFont->print(healthStr,GAME_WIDTH-MENU_RIGHT_WIDTH + 35,GAME_HEIGHT-towerMenu.getHeight()+4);
		currencyFont->print(energyStr,GAME_WIDTH-MENU_RIGHT_WIDTH + 150,GAME_HEIGHT-towerMenu.getHeight()+4);
	}else{
		healthImage.setX(GAME_WIDTH-MENU_RIGHT_WIDTH + 10);
		healthImage.setY(GAME_HEIGHT-22);
		energyImage.setX(GAME_WIDTH-MENU_RIGHT_WIDTH + 125);
		energyImage.setY(GAME_HEIGHT-23);
		currencyFont->print(healthStr,GAME_WIDTH-MENU_RIGHT_WIDTH + 35,GAME_HEIGHT-23);
		currencyFont->print(energyStr,GAME_WIDTH-MENU_RIGHT_WIDTH + 150,GAME_HEIGHT-23);
	}
}
