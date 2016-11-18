#include "gameState.h"



GameState::GameState()
{
	currency = 0;
	health = 0;
	selectionMode = normal;
	gamePhase = intro;
}


GameState::~GameState()
{
}

void GameState::setSelectionMode(SelectionMode in)
{
	selectionMode = in;
}
