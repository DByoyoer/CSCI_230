#pragma once
#include <iostream>
#include <queue>
#include <list>
#include <vector>
#include "Graph.h"

// Created by T. Vo for CSCI 230
// Based on Java version of Goodrich book w/o template
// and minimal exception handling
// Some operations are incomplete and there are provisions
// to change from map to a list/vector for adjacency list
//Modified by Michael Morikawa for Proj 4

#define INF (double)99999999

class AdjacencyListGraph : public Graph
{
private:
    bool isDirected;
    std::list<Vertex *> vertices;
    std::list<Edge *> edges;

    /* A vertex of an adjacency list graph representation. */
    class InnerVertex : public Vertex
    {
    private:
        std::string element;
        //Position<Vertex<V>> pos;d
        Vertex *pos;
        InnerVertex *predecessor;
        double distance;

        std::list<std::pair<Vertex *, Edge *>> *outgoing;
        std::list<std::pair<Vertex *, Edge *>> *incoming;

    public:
        /* Constructs a new InnerVertex instance storing the given element. */
        InnerVertex(std::string elem, bool graphIsDirected = false)
        {
            element = elem;
            outgoing = new std::list<std::pair<Vertex *, Edge *>>();
            if (graphIsDirected)
                incoming = new std::list<std::pair<Vertex *, Edge *>>();
            else
                incoming = outgoing; // if undirected, alias outgoing map
        }

        /* Returns the element associated with the vertex. */
        std::string getElement()
        {
            return element;
        }

        /* Stores the position of this vertex within the graph's vertex list. */
        void setPosition(Vertex *p)
        {
            pos = p;
        }

        /* Returns the position of this vertex within the graph's vertex list. */
        Vertex *getPosition()
        {
            return pos;
        }

        //returns list of outgoing edges
        std::list<std::pair<Vertex *, Edge *>> *getOutgoing()
        {
            return outgoing;
        }

        /* Returns list of incoming edges. */
        std::list<std::pair<Vertex *, Edge *>> *getIncoming()
        {
            return incoming;
        }

        InnerVertex *getPredecessor()
        {
            return predecessor;
        }

        void setPredecessor(InnerVertex *u)
        {
            predecessor = u;
        }

        double getDistance()
        {
            return distance;
        }

        void setDistance(double n)
        {
            distance = n;
        }

    }; //------------ end of InnerVertex class ------------

    struct VertexComp
    {
        bool operator()(InnerVertex *a, InnerVertex *b)
        {
            return a->getDistance() > b->getDistance();
        }
    };

    //---------------- nested InnerEdge class ----------------
    /* An edge between two vertices. */
    class InnerEdge : public Edge
    {
    private:
        std::string element;
        double weight;
        Edge *pos;
        std::vector<Vertex *> endpoints;

    public:
        /* Constructs InnerEdge instance from u to v, storing the given element. */
        InnerEdge(Vertex *u, Vertex *v, std::string elem, double w)
        {
            element = elem;
            weight = w;
            endpoints.push_back(u);
            endpoints.push_back(v);
        }

        /* Returns the element associated with the edge. */
        std::string getElement()
        {
            return element;
        }

        double getWeight()
        {
            return weight;
        }

        void setWeight(double w)
        {
            weight = w;
        }

        /* Returns reference to the endpoint array. */
        std::vector<Vertex *> getEndpoints()
        {
            return endpoints;
        }

        /* Stores the position of this edge within the graph's vertex list. */
        void setPosition(Edge *p)
        {
            pos = p;
        }

        /* Returns the position of this edge within the graph's vertex list. */
        Edge *getPosition()
        {
            return pos;
        }
    }; //------------ end of InnerEdge class ------------

public:
    /*
	* Constructs an empty graph.
	* The parameter determines whether this is an undirected or directed graph.
	*/
    AdjacencyListGraph(bool directed = false)
    {
        isDirected = directed;
    }

    ~AdjacencyListGraph()
    {
        // should deallocate memory here
    }

    /* Returns the number of vertices of the graph */
    int numVertices()
    {
        return static_cast<int>(vertices.size());
    }

    /* Returns the number of edges of the graph */
    int numEdges()
    {
        return static_cast<int>(edges.size());
    }

    /* Returns the vertices of the graph as an iterable collection */
    std::list<Vertex *> getVertices()
    {
        return vertices;
    }

    /* Returns the edges of the graph as an iterable collection */
    std::list<Edge *> getEdges()
    {
        return edges;
    }

    /*
	* Returns the number of edges leaving vertex v.
	* Note that for an undirected graph, this is the same result
	* returned by inDegree
	* throws IllegalArgumentException if v is not a valid vertex?
	*/
    int outDegree(Vertex *v) // throws IllegalArgumentException;
    {
        InnerVertex *vert = static_cast<InnerVertex *>(v);
        return static_cast<int>(vert->getOutgoing()->size());
    }

    /**
	* Returns the number of edges for which vertex v is the destination.
	* Note that for an undirected graph, this is the same result
	* returned by outDegree
	* throws IllegalArgumentException if v is not a valid vertex
	*/
    int inDegree(Vertex *v) // throws IllegalArgumentException;
    {
        InnerVertex *vert = static_cast<InnerVertex *>(v);
        return static_cast<int>(vert->getIncoming()->size());
    }

    /*
	* Returns an iterable collection of edges for which vertex v is the origin.
	* Note that for an undirected graph, this is the same result
	* returned by incomingEdges.
	* throws IllegalArgumentException if v is not a valid vertex
	*/
    std::vector<Edge *> outgoingEdges(Vertex *v) // throws IllegalArgumentException;
    {
        std::vector<Edge *> temp;
        std::list<std::pair<Vertex *, Edge *>> *listPtr = static_cast<InnerVertex *>(v)->getOutgoing();
        for (auto it = listPtr->begin(); it != listPtr->end(); ++it)
        {
            temp.push_back(it->second);
        }
        return temp;
    }

    /*
	* Returns an iterable collection of edges for which vertex v is the destination.
	* Note that for an undirected graph, this is the same result
	* returned by outgoingEdges.
	* throws IllegalArgumentException if v is not a valid vertex
	*/
    std::vector<Edge *> incomingEdges(Vertex *v) // throws IllegalArgumentException;
    {
        std::vector<Edge *> temp;
        std::list<std::pair<Vertex *, Edge *>> *listPtr = static_cast<InnerVertex *>(v)->getIncoming();
        for (auto it = listPtr->begin(); it != listPtr->end(); ++it)
        {
            temp.push_back(it->second);
        }
        return temp;
    }

    /* Returns the edge from u to v, or null if they are not adjacent. */
    Edge *getEdge(Vertex *u, Vertex *v) // throws IllegalArgumentException;
    {
        Edge *temp = nullptr;
        std::list<std::pair<Vertex *, Edge *>> *listPtr = static_cast<InnerVertex *>(u)->getOutgoing();
        auto it = listPtr->begin();
        for (it, it = listPtr->begin(); it != listPtr->end(); it++)
        {
            if (it->first == v)
            {
                break;
            }
        }
        if (it != listPtr->end())
            temp = it->second;
        return temp; // origin.getOutgoing().get(v);    // will be null if no edge from u to v
    }

    /*
	* Returns the vertices of edge e as an array of length two.
	* If the graph is directed, the first vertex is the origin, and
	* the second is the destination.  If the graph is undirected, the
	* order is arbitrary.
	*/
    std::vector<Vertex *> endVertices(Edge *e) // throws IllegalArgumentException;
    {
        std::vector<Vertex *> endpoints = static_cast<InnerEdge *>(e)->getEndpoints();
        return endpoints;
    }

    /* Returns the vertex that is opposite vertex v on edge e. */
    Vertex *opposite(Vertex *v, Edge *e) // throws IllegalArgumentException;
    {
        std::vector<Vertex *> endpoints = static_cast<InnerEdge *>(e)->getEndpoints();

        if (endpoints[0] == v)
            return endpoints[1];
        else
            return endpoints[0];
    }

    /* Inserts and returns a new vertex with the given element. */
    Vertex *insertVertex(std::string element)
    {
        Vertex *v = new InnerVertex(element, isDirected);
        vertices.push_back(v);
        static_cast<InnerVertex *>(v)->setPosition(vertices.back());
        return v;
    }

    /*
	* Inserts and returns a new edge between vertices u and v, storing given element.
	*
	* throws IllegalArgumentException if u or v are invalid vertices, or if an edge already exists between u and v.
	*/
    Edge *insertEdge(Vertex *u, Vertex *v, std::string element, double weight = 1) // throws IllegalArgumentException;
    {
        Edge *e = new InnerEdge(u, v, element, weight);
        edges.push_back(e);
        static_cast<InnerEdge *>(e)->setPosition(edges.back());
        InnerVertex *origin = static_cast<InnerVertex *>(u);
        InnerVertex *dest = static_cast<InnerVertex *>(v);
        (origin->getOutgoing())->push_back(std::pair<Vertex *, Edge *>(v, e));
        (dest->getIncoming())->push_back(std::pair<Vertex *, Edge *>(u, e));

        return e;
    }

