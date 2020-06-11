#include <iostream>
#include <string>
#include "AdjacencyListGraph.hpp"

using namespace std;

// A simple driver to test AdjacencyMapGraph class
// Created by T. Vo for CSCI 230

int main()
{
	AdjacencyListGraph g1(true); // use g1(true) for digraph
	Vertex *v1 = g1.insertVertex("A");
	Vertex *v2 = g1.insertVertex("B");
	Vertex *v3 = g1.insertVertex("C");
	Vertex *v4 = g1.insertVertex("D");
	Edge *e1 = g1.insertEdge(v1, v2, "test", 100.9);
	Edge *e2 = g1.insertEdge(v2, v3, "test2", 200);
	Edge *e3 = g1.insertEdge(v2, v4, "test2", 500);
	Edge *e4 = g1.insertEdge(v3, v4, "test3", 100);

	cout << "Find vertices for one edge: ";
	vector<Vertex *> endPoints = g1.endVertices(e1);
	Vertex *origin = endPoints[0];
	Vertex *dest = endPoints[1];
	cout << e1->getElement() << " --> " << origin->getElement() << " to " << dest->getElement() << endl;

	cout << "\nCurrent graph:" << endl;
	g1.print();
	cout << endl;

	std::cout << g1.shortestPath(v1, v4) << '\n';
	g1.printShortestPath(v1, v4);
	g1.print();

	return 0;
}