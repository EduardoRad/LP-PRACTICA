#include "pch.h"
#include "PuntDeInteresBotigaSolucio.h"

unsigned int PuntDeInteresBotigaSolucio::getColor()
{
	unsigned int color; 

	if (m_shopType == "supermarket")
		color = SUPERMARKET;
	else if (m_shopType == "tobacco")
		color = TOBACCO;
	else if (m_shopType == "bakery")
		color = BAKERY;
	else
		color = OTHERS;

	return color;
}

PuntDeInteresBotigaSolucio* PuntDeInteresBotigaSolucio::clone()
{
	return new PuntDeInteresBotigaSolucio(*this);
}