    /* Removes a vertex and all its incident edges from the graph. */
    void removeVertex(Vertex *v) // throws IllegalArgumentException;
    {
        for (Edge *e : outgoingEdges(v))
        {
            removeEdge(e);
        }
        for (Edge *e : incomingEdges(v))
        {
            removeEdge(e);
        }
        vertices.remove(v);
    }

    /* Removes an edge from the graph. */
    void removeEdge(Edge *e)
    {
        if (e == nullptr)
        {
            return;
        }
        std::vector<Vertex *> endpoints = static_cast<InnerEdge *>(e)->getEndpoints();
        static_cast<InnerVertex *>(endpoints[0])->getOutgoing()->remove(std::make_pair(endpoints[1], e));
        static_cast<InnerVertex *>(endpoints[1])->getIncoming()->remove(std::make_pair(endpoints[0], e));
        edges.remove(static_cast<InnerEdge *>(e)->getPosition());
    }

    double getWeight(Edge *e)
    {
        return static_cast<InnerEdge *>(e)->getWeight();
    }

    void setWeight(Edge *e, double weight)
    {
        static_cast<InnerEdge *>(e)->setWeight(weight);
    }

    double shortestPath(Vertex *src, Vertex *dest, bool weighted = true)
    {
        InnerVertex *source = static_cast<InnerVertex *>(src);
        InnerVertex *destination = static_cast<InnerVertex *>(dest);
        std::priority_queue<InnerVertex *, std::vector<InnerVertex *>, VertexComp> PQ;
        for (auto v : vertices)
        {
            static_cast<InnerVertex *>(v)->setDistance(INF);
            static_cast<InnerVertex *>(v)->setPredecessor(0);
        }
        source->setDistance(0);
        PQ.push(source);
        InnerVertex *currentVert;
        InnerVertex *adjVert;
        double adjustedDist;
        double edgeWeight;
        while (!PQ.empty())
        {
            currentVert = PQ.top();
            if (currentVert == destination)
            {
                break;
            }
            PQ.pop();
            for (auto e : outgoingEdges(currentVert))
            {
                if (weighted)
                {
                    edgeWeight = static_cast<InnerEdge *>(e)->getWeight();
                }
                else
                {
                    edgeWeight = 1;
                }

                adjVert = static_cast<InnerVertex *>(opposite(currentVert, e));
                adjustedDist = currentVert->getDistance() + edgeWeight;
                if (adjustedDist < adjVert->getDistance())
                {
                    adjVert->setDistance(adjustedDist);
                    adjVert->setPredecessor(currentVert);
                    PQ.push(adjVert);
                }
            }
        }
        if (!weighted)
        {
            double total = 0;
            Vertex *current = dest;
            std::list<Vertex *> path;
            while (current != 0)
            {
                path.push_front(current);
                current = static_cast<InnerVertex *>(current)->getPredecessor();
            }
            while (true)
            {
                auto v = path.front();
                if (v == dest)
                {
                    break;
                }
                path.pop_front();
                total += getWeight(getEdge(v, path.front()));
            }
            return total;
        }
        return destination->getDistance();
    }

    void printShortestPath(Vertex *src, Vertex *dest)
    {
        Vertex *current = dest;
        std::list<Vertex *> path;
        while (current != 0)
        {
            path.push_front(current);
            current = static_cast<InnerVertex *>(current)->getPredecessor();
        }
        while (true)
        {
            auto v = path.front();
            if (v == dest)
            {
                std::cout << v->getElement() << '\n';
                break;
            }
            std::cout << v->getElement() << " --- ";
            path.pop_front();
            std::cout << getEdge(v, path.front())->getElement() << " --> ";
        }
    }

    void print()
    {
        for (auto itr = vertices.begin(); itr != vertices.end(); itr++)
        {
            std::cout << "\nVertex " << (*itr)->getElement() << '\n';
            if (isDirected)
                std::cout << "[outgoing]";
            std::cout << " " << outDegree(*itr) << " adjacencies:\n";
            for (auto e : outgoingEdges(*itr))
            {
                std::cout << "(" << opposite(*itr, e)->getElement() << ", " << e->getElement() << ", "
                          << getWeight(e) << ")\n";
            }
            std::cout << '\n';
            if (isDirected)
            {
                std::cout << "[incoming]";
                std::cout << " " << inDegree(*itr) << " adjacencies:\n";
                for (auto e : incomingEdges(*itr))
                {
                    std::cout << "(" << opposite(*itr, e)->getElement() << ", " << e->getElement() << ", "
                              << getWeight(e) << ")\n";
                }
            }
        }
    }
};
