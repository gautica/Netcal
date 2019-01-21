#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <cstddef>

class Graph {

public:
	Graph() {
		edges[1] = 2;
		edges[2] = 3;
		edges[3] = 4;
		edges[4] = 5;
		edges[5] = 1;
	}

	void generateGraph();
private:
	std::map<int, int> edges;
};

#endif
