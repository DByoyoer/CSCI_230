#include <stack>
#include "BFS.hpp"
#include "LabDFS.hpp"
#include "AdjacencyListGraph.hpp"

std::list<Vertex *> TopologicalSort(Graph *G);

int main()
{
    Graph *test = new AdjacencyListGraph();

    Vertex *A = test->insertVertex("A");
    Vertex *B = test->insertVertex("B");
    Vertex *C = test->insertVertex("C");
    Vertex *D = test->insertVertex("D");
    Vertex *E = test->insertVertex("E");

    test->insertEdge(A, B, 1);
    test->insertEdge(A, D, 2);
    test->insertEdge(B, C, 3);
    test->insertEdge(C, D, 4);
    test->insertEdge(D, E, 5);
    LabDFS depthSearch(test);
    depthSearch.initialize();

    std::cout << "Depth First Search: \n";

    depthSearch.dfsTraversal(A);

    BFS breadthSearch(test);
    breadthSearch.initialize();
    std::cout << "\nBreadth First Search:\n";
    breadthSearch.bfsTraversal(A);
    //DAG Driver

    Graph *dagTest = new AdjacencyListGraph(true);
    Vertex *a = dagTest->insertVertex("A");
    Vertex *b = dagTest->insertVertex("B");
    Vertex *c = dagTest->insertVertex("C");
    Vertex *d = dagTest->insertVertex("D");
    Vertex *e = dagTest->insertVertex("E");
    dagTest->insertEdge(b, a, 100);
    dagTest->insertEdge(b, c, 200);
    dagTest->insertEdge(c, d, 300);
    dagTest->insertEdge(a, d, 400);
    dagTest->insertEdge(d, e, 500);
    std::cout << "\nDAG Topological Ordering\n";
    std::list<Vertex *> sortedVertices = TopologicalSort(dagTest);
    int i = 1;
    for (auto v : sortedVertices)
    {
        std::cout << v->getElement() << " " << '\n';
    }
}

std::list<Vertex *> TopologicalSort(Graph *G)
{
    std::stack<Vertex *> S;
    std::list<Vertex *> sorted;
    std::map<Vertex *, int> incounter;
    for (auto u : G->getVertices())
    {
        incounter[u] = G->inDegree(u);
        if (G->inDegree(u) == 0)
        {
            S.push(u);
        }
    }
    int i = 1;
    Vertex *u;
    Vertex *w;
    while (!S.empty())
    {
        u = S.top();
        sorted.push_back(u);
        S.pop();
        i++;
        for (auto e : G->outgoingEdges(u))
        {
            w = G->opposite(u, e);
            incounter[w]--;
            if (incounter[w] == 0)
            {
                S.push(w);
            }
        }
    }
    return sorted;
}