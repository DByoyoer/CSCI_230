#include <map>
#include <iomanip>
#include <fstream>
#include "AdjacencyListGraph.hpp"

void loadVertices(std::string filepath, std::map<std::string, Vertex *> &vertexMap,
                  std::map<std::string, std::string> &nameMap, AdjacencyListGraph &G);

void loadEdges(std::string filepath, std::map<std::string, Edge *> &edgeMap,
               std::map<std::string, Vertex *> &vertexMap, AdjacencyListGraph &G);

void cheapestFlight(Vertex *src, Vertex *dest, AdjacencyListGraph &G, bool weighted = true);

void cheapestRoundTrip(Vertex *src, Vertex *dest, AdjacencyListGraph &G);

void updateFlights(AdjacencyListGraph &G);

void updateAirports(std::map<std::string, Vertex *> &vertexMap);

void printMenu();

int main()
{
    AdjacencyListGraph airportNetwork(true);
    std::map<std::string, Vertex *> vertexInfo;
    std::map<std::string, std::string> airportNames;
    std::map<std::string, Edge *> edgeInfo;
    loadVertices("docs/P4Airports.txt", vertexInfo, airportNames, airportNetwork);
    loadEdges("docs/P4Flights.txt", edgeInfo, vertexInfo, airportNetwork);
    int choice = 0;
    bool running = true;
    while (running)
    {
        printMenu();
        std::cin >> choice;
        std::cout << choice << '\n'; //for file redirection
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore();
            break;
        }
        switch (choice)
        {
        case 0:
        {
            airportNetwork.print();
        }
        break;
        case 1:
        {
            std::string code;
            std::cout << std::setprecision(2) << std::fixed;
            std::cout << "\nPlease enter an airport code: ";
            std::cin >> code;
            std::cout << code << '\n'; //file redirection
            if (vertexInfo.find(code) != vertexInfo.end())
            {
                Vertex *airport = vertexInfo[code];
                std::cout << airport->getElement() << ": " << airportNames[code]
                          << "\n"
                          << airportNetwork.outDegree(airport) << " Departing Flights: ";
                for (auto e : airportNetwork.outgoingEdges(airport))
                {
                    std::cout << "\nFlight ID: " << e->getElement()
                              << "\nFlight Destination: "
                              << airportNetwork.opposite(airport, e)->getElement()
                              << "\nFlight Cost: $" << airportNetwork.getWeight(e);
                }
                std::cout << "\n";
            }
            else
            {
                std::cout << "Could not find that airport\n";
            }
        }
        break;
        case 2:
        {
            std::string code1, code2;
            std::cout << "Please enter source airport then destination airport codes: ";
            std::cin >> code1 >> code2;
            std::cout << code1 << ' ' << code2 << '\n'; //file redirction
            if (vertexInfo.find(code1) != vertexInfo.end() && vertexInfo.find(code2) != vertexInfo.end())
            {
                Vertex *source = vertexInfo[code1];
                Vertex *dest = vertexInfo[code2];
                cheapestFlight(source, dest, airportNetwork);
            }
            else
            {
                std::cout << "Could not find inputted airports\n";
            }
        }
        break;
        case 3:
        {
            std::string code1, code2;
            std::cout << "Please enter source airport then destination airport codes: ";
            std::cin >> code1 >> code2;
            std::cout << code1 << ' ' << code2 << '\n'; //file redirction
            if (vertexInfo.find(code1) != vertexInfo.end() && vertexInfo.find(code2) != vertexInfo.end())
            {
                Vertex *source = vertexInfo[code1];
                Vertex *dest = vertexInfo[code2];
                cheapestRoundTrip(source, dest, airportNetwork);
            }
            else
            {
                std::cout << "Could not find inputted airports\n";
            }
        }
        break;
        case 4:
        {
            std::string code1, code2, flightCode;
            double cost;
            std::cout << "Please enter source airport then destination airport codes: ";
            std::cin >> code1 >> code2;
            std::cout << code1 << ' ' << code2 << '\n'; //file redirction
            std::cout << "\nPlease Enter Flight number: ";
            std::cin >> flightCode;
            std::cout << flightCode << '\n';
            std::cout << "Please enter the cost: ";
            std::cin >> cost;
            std::cout << cost << '\n';
            if (vertexInfo.find(code1) != vertexInfo.end() && vertexInfo.find(code2) != vertexInfo.end())
            {
                Vertex *source = vertexInfo[code1];
                Vertex *dest = vertexInfo[code2];
                if (edgeInfo.find(flightCode) == edgeInfo.end())
                {
                    Edge *e = airportNetwork.insertEdge(source, dest, flightCode, cost);
                    edgeInfo[flightCode] = e;
                    std::cout << "Successfully added flight\n";
                }
                else
                {
                    airportNetwork.setWeight(edgeInfo[flightCode], cost);
                    std::cout << "Successfully updated flight\n";
                }
            }
            else
            {
                std::cout << "Could not find inputted airports\n";
            }
        }
        break;
        case 5:
        {
            std::string code1, code2;

            std::cout << "Please enter source airport then destination airport codes: ";
            std::cin >> code1 >> code2;
            std::cout << code1 << ' ' << code2 << '\n'; //file redirction
            if (vertexInfo.find(code1) != vertexInfo.end() && vertexInfo.find(code2) != vertexInfo.end())
            {
                Vertex *source = vertexInfo[code1];
                Vertex *dest = vertexInfo[code2];
                Edge *e = airportNetwork.getEdge(source, dest);
                if (e != nullptr)
                {
                    edgeInfo.erase(e->getElement());
                    airportNetwork.removeEdge(e);
                    std::cout << "Successfully deleted flight\n";
                }
                else
                {
                    std::cout << "Flight from " << code1 << " to " << code2 << " does not exist.\n";
                }
            }
            else
            {
                std::cout << "Could not find inputted airports\n";
            }
        }
        break;
        case 6:
        {
            std::string code1, code2;
            std::cout << "Please enter source airport then destination airport codes: ";
            std::cin >> code1 >> code2;
            std::cout << code1 << ' ' << code2 << '\n'; //file redirction
            if (vertexInfo.find(code1) != vertexInfo.end() && vertexInfo.find(code2) != vertexInfo.end())
            {
                Vertex *source = vertexInfo[code1];
                Vertex *dest = vertexInfo[code2];
                cheapestFlight(source, dest, airportNetwork, false); //false to use all weights = 1
            }
            else
            {
                std::cout << "Could not find inputted airports\n";
            }
        }
        break;
        case 9:
        {
            std::string code;
            std::cout << "Please enter airport code that you wish to delete: ";
            std::cin >> code;
            std::cout << code << '\n'; //file redirection
            if (vertexInfo.find(code) != vertexInfo.end())
            {
                airportNetwork.removeVertex(vertexInfo[code]);
                vertexInfo.erase(code);
                std::cout << "Successfully deleted airport\n";
            }
            else
            {
                std::cout << "Could not find inputted airport\n";
            }
        }
        break;

        default:
        {
            std::cout << "Option unavailable\n";
        }
        break;
        }
    }

    updateAirports(vertexInfo);
    updateFlights(airportNetwork);
}

void loadVertices(std::string filepath, std::map<std::string, Vertex *> &vertexMap,
                  std::map<std::string, std::string> &nameMap, AdjacencyListGraph &G)
{
    std::ifstream infile(filepath);
    std::string code, name;
    while (true)
    {
        if (infile.eof())
        {
            break;
        }
        infile >> code;
        std::getline(infile, name);
        vertexMap[code] = G.insertVertex(code);
        nameMap[code] = name;
    }
}

void loadEdges(std::string filepath, std::map<std::string, Edge *> &edgeMap,
               std::map<std::string, Vertex *> &vertexMap, AdjacencyListGraph &G)
{
    std::ifstream infile(filepath);
    std::string src, dest, code;
    Vertex *source, *destination;
    double cost;
    while (true)
    {
        if (infile.eof())
        {
            break;
        }
        infile >> src >> dest >> cost >> code;
        source = vertexMap[src];
        destination = vertexMap[dest];
        G.insertEdge(source, destination, code, cost);
    }
}
void cheapestFlight(Vertex *src, Vertex *dest, AdjacencyListGraph &G, bool weighted)
{
    double cost = G.shortestPath(src, dest, weighted);
    G.printShortestPath(src, dest);
    std::cout << std::setprecision(2) << std::fixed;
    std::cout << "Cost: $" << cost << '\n';
}
void cheapestRoundTrip(Vertex *src, Vertex *dest, AdjacencyListGraph &G)
{
    double cost = G.shortestPath(src, dest);
    G.printShortestPath(src, dest);
    std::cout << "Return: ";
    cost += G.shortestPath(dest, src);
    G.printShortestPath(dest, src);
    std::cout << std::setprecision(2) << std::fixed;
    std::cout << "Cost: $" << cost << '\n';
}

void printMenu()
{
    std::cout << "\n1. Display airport information\n"
              << "2. Cheapest flight from one airport to another\n"
              << "3. Cheapest roundrtip from one airport to another\n"
              << "4. Add a flight\n"
              << "5. Delete a flight\n"
              << "6. Fewest stops\n"
              << "7. All flights from one airport to another\n"
              << "8. Order to visit all airports from one airport\n"
              << "9. Delete airport\n"
              << "Q. Exit\n"
              << "\nPlease Select from Above Options: ";
}

void updateAirports(std::map<std::string, Vertex *> &vertexMap)
{
    std::ofstream outfile("docs/P4AirportsRev1.txt");
    for (auto p : vertexMap)
    {
        outfile << p.second->getElement() << "    " << p.first << '\n';
    }
}

void updateFlights(AdjacencyListGraph &G)
{
    std::ofstream outfile("docs/P4FlightsRev1.txt");
    std::vector<Vertex *> endpoints;
    outfile << std::setprecision(2) << std::fixed;
    for (auto e : G.getEdges())
    {
        endpoints = G.endVertices(e);
        outfile << endpoints[0]->getElement() << "   " << endpoints[1]->getElement()
                << std::setw(10) << std::right
                << G.getWeight(e) << "   " << e->getElement() << '\n';
    }
}