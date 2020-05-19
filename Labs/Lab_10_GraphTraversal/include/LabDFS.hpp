#pragma once
#include "DFS.h"
#include <iostream>

class LabDFS : public DFS
{
public:
    LabDFS(Graph *g) : DFS(g) {}

protected:
    void traverseDiscovery(Edge *e, Vertex *from);
};

void LabDFS::traverseDiscovery(Edge *e, Vertex *from)
{
    std::cout << from->getElement() << " " << e->getElement() << " "
              << graph->opposite(from, e)->getElement() << "\n";
}
