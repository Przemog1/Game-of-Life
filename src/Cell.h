#pragma once

#include "Graphics\RGBTexture\RGBTexture.h"

class Cell
{
public:
	Cell();
	Cell(bool alive);

	inline void setState(bool alive) { m_isAlive = alive; }
	inline bool isAlive() const { return m_isAlive; }

	static void setAliveCellColor(const Pixel& pix);
	static void setDeadCellColor(const Pixel& pix);

	inline static const Pixel& getAliveCellColor() { return aliveCellColor; };
	inline static const Pixel& getDeadCellColor() { return deadCellColor; };

private:
	bool m_isAlive;

	static Pixel aliveCellColor;
	static Pixel deadCellColor;
};
