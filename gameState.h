#pragma once
class GameState
{
public:
	GameState();
	~GameState();

	enum GamePhase { intro, instructions, instructions1, instructions2, level1Init, level1Play, level2Init, level2Play, level3Init, level3Play,Play, transition, won, lost };
	enum SelectionMode { normal, build, wallSelection, towerSelection, photonCannonSelection, turretSelection, sell, repair };

	GamePhase getGamePhase() { return gamePhase; }
	void setGamePhase(GamePhase in) { gamePhase = in; }

	SelectionMode getSelectionMode() { return selectionMode; }
	void setSelectionMode(SelectionMode in);

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

