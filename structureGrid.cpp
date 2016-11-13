#include "structureGrid.h"


StructureGrid::StructureGrid(void)
{
	this->cellHeight = CELL_HEIGHT;
	this->cellWidth = CELL_WIDTH;
}


StructureGrid::~StructureGrid(void)
{
}


void StructureGrid::addAtGridCoords(Structure* in, int x, int y)
{
	
	structures[x][y] = in;
}

void StructureGrid::addAtPixelCoords(Structure* in, int x, int y)
{
	addAtGridCoords(in, gridXLoc(x), gridYLoc(y));
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