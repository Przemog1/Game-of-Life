#include "Cell.h"

Cell::Cell()
	:m_isAlive(false) {};

Cell::Cell(bool alive)
	:m_isAlive(alive) {};

void Cell::setAliveCellColor(const Pixel& pix)
{
	aliveCellColor = pix;
}

void Cell::setDeadCellColor(const Pixel& pix)
{
	deadCellColor = pix;
}

Pixel Cell::aliveCellColor = { 0,  255,   0 };
Pixel Cell::deadCellColor = { 0, 0, 0 };