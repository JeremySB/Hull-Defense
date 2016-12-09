// Created by Samuel Casteel
#include "Waves.h"

Waves::Waves():betweenWaves(true),currentWave(0),timeBetweenWaves(10),timePassed(0){}

Waves::~Waves(){}

void Waves::initialize(EnemyManager* manager){
	this->manager = manager;
    for(int j = 0; j < 5; j++){
		waves[j].initialize(manager);
    }
}

void Waves::loadWaves(std::string filename){
	std::ifstream fin;
	
	fin.open(filename);

	if(fin.fail())
		return;

	std::string currentLine;
	
	for(int waveNum = 0; waveNum < 5 && !fin.eof(); waveNum++){
		float spawnTime;
		fin >> spawnTime;
		waves[waveNum].reset();
		waves[waveNum].setSpawnTime(spawnTime);
		getline(fin,currentLine);
		for(int i = 0; i < currentLine.size(); i++){
			currentLine[i] = toupper(currentLine[i]);
			if(currentLine[i] == 'H' || currentLine[i] == 'L' || currentLine[i] == 'M')
				waves[waveNum].addEnemy(currentLine[i]);
		}
	}
	currentWave = 0;
	timePassed = 0;
	betweenWaves = false;
}

void Waves::update(float frameTime){
    timePassed += frameTime;
    if(!betweenWaves && this->timeBetweenWaves <= timePassed && currentWave < 5 && !this->waves[currentWave].update(frameTime)){
        this->currentWave++;
        this->betweenWaves = true;
    }
    if(betweenWaves && manager->getNumChildren() == 0){
        this->betweenWaves = false;
        timePassed = 0;
    }
}

bool Waves::complete(){
	return currentWave == 5;
}