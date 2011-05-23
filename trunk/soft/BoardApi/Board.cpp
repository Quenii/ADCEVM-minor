#include "..\include\gkhy\BoardApi\Board.h"

Board::Board(void)
{
}

Board::~Board(void)
{
}

Board* Board::instance()
{
	static Board _inst;
	return &_inst;
}
