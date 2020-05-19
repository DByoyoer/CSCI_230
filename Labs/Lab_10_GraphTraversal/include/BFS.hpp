#pragma once
#include <iostream>
#include "Decorator.h"
#include "Graph.h"

class BFS
{
public:
    BFS(Graph *g);
    void initialize();
    void bfsTraversal(Vertex *v);
    void visit(Vertex *v) { v->set("visited", yes); }
    void visit(Edge *e) { e->set("visited", yes); }
    void unvisit(Vertex *v) { v->set("visited", no); }
    void unvisit(Edge *e) { e->set("visited", no); }
    bool isVisited(Vertex *v) { return v->get("visited") == yes; }
    bool isVisited(Edge *e) { return e->get("visited") == yes; }

private:
    Graph *graph;
    Vertex *start;
    Object *yes, *no;
};

BFS::BFS(Graph *g) : graph(g), yes(new Object), no(new Object) {}

void BFS::initialize()
{
    std::list<Vertex *> verts = graph->getVertices();
    for (auto v : verts)
    {
        unvisit(v);
    }

    std::list<Edge *> edges = graph->getEdges();
    for (auto e : edges)
    {
        unvisit(e);
    }
}

void BFS::bfsTraversal(Vertex *v)
{
    //initialize level 0 to contain the start vertex
    std::vector<std::list<Vertex *>> levels(1, std::list<Vertex *>(1, v));
    int i = 0;
    Vertex *w;
    while (!levels[i].empty())
    {
        levels.push_back(std::list<Vertex *>());
        for (auto u : levels[i])
        {
            for (auto e : graph->outgoingEdges(u))
            {
                if (!isVisited(e))
                {
                    w = graph->opposite(u, e);
                    visit(e);
                    if (!isVisited(w))
                    {
                        visit(w);
                        levels[i + 1].push_back(w);
                        std::cout << u->getElement() << " " << e->getElement()
                                  << " " << w->getElement() << "\n";
                    }
                }
            }
        }
        i++;
    }
}