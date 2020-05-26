#include <iostream>
#include <vector>
#include <stack>
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
void shortestPath(Matrix g, int src, int dest);
void printPath(const std::vector<int> &parent, int dest);
void printMatrix(const Matrix &input);

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

    std::cout << "Starter matrix/graph: \n";
    printMatrix(transitiveGraph);
    std::cout << "\nUpdated matrix/graph: \n";
    Matrix update = transitiveClosure(transitiveGraph);
    printMatrix(update);
    std::cout << '\n';
    shortestPath(dijkstraGraph, 1, 4);
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

void printMatrix(const Matrix &input)
{
    for (auto row : input)
    {
        std::cout << "[";
        for (auto elem : row)
        {
            std::cout << elem << "  ";
        }
        std::cout << "]\n";
    }
}

void shortestPath(Matrix g, int src, int dest)
{
    typedef std::pair<int, int> int_pair;
    std::vector<std::pair<int, int>> distance;
    std::vector<int> parent(g.size());
    parent[src] = -1;
    for (int i = 0; i < g.size(); i++)
    {
        distance.push_back(std::make_pair(INT_MAX, i));
    }
    distance[src].first = 0;
    std::priority_queue<int_pair, std::vector<int_pair>, std::greater<int_pair>> Q;
    Q.push(distance[src]);
    int u;
    std::vector<bool> isInQueue(g.size(), true);
    while (!Q.empty())
    {
        u = Q.top().second;
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
                if (distance[u].first + g[u][z] < distance[z].first)
                {
                    distance[z].first = distance[u].first + g[u][z];
                    Q.push(distance[z]);
                    parent[z] = u;
                }
            }
        }
    }
    std::cout << "Distance from vertex " << src
              << " to vertex " << dest << ": "
              << distance[dest].first
              << "\nExtra Credit: \n";
    printPath(parent, dest);
}

void printPath(const std::vector<int> &parent, int dest)
{
    int i = dest;
    std::stack<int> path;
    path.push(dest);

    while (parent[i] != -1)
    {
        path.push(parent[i]);
        i = parent[i];
    }

    std::cout << "Path taken: ";

    while (!path.empty())
    {
        std::cout << path.top() << " ";
        path.pop();
    }
    std::cout << '\n';
}
