#pragma once

#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> v = {"a", "b", "c", "d", "e"};

class AdjacencyMatrix
{
private:
    vector<string> vertices;
    vector<vector<int>> edges;

public:
    AdjacencyMatrix(vector<string> verts) 
    {
        vertices = verts;
        vector<vector<int>> temp(vertices.size(), vector<int> (vertices.size()));
        edges = temp;

    
    }

    void insertEdge(int v1, int v2, int weight)
    {
        edges[v1][v2] = weight;
    }

    int weight(int v1, int v2)
    {
        return edges[v1][v2];
    }

    bool isAdjacent(int v1, int v2)
    {
        //cout << "v1: " << v1 << " " << "v2: " << v2 << " " << "weight: " << edges[v1][v2] << endl;
        bool isAdj = false;
        if(edges[v1][v2] > 0 )
            isAdj = true;
        return isAdj;
    }



};


