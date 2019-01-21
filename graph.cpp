#include "graph.h"
#include <iostream>
#include <fstream>

void Graph::generateGraph() {
	std::ofstream g;
	g.open("graph.txt");
	g << "graph {\n";
	g << "node [shape=circle,fixedsize=true,width=0.9];\n";
	for (auto it=edges.begin(); it != edges.end(); it++) {
		g << it->first << " -- " << it->second << "\n";
	}

	g << "overlap=false\n";
	g << "label=\"test\"\n";
	g << "fontsize=12;";
	g << "}";
	g.close();
}
