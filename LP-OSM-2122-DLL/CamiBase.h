#pragma once

#include "Common.h"
#include <vector>

class CamiBase {
public:
	virtual ~CamiBase() {};
	virtual std::vector<Coordinate> getCamiCoords() = 0;
};

