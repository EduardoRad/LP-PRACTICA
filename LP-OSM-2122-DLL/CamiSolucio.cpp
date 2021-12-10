#include "pch.h"
#include "CamiSolucio.h"

CamiSolucio& CamiSolucio::operator=(const CamiSolucio& cs)
{
	if (this != &cs)
	{
		if (!m_coords.empty())
			m_coords.clear();

		for (int i = 0; i < m_coords.size(); i++)
		{
			m_coords[i].lat = cs.m_coords[i].lat;
			m_coords[i].lon = cs.m_coords[i].lon;
		}
	}

	return *this;
}

std::vector<Coordinate> CamiSolucio::getCamiCoords()
{
	return this->m_coords;
}
