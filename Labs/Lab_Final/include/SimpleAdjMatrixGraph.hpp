#pragma once
#include <vector>
#include <list>
#include <iomanip>
#include <iostream>

class AdjacencyMatrixGraph
{
private:
    typedef std::vector<std::vector<bool>> Matrix;
    Matrix AdjMatrix;

public:
    AdjacencyMatrixGraph(int vertices = 0);
    void insertEdge(int src, int dest);
    void insertVertex();
    bool isAdjacent(int src, int dest);
    int inDegree(int vertex);
    void print();
    std::list<int> outgoingEdges(int u);
    int size();
};

AdjacencyMatrixGraph::AdjacencyMatrixGraph(int vertices)
    : AdjMatrix(vertices, std::vector<bool>(vertices, false)){};

void AdjacencyMatrixGraph::insertVertex()
{
    AdjMatrix.push_back(std::vector<bool>(AdjMatrix.size() + 1, false));
}

void AdjacencyMatrixGraph::insertEdge(int src, int dest)
{
    AdjMatrix[src][dest] = true;
}

std::list<int> AdjacencyMatrixGraph::outgoingEdges(int u)
{
    std::list<int> output;
    for (int w = 0; w < AdjMatrix[u].size(); w++)
    {
        if (AdjMatrix[u][w])
        {
            output.push_back(w);
        }
    }
    return output;
}

bool AdjacencyMatrixGraph::isAdjacent(int src, int dest)
{
    return AdjMatrix[src][dest];
}

int AdjacencyMatrixGraph::inDegree(int vertex)
{
    int inCounter = 0;
    for (auto row : AdjMatrix)
    {
        if (row[vertex])
        {
            inCounter++;
        }
    }
    return inCounter;
}
int AdjacencyMatrixGraph::size()
{
    return AdjMatrix.size();
}
void AdjacencyMatrixGraph::print()
{
    std::cout << std::setw(10) << "Vertex"
              << "Edges";
    for (int i = 0; i < AdjMatrix.size(); i++)
    {
        std::cout << '\n'
                  << std::setw(10)
                  << i;

        for (int j = 0; j < AdjMatrix[i].size(); j++)
        {
            if (AdjMatrix[i][j])
            {
                std::cout << j << ' ';
            }
        }
    }
    std::cout << '\n';
}