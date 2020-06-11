#include "AdjacencyMatrix.h"
#include <limits>
#include <queue>

using namespace std;

struct location
{
    int distance;
    int vertex;
};

/* void dijkstra(AdjacencyMatrix G, int s)
{
    priority_queue<pair<int,int>> pq; //(Distance, Vertex)
    location l;
    for(int v = 0; v < 5; v++)
    {
        if(v == s)
        {

            l = pq.top();
        }
    }
    
    
} */

/* void shortestPath(AdjacencyMatrix G, int vertex)
{
    priority_queue<pair<int,int>> pq; //(Distance, Vertex)
    int D[5];
    D[vertex] = 0;
    pq.push(make_pair(0, vertex));
    for(int i = 1; i < 5; i++)
    {
        D[i] = 9999;
        pq.push(make_pair(D[i], i));
    }

    while(!(pq.empty()))
    {
        pair<int,int> top = pq.top();
        int u = top.second;
        pq.pop();
        for(int z = 0; z < 5; z++)
        {
            if(z != u)
            {
                if(G.isAdjacent(u,z))
                {
                    if(D[u] + G.weight(u,z) < D[z])
                    {
                        D[z] = D[u] + G.weight(u, z);
                        pq.push(make_pair(D[z], z));
                    }
                }
            }
        }
    }
    
    for(int i = 0 ; i < 5; i++)
    {
        cout << D[i] << endl;
    }
} */

void PrimJarnik(AdjacencyMatrix G)
{
    int D[5]; //D[v] ← 0
    D[0] = 0;
    vector<bool> inQueue(5, true);
    for (int i = 1; i < 5; i++)
    {
        D[i] = INT8_MAX; // D[u] ← +∞
    }

    AdjacencyMatrix T(v);                                    //Initialize T ← ∅
    priority_queue<pair<int, pair<int, pair<int, int>>>> pq; //(D[u], (u, null)) Initialize a priority queue Q with an entry ((u,null),D[u]) for each vertex u,where (u,null) is the element and D[u]) is the key.
    // Will let edge (-1, -1) denote null

    for (int u = 0; u < 5; u++)
    {
        pq.push(make_pair(D[u], make_pair(u, make_pair(-1, -1))));
    }

    while (!(pq.empty()))
    {
        pair<int, pair<int, pair<int, int>>> top = pq.top(); // (u,e) ← Q.removeMin()
        pq.pop();

        int v1 = top.second.second.first;
        int v2 = top.second.second.second;

        if (v1 != -1)
        {
            T.insertEdge(v1, v2, G.weight(v1, v2));
            inQueue[v1] = false;
        }

        int u = top.second.first;             // u ← Q.removeMin()
        pair<int, int> e = top.second.second; // e ← Q.removeMin()

        for (int z = 0; z < 5; z++)
        {
            if (G.isAdjacent(u, z) && inQueue[z])
            {
                if (G.weight(u, z) < D[z])
                {
                    D[z] = G.weight(u, z);
                    // make_pair( D[z], make_pair(z, make_pair(u, z)) );
                    pq.push(make_pair(D[z], make_pair(z, make_pair(u, z))));
                }
            }
        }
    }
    cout << " "
         << " a b c d e " << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << v[i] << " ";
        for (int j = 0; j < 5; j++)
        {
            cout << T.weight(i, j) << " ";
        }
        cout << endl;
    }
}

int main()
{
    vector<string> v = {"a", "b", "c", "d", "e"};

    AdjacencyMatrix a1(v);
    a1.insertEdge(0, 1, 3);
    a1.insertEdge(0, 3, 5);
    a1.insertEdge(0, 4, 5);
    a1.insertEdge(1, 2, 4);
    a1.insertEdge(2, 3, 2);
    a1.insertEdge(3, 4, 5);
    a1.insertEdge(2, 4, 3);

    /* cout << a1.weight(4,2);
    shortestPath(a1, 0); */
    PrimJarnik(a1);

    /*   for(int i = 0; i < v.size(); i++)
    {
        cout << "Vertex " << v[i];
        for(int j = 0; j < v.size(); j++)
        {
            if(a1.isAdjacent(i, j))
            cout << endl <<  "  adjacent to " << v[j];
        }
        cout << endl;
    } */
    system("pause");
    return 0;
}