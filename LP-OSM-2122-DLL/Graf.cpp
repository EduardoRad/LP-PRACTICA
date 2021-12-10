#include "pch.h"
#include "Graf.h"

Graf::Graf(const std::vector<Coordinate>& nodes, const std::vector<std::vector<int>>& parNodes)
{
	m_numNodes = nodes.size();
	m_nodes.resize(m_numNodes);
	m_veins.resize(m_numNodes);
	m_numArestes = parNodes.size();

	m_nodes = nodes;

	for (int i = 0; i < parNodes.size(); i++)
	{
		if ((parNodes[i][0] < m_numNodes) && (parNodes[i][1] < m_numNodes) && (parNodes[i][0] >= 0) && (parNodes[i][1] >= 0))
		{
			m_veins[parNodes[i][0]].emplace_back(std::pair<int,double>{ parNodes[i][1], 1.0 });
			m_veins[parNodes[i][1]].emplace_back(std::pair<int,double>{ parNodes[i][0], 1.0 });
		}
	}
}

Graf::Graf(const std::vector<Coordinate>& nodes, const std::vector<std::vector<int>>& parNodes, const std::vector<double>& pesos)
{
	m_numNodes = nodes.size();
	m_nodes.resize(m_numNodes);
	m_veins.resize(m_numNodes);
	m_numArestes = parNodes.size();

	m_nodes = nodes;

	for (int i = 0; i < parNodes.size(); i++)
	{
		if ((parNodes[i][0] < m_numNodes) && (parNodes[i][1] < m_numNodes) && (parNodes[i][0] >= 0) && (parNodes[i][1] >= 0))
		{
			m_veins[parNodes[i][0]].emplace_back(std::pair<int, double>{ parNodes[i][1], pesos[i] });
			m_veins[parNodes[i][1]].emplace_back(std::pair<int, double>{ parNodes[i][0], pesos[i] });
		}
	}
}

void Graf::afegirAresta(int posNode1, int posNode2, double pes)
{
	m_veins[posNode1].emplace_back(std::make_pair(posNode2, pes));
	m_veins[posNode2].emplace_back(std::make_pair(posNode1, pes));
}

void Graf::eliminarAresta(int posNode1, int posNode2)
{
	std::list<std::pair<int, double>>::const_iterator it1, it2;
	for (it1 = m_veins[posNode1].begin(); it1 != m_veins[posNode1].end(); ++it1)
	{
		if (it1->first == posNode2)
			m_veins[posNode1].erase(it1);
	}
	for (it2 = m_veins[posNode2].begin(); it2 != m_veins[posNode2].end(); ++it2)
	{
		if (it2->first == posNode1)
			m_veins[posNode2].erase(it2);
	}
}

void Graf::afegirNode(Coordinate node)
{
	std::list<std::pair<int, double>> lista;
	m_nodes.push_back(node);
	m_veins.push_back(lista);
}
