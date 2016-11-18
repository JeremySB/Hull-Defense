#pragma once
class GameState
{
public:
	GameState();
	~GameState();

	enum GamePhase { intro, instructions, level1Init, level1Build, level1Play, level2Init, level2Build, level2Play, won, lost };
	enum SelectionMode { normal, wallSelection, towerSelection, turretSelection, sell };

	GamePhase getGamePhase() { return gamePhase; }
	void setGamePhase(GamePhase in) { gamePhase = in; }

	SelectionMode getSelectionMode() { return selectionMode; }
	void setSelectionMode(SelectionMode in) { selectionMode = in; }

	int getCurrency() { return currency; }
	void setCurrency(int in) { currency = in; }
	void addCurrency(int in) { currency += in; }

	int getHealth() { return health; }
	void setHealth(int in) { health = in; }
	
private:
	GamePhase gamePhase;
	SelectionMode selectionMode;
	int currency; 
	int health;
};

