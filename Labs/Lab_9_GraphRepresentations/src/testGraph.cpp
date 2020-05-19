#include <iostream>
#include <string>
#include "AdjacencyListGraph.hpp"

using namespace std;

// A simple driver to test AdjacencyMapGraph class
// Created by T. Vo for CSCI 230

int main()
{
	AdjacencyListGraph g1; // use g1(true) for digraph
	Vertex *v1 = g1.insertVertex("A");
	Vertex *v2 = g1.insertVertex("B");
	Vertex *v3 = g1.insertVertex("C");
	Edge *e1 = g1.insertEdge(v1, v2, 100);
	Edge *e2 = g1.insertEdge(v1, v3, 200);

	cout << "Find vertices for one edge: ";
	vector<Vertex *> endPoints = g1.endVertices(e1);
	Vertex *origin = endPoints[0];
	Vertex *dest = endPoints[1];
	cout << e1->getElement() << " --> " << origin->getElement() << " to " << dest->getElement() << endl;

	cout << "Find edge for two vertices: ";
	Edge *myEdge = g1.getEdge(v1, v3);
	cout << v1->getElement() << " to " << v3->getElement() << " --> " << myEdge->getElement() << endl;

	cout << "\nCurrent graph:" << endl;
	g1.print();
	cout << endl;

	return 0;
}