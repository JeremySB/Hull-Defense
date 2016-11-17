// Created by Jeremy Bost

#include "structureGrid.h"


StructureGrid::StructureGrid(void) : structures((int)(GAME_WIDTH / CELL_WIDTH) + 1, 
										std::vector<Structure*>((int)(GAME_HEIGHT / CELL_HEIGHT) + 1, nullptr))
{
	this->cellHeight = CELL_HEIGHT;
	this->cellWidth = CELL_WIDTH;

	maxX = (int)(GAME_WIDTH / CELL_WIDTH);
	maxY = (int)(GAME_HEIGHT / CELL_HEIGHT);
}


StructureGrid::~StructureGrid(void)
{
	for (int i = 0; i < structures.size(); i++) {
		for (int j = 0; j < structures[i].size(); j++)
		{
			if (structures[i][j])
				removeAtGridCoords(i, j);
		}
	}
}


void StructureGrid::addAtGridCoords(Structure* in, int x, int y)
{
	if(!(x >= 0 && y >= 0 && x + in->getWidthInGrid() <= maxX && y + in->getHeightInGrid() <= maxY))
		throw(GameError(gameErrorNS::WARNING, "Structure out of grid boundary"));

	structureList.push_back(in);

	in->setX(pixelXLoc(x));
	in->setY(pixelYLoc(y));

	// fill in multiple cells if structure is wider or taller than one cell
	for (int i = 0; i < in->getWidthInGrid(); i++) {
		for (int j = 0; j < in->getHeightInGrid(); j++) {
			structures[x + i][y + j] = in;
		}
	}
}

void StructureGrid::addAtPixelCoords(Structure* in, int x, int y)
{
	addAtGridCoords(in, gridXLoc(x), gridYLoc(y));
}

void StructureGrid::removeAtGridCoords(int x, int y)
{
	if (!(x >= 0 && y >= 0 && x <= maxX && y <= maxY))
		throw(GameError(gameErrorNS::WARNING, "Structure out of grid boundary"));
	
	// have to loop through to delete multi-cell structures
	Structure* toDelete = atGridCoords(x, y);

	structureList.remove(toDelete);

	for (auto iter = structures.begin(); iter != structures.end(); iter++) {
		for (auto iter2 = iter->begin(); iter2 != iter->end(); iter2++)
		{
			if (*iter2 == toDelete)
				*iter2 = nullptr;
		}
	}
	safeDelete(toDelete);
}

Structure * StructureGrid::atGridCoords(int x, int y)
{
	if ((x >= 0 && y >= 0 && x <= maxX && y <= maxY))
		return structures[x][y];
	return nullptr;
}

void StructureGrid::draw()
{
	for (auto iter = structureList.begin(); iter != structureList.end(); iter++) {
		if (*iter)
			(*iter)->draw();
	}

	for (auto iter = structureList.begin(); iter != structureList.end(); iter++) {
		if (*iter)
			(*iter)->drawProjectiles();
	}
}

void StructureGrid::update(float frameTime)
{
	for (auto iter = structureList.begin(); iter != structureList.end(); iter++) {
		if (*iter)
			(*iter)->update(frameTime);
	}
}

std::list<Structure*> StructureGrid::getStructures()
{
	return structureList;
}

int StructureGrid::gridXLoc(int pixelLoc)
{
	return (int)(pixelLoc / cellWidth);
}

int StructureGrid::gridYLoc(int pixelLoc)
{
	return (int)(pixelLoc / cellHeight);
}

int StructureGrid::pixelXLoc(int gridLoc)
{
	return gridLoc * cellWidth;
}

int StructureGrid::pixelYLoc(int gridLoc)
{
	return gridLoc * cellHeight;
}