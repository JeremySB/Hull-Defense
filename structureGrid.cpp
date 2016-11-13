#include "structureGrid.h"


StructureGrid::StructureGrid(void)
{
	this->cellHeight = CELL_HEIGHT;
	this->cellWidth = CELL_WIDTH;

	maxX = (int)(GAME_WIDTH / CELL_WIDTH) - 1;
	maxY = (int)(GAME_HEIGHT / CELL_HEIGHT) - 1;
}


StructureGrid::~StructureGrid(void)
{
}


void StructureGrid::addAtGridCoords(Structure* in, int x, int y)
{
	if(!(x >= 0 && y >= 0 && x <= maxX && y <= maxY))
		throw(GameError(gameErrorNS::WARNING, "Structure out of grid boundary"));

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

void StructureGrid::update(float frameTime)
{
	for (auto iter = structures.begin(); iter != structures.end(); iter++) {
		for (auto iter2 = iter->begin(); iter2 != iter->end(); iter2++)
		{
			(*iter2)->update(frameTime);
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