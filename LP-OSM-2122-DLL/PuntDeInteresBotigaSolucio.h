#pragma once
#include "PuntDeInteresBase.h"

class PuntDeInteresBotigaSolucio : public PuntDeInteresBase
{
private:
	std::string m_shopType;
public:
	PuntDeInteresBotigaSolucio() : m_shopType("undefinit") {};
	PuntDeInteresBotigaSolucio(std::string id, std::string name, Coordinate coord, std::string shopType)
		: PuntDeInteresBase(id, name, coord), m_shopType(shopType) {};

	~PuntDeInteresBotigaSolucio() {};
	std::string getShopType() const { return m_shopType; }
	unsigned int getColor();
	PuntDeInteresBotigaSolucio* clone();
};

