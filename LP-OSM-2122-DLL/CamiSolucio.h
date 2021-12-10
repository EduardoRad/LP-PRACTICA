#pragma once
#include "CamiBase.h"

class CamiSolucio : public CamiBase
{
private:
	std::vector<Coordinate> m_coords;
public:
	~CamiSolucio() {};
	CamiSolucio(std::vector<Coordinate> coords) : m_coords(coords) {};
	CamiSolucio& operator=(const CamiSolucio& cs);
	std::vector<Coordinate> getCamiCoords();
};
