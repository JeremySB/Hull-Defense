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
	for (auto iter = structures.begin(); iter != structures.end(); iter++) {
		for (auto iter2 = iter->begin(); iter2 != iter->end(); iter2++)
		{
			safeDelete(*iter2);
		}
	}
}


void StructureGrid::addAtGridCoords(Structure* in, int x, int y)
{
	if(!(x >= 0 && y >= 0 && x + in->getWidthInGrid() <= maxX && y + in->getHeightInGrid() <= maxY))
		throw(GameError(gameErrorNS::WARNING, "Structure out of grid boundary"));

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
	// have to loop through to delete multi-cell structures
	Structure* toDelete = atGridCoords(x, y);

	for (auto iter = structures.begin(); iter != structures.end(); iter++) {
		for (auto iter2 = iter->begin(); iter2 != iter->end(); iter2++)
		{
			if (*iter2 == toDelete)
				*iter2 = nullptr;
		}
	}
	safeDelete(toDelete);
}

void StructureGrid::draw()
{
	for (auto iter = structures.begin(); iter != structures.end(); iter++) {
		for (auto iter2 = iter->begin(); iter2 != iter->end(); iter2++)
		{
			if (*iter2) 
				(*iter2)->draw();
		}
	}
}

void StructureGrid::update(float frameTime)
{
	for (auto iter = structures.begin(); iter != structures.end(); iter++) {
		for (auto iter2 = iter->begin(); iter2 != iter->end(); iter2++)
		{
			if(*iter2) (*iter2)->update(frameTime);
		}
	}
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