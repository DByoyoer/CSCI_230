#include <iostream>
#include <vector>
#include <queue>
#include <climits>

typedef std::vector<std::vector<int>> Matrix;

class PQComp
{
public:
    bool operator()(std::pair<int, int> a, std::pair<int, int> b)
    {
        return a > b;
    }
};

Matrix transitiveClosure(Matrix g);
int shortestPath(Matrix g, int src, int dest);

int main()
{
    Matrix transitiveGraph = {{0, 0, 0, 1, 1},
                              {1, 0, 1, 0, 0},
                              {0, 0, 0, 1, 0},
                              {0, 0, 0, 0, 1},
                              {0, 0, 1, 0, 0}};

    Matrix dijkstraGraph = {{0, 0, 0, 5, 10},
                            {3, 0, 4, 0, 0},
                            {0, 0, 0, 2, 0},
                            {0, 0, 0, 0, 3},
                            {0, 0, 6, 0, 0}};

    std::cout << shortestPath(dijkstraGraph, 0, 2) << '\n';
}

Matrix transitiveClosure(Matrix g)
{
    Matrix output = g;
    for (int k = 0; k < g.size(); k++)
    {
        for (int i = 0; i < g.size(); i++)
        {
            for (int j = 0; j < g.size(); j++)
            {
                if (g[i][k] == 1 && g[k][j] == 1)
                {
                    output[i][j] = 1;
                }
            }
        }
    }
    return output;
}

int shortestPath(Matrix g, int src, int dest)
{
    std::vector<std::pair<int, int>> distance;
    for (int i = 0; i < g.size(); i++)
    {
        distance.push_back(std::make_pair(i, INT_MAX));
    }
    distance[src].second = 0;
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, PQComp> Q;
    Q.push(distance[src]);
    int u;
    std::vector<bool> isInQueue(g.size(), true);
    while (!Q.empty())
    {
        u = Q.top().first;
        isInQueue[u] = false;
        if (u == dest)
        {
            break;
        }
        Q.pop();
        for (int z = 0; z < g.size(); z++)
        {
            if (g[u][z] != 0 && isInQueue[z])
            {
                if (distance[u].second + g[u][z] < distance[z].second)
                {
                    distance[z].second = distance[u].second + g[u][z];
                    Q.push(distance[z]);
                }
            }
        }
    }

    return distance[dest].second;
}