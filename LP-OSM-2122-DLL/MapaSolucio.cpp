#include "pch.h"
#include "MapaSolucio.h"

void MapaSolucio::getPdis(std::vector<PuntDeInteresBase*>& pdis)
{
	for (int punt = 0; punt < m_pdis.size(); punt++)
		pdis.push_back(m_pdis[punt]->clone());
}

void MapaSolucio::getCamins(std::vector<CamiBase*>& camins)
{
	for (int way = 0; way < m_camins.size(); way++)
	{
		camins.push_back(new CamiSolucio(m_camins[way]->getCamiCoords()));
	}
}

void MapaSolucio::parsejaXmlElements(std::vector<XmlElement>& xmlElements)
{

	if (!m_camins.empty())
	{
		std::vector<CamiBase*>::const_iterator itW;
		const int caminsSize = m_camins.size();

		for (itW = m_camins.begin(); itW != m_camins.end(); itW++)
			delete* itW;

		for (int i = 0; i < caminsSize; i++)
			m_camins.pop_back();
	}
	if (!m_pdis.empty())
	{
		std::vector<PuntDeInteresBase*>::const_iterator itP;
		const int pdisSize = m_pdis.size();

		for (itP = m_pdis.begin(); itP != m_pdis.end(); itP++)
			delete* itP;

		for (int i = 0; i < pdisSize; i++)
			m_pdis.pop_back();
	}

	const int SHOP = 1;
	const int REST = 2;

	std::vector<std::pair<std::string, Coordinate>> nodesCami;
	std::pair<std::string, Coordinate> auxNodes;

	for (int elementIt = 0; elementIt < xmlElements.size(); elementIt++)
	{
		if (xmlElements[elementIt].id_element == "node")
		{
			std::string name, id;
			Coordinate nodeCoord{ 0.0, 0.0 };
			std::string shop;
			std::string cuisine, wheelchair;
			bool puntInteres = false;
			bool puntWay = false;
			int piType = 0;

			for (int naIt = 0; naIt < xmlElements[elementIt].atributs.size(); naIt++)		// ATRIBUTS
			{
				if (xmlElements[elementIt].atributs[naIt].first == "id")
				{
					id = xmlElements[elementIt].atributs[naIt].second;
					continue;
				}
				if (xmlElements[elementIt].atributs[naIt].first == "lat")
				{
					nodeCoord.lat = stod(xmlElements[elementIt].atributs[naIt].second);
					continue;
				}
				if (xmlElements[elementIt].atributs[naIt].first == "lon")
				{
					nodeCoord.lon = stod(xmlElements[elementIt].atributs[naIt].second);
					continue;
				}
			}

			for (int nfIt = 0; nfIt < xmlElements[elementIt].fills.size(); nfIt++)		//FILLS
			{
				if (xmlElements[elementIt].fills[nfIt].first == "tag")
				{
					std::pair<std::string, std::string> nValorTag = Util::kvDeTag(xmlElements[elementIt].fills[nfIt].second);

					if (nValorTag.first == "highway" || nValorTag.first == "public_transport" || nValorTag.first == "access" || nValorTag.first == "entrance")
					{
						puntWay = true;
						continue;
					}
					else if (!puntWay)
					{
						if (nValorTag.first == "name")
						{
							puntInteres = true;
							name = nValorTag.second;
							continue;
						}
						if (nValorTag.first == "shop")
						{
							shop = nValorTag.second;
							piType = SHOP;
							continue;
						}
						if (nValorTag.first == "amenity" && nValorTag.second == "restaurant")
						{
							piType = REST;
							continue;
						}
						if (nValorTag.first == "cuisine")
						{
							cuisine = nValorTag.second;
							continue;
						}
						if (nValorTag.first == "wheelchair")
						{
							wheelchair = nValorTag.second;
							continue;
						}
					}
				}
			}

			if (xmlElements[elementIt].fills.empty())
				puntInteres = false;

			if (puntInteres)
			{
				if (piType == SHOP)
				{
					PuntDeInteresBotigaSolucio botiga(id, name, nodeCoord, shop);
					m_pdis.push_back(new PuntDeInteresBotigaSolucio(botiga));
				}
				else if (piType == REST)
				{
					PuntDeInteresRestaurantSolucio restaurant(id, name, nodeCoord, cuisine, wheelchair);
					m_pdis.push_back(new PuntDeInteresRestaurantSolucio(restaurant));
				}
				else if (piType == 0)
				{
					PuntDeInteresBase piBase(id, name, nodeCoord);
					m_pdis.push_back(new PuntDeInteresBase(piBase));
				}
			}
			else
			{
				std::pair<std::string, Coordinate> ncAux(id, nodeCoord);
				nodesCami.push_back(ncAux);
			}
		}
		else if (xmlElements[elementIt].id_element == "way")
		{

			bool nodesOrdenats = false;
			size_t contador = 0;

			while (!nodesOrdenats && contador < nodesCami.size())
			{
				nodesOrdenats = true;

				for (size_t i = 0; i < nodesCami.size() - 1; i++)
				{
					if (stod(nodesCami[i].first) > stod(nodesCami[i + 1].first))
					{
						nodesOrdenats *= false;
						auxNodes.first = nodesCami[i].first;
						auxNodes.second.lat = nodesCami[i].second.lat;
						auxNodes.second.lon = nodesCami[i].second.lon;
						nodesCami[i].first = nodesCami[i + 1].first;
						nodesCami[i].second.lat = nodesCami[i + 1].second.lat;
						nodesCami[i].second.lon = nodesCami[i + 1].second.lon;
						nodesCami[i + 1].first = auxNodes.first;
						nodesCami[i + 1].second.lat = auxNodes.second.lat;
						nodesCami[i + 1].second.lon = auxNodes.second.lon;
					}
					else
						nodesOrdenats *= true;
				}
				contador++;
			}


			bool highway = false;
			int wfhIt = 0;

			while (!highway && wfhIt < xmlElements[elementIt].fills.size())
			{
				if (xmlElements[elementIt].fills[wfhIt].first == "tag")
				{
					std::pair<std::string, std::string> wValorTag = Util::kvDeTag(xmlElements[elementIt].fills[wfhIt].second);

					if (wValorTag.first == "highway")			// BUSCAMOS EL HIJO HIGHWAY
						highway = true;
				}

				wfhIt++;
			}

			if (highway)
			{
				std::vector<Coordinate> wayCoords;

				for (int wfnIt = 0; wfnIt < xmlElements[elementIt].fills.size(); wfnIt++)		// BUSCAMOS LOS NODOS
				{
					if (xmlElements[elementIt].fills[wfnIt].first == "nd")
					{
						int iniciIt = 0;
						int finalIt = nodesCami.size();
						int posicio = 0;
						bool trobat = false;

						std::string ref = xmlElements[elementIt].fills[wfnIt].second[0].second;

						while (!trobat && iniciIt <= finalIt)
						{
							posicio = (iniciIt + finalIt) / 2;

							if (nodesCami[posicio].first == ref)
							{
								trobat = true;
							}
							else
							{
								if (stod(ref) < stod(nodesCami[posicio].first))
									finalIt = posicio - 1;
								else
									iniciIt = posicio + 1;
							}
						}

						if (trobat)
						{
							wayCoords.push_back(nodesCami[posicio].second);
						}

					}
				}
				if (!wayCoords.empty())
				{
					CamiSolucio cami(wayCoords);
					m_camins.push_back(new CamiSolucio(cami));
				}
			}

		}
	}
}