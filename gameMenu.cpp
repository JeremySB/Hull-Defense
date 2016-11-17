#include "gameMenu.h"


GameMenu::GameMenu(void)
{
	scoreFont = new TextDX();
	currencyFont = new TextDX();
	objDescriptionFont = new TextDX();
}


GameMenu::~GameMenu(void)
{
}

void GameMenu::initialize(Graphics* graphics, Game* game, Input* input){

	this->input = input;
	this->game = game;
	this->graphics = graphics;

	normalColor = graphicsNS::WHITE;
	scoreFont = new TextDX();
	currencyFont = new TextDX();
	objDescriptionFont = new TextDX();

	if(scoreFont->initialize(graphics, 15, true, false, "Calibri") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing score font"));
	if(currencyFont->initialize(graphics, 18, true, false, "Calibri") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing currency font"));
	if(objDescriptionFont->initialize(graphics, 25, true, false, "Calibri") == false)
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
	if (!turretMenu.initialize(graphics, 0, 0, 0, &turretmenuTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing turret menu"));

	// wall menu
	if (!wallMenu.initialize(graphics, 0, 0, 0, &wallmenuTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall menu"));

	// def menu
	if (!defMenu.initialize(graphics, 0, 0, 0, &defmenuTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Default menu"));
	
	towerMenu.setX(0);
	towerMenu.setY(GAME_HEIGHT-towerMenu.getHeight());
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
}

void GameMenu::update(float frameTime){
	if(menuActive){
		if(input->getMouseLButton()){
			if(input->getMouseX()>(0) && input->getMouseX()<(TABS_WIDTH) && input->getMouseY()>(GAME_HEIGHT-towerMenu.getHeight()) && input->getMouseY()<(GAME_HEIGHT-towerMenu.getHeight()+TABS_HEIGHT)){
				towerMenu.setVisible(true);
				wallMenu.setVisible(false);
				turretMenu.setVisible(false);
				defMenu.setVisible(false);
				menuActive = true;
			}else if(input->getMouseX()>(TABS_WIDTH) && input->getMouseX()<(2*TABS_WIDTH) &&  input->getMouseY()>(GAME_HEIGHT-towerMenu.getHeight()) && input->getMouseY()<(GAME_HEIGHT-towerMenu.getHeight()+TABS_HEIGHT)){
				towerMenu.setVisible(false);
				wallMenu.setVisible(true);
				turretMenu.setVisible(false);
				defMenu.setVisible(false);
				menuActive = false;
			}else if(input->getMouseX()>(2*TABS_WIDTH) && input->getMouseX()<(3*TABS_WIDTH) && input->getMouseY()>(GAME_HEIGHT-towerMenu.getHeight()) && input->getMouseY()<(GAME_HEIGHT-towerMenu.getHeight()+TABS_HEIGHT)){
				towerMenu.setVisible(false);
				wallMenu.setVisible(false);
				turretMenu.setVisible(true);
				defMenu.setVisible(false);
				menuActive = false;
			}
		}
	}else{
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
				menuActive = false;
			}else if(input->getMouseX()>(2*TABS_WIDTH) && input->getMouseX()<(3*TABS_WIDTH) && input->getMouseY()>(GAME_HEIGHT-TABS_HEIGHT) && input->getMouseY()<(GAME_HEIGHT)){
				towerMenu.setVisible(false);
				wallMenu.setVisible(false);
				turretMenu.setVisible(true);
				defMenu.setVisible(false);
				menuActive = false;
			}
		}
	}

	if(input->getMouseLButton() && input->getMouseY()<GAME_HEIGHT-towerMenu.getHeight()){
		defMenu.setVisible(true);
		towerMenu.setVisible(false);
		wallMenu.setVisible(false);
		turretMenu.setVisible(false);
		menuActive = false;
	}
	
}

void GameMenu::draw(){
	towerMenu.draw();
	wallMenu.draw();
	turretMenu.draw();
	defMenu.draw();
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