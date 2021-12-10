#pragma once
#include "Common.h"
#include "MapaSolucio.h"
#include <vector>
#include <list>

class Graf
{
public:
	Graf() : m_numNodes(0), m_numArestes(0) {};
	Graf(const std::vector<Coordinate>& nodes, const std::vector<std::vector<int>>& parNodes);
	Graf(const std::vector<Coordinate>& nodes, const std::vector<std::vector<int>>& parNodes, const std::vector<double>& pesos);
	~Graf();
	int getNumNodes() { return m_numNodes; }
	void afegirAresta(int posNode1, int posNode2);
	void afegirAresta(int posNode1, int posNode2, double pes);
	void eliminarAresta(int posNode1, int posNode2);
	void afegirNode(Coordinate node);
	void eliminarNode(Coordinate node);
private:
	std::vector<std::list<std::pair<int, double>>> m_veins;
	std::vector<Coordinate> m_nodes;
	int m_numNodes;
	int m_numArestes;
};

