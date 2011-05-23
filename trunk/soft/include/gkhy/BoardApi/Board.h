#pragma once

#include "boardapi_global.h"

class BOARDAPI_EXPORT Board
{
public:
	Board* instance();

private:
	Board(void);
public:
	virtual ~Board(void);
};
