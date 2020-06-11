#pragma once
#include <vector>
#include <list>
#include <string>

// Created by T. Vo for CSCI 230
// Based on Java version of Goodrich book w/o template
// string for vertex and int for edge
//Modified by Michael Morikawa for Proj 4

class Vertex // behaves like interface in Java
{
public:
	virtual std::string getElement() = 0;
};

class Edge // behaves like interface in Java
{
public:
	virtual std::string getElement() = 0;
};

class Graph
{
public:
	/* Returns the number of vertices of the graph */
	virtual int numVertices() = 0;

	/* Returns the number of edges of the graph */
	virtual int numEdges() = 0;

	/* Returns the vertices of the graph as an iterable collection */
	virtual std::list<Vertex *> getVertices() = 0;

	/* Returns the edges of the graph as an iterable collection */
	virtual std::list<Edge *> getEdges() = 0;

	/*
	* Returns the number of edges leaving vertex v.
	* Note that for an undirected graph, this is the same result
	* returned by inDegree
	* throws IllegalArgumentException if v is not a valid vertex?
	*/
	virtual int outDegree(Vertex *v) = 0; // throws IllegalArgumentException;

	/**
	* Returns the number of edges for which vertex v is the destination.
	* Note that for an undirected graph, this is the same result
	* returned by outDegree
	* throws IllegalArgumentException if v is not a valid vertex
	*/
	virtual int inDegree(Vertex *v) = 0; // throws IllegalArgumentException;

	/*
	* Returns an iterable collection of edges for which vertex v is the origin.
	* Note that for an undirected graph, this is the same result
	* returned by incomingEdges.
	* throws IllegalArgumentException if v is not a valid vertex
	*/
	virtual std::vector<Edge *> outgoingEdges(Vertex *v) = 0; // throws IllegalArgumentException;

	/*
	* Returns an iterable collection of edges for which vertex v is the destination.
	* Note that for an undirected graph, this is the same result
	* returned by outgoingEdges.
	* throws IllegalArgumentException if v is not a valid vertex
	*/
	virtual std::vector<Edge *> incomingEdges(Vertex *v) = 0; // throws IllegalArgumentException;

	/** Returns the edge from u to v, or null if they are not adjacent. */
	virtual Edge *getEdge(Vertex *u, Vertex *v) = 0; // throws IllegalArgumentException;

	/*
	* Returns the vertices of edge e as an array of length two.
	* If the graph is directed, the first vertex is the origin, and
	* the second is the destination.  If the graph is undirected, the
	* order is arbitrary.
	*/
	virtual std::vector<Vertex *> endVertices(Edge *e) = 0; // throws IllegalArgumentException;

	/* Returns the vertex that is opposite vertex v on edge e. */
	virtual Vertex *opposite(Vertex *v, Edge *e) = 0; // throws IllegalArgumentException;

	/* Inserts and returns a new vertex with the given element. */
	virtual Vertex *insertVertex(std::string element) = 0;

	/*
	* Inserts and returns a new edge between vertices u and v, storing given element.
	*
	* throws IllegalArgumentException if u or v are invalid vertices, or if an edge already exists between u and v.
	*/
	virtual Edge *insertEdge(Vertex *u, Vertex *v, std::string element, double weight) = 0; // throws IllegalArgumentException;

	/* Removes a vertex and all its incident edges from the graph. */
	virtual void removeVertex(Vertex *v) = 0; // throws IllegalArgumentException;

	/* Removes an edge from the graph. */
	virtual void removeEdge(Edge *e) = 0; // throws IllegalArgumentException;

	virtual void print() = 0;
};
