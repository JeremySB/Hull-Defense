#pragma once
class GameState
{
public:
	GameState();
	~GameState();

	enum GamePhase { intro, instructions, instructions1, instructions2, level1Init, level2Init, level3Init, play, load, transition, won, lost };
	enum SelectionMode { normal, build, wallSelection, towerSelection, photonCannonSelection, turretSelection, sell, repair };

	GamePhase getGamePhase() { return gamePhase; }
	void setGamePhase(GamePhase in) { gamePhase = in; }

	SelectionMode getSelectionMode() { return selectionMode; }
	void setSelectionMode(SelectionMode in);

	int getCurrency() { return currency; }
	void setCurrency(int in) { currency = in; }
	void addCurrency(int in) { currency += in; }

	int getHealth() { return health; }
	float getTimer() {return timer; }
	void setHealth(int in) { health = in; }
	
private:
	GamePhase gamePhase;
	SelectionMode selectionMode;
	int currency; 
	int health;
	float timer;
};

