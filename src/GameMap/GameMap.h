#ifndef GAMEMAP_H_
#define GAMEMAP_H_
#include <iostream>
#include <string>   // strings
#include <vector>   // vectors
#include <utility>  // pairs
#include <climits>  // INT_MAX
#include <algorithm>
#include <stack>    // stacks
#include <sstream>
using namespace std;

// Global Variables
enum pathType {BOTRGHT, BOTLEFT, TOPRGHT, TOPLEFT, VERTHALL, HORIHALL, T_DOWN, T_UP, T_2RGHT, T_2LEFT, INTRSECTNS};
enum objectType {PACDOT, EMPTY, PACPOWER};
const int X_MAX = 32;
const int Y_MAX = 34;
const int TOTALSIZE = X_MAX * Y_MAX;

struct Vertex {
public:
	pair<int, int> position;            // x & y coordinates
	vector<pair<int, int> > neighbors;  // list of the indexes of connected verticies and the cost to travel that edge
	int distance;                       // Keeps track of how far current Vertex is from starting vertex for pathfinding
	Vertex* prevV;                      // Points to previous Vertex. Used in Dijkstras.
	pathType patType;
	objectType itemType;

	Vertex(int x, int y) {
		position.first = x;
		position.second = y;
		vector<pair<int, int> > neighbors;
		distance = INT_MAX;               // Keeps track of how far current Vertex is from starting vertex for pathfinding
		prevV = 0;                        // FELT CUTE, MIGHT DELETE LATER FOR PATHFINDING
	}

	~Vertex() {}
};

class Queue {
public:
	Queue();
	void enqueue(Vertex*);
	void dequeue();
	void erase(unsigned);
	Vertex* end();
	Vertex* at(unsigned);
	unsigned size();
	bool empty();

private:
	vector<Vertex*> queue;
};

class GameMap {
public:
	GameMap();
	~GameMap();

	//solve is used to check input and find the solution if one exists
	//returns -1 invalid inputs. solution set to empty string.
	//returns 0 if inputs are valid but a solution does not exist. solution set to empty string.
	//returns 1 if solution is found and stores solution steps in solution string.
	int pathFind(string &solution, int, int, int, int);     // Finds shortest path to specified coordinates
	void printMap();										                    // Testing purposes. NOT A GUI
	vector<Vertex>* getGraph();

private:
	vector<Vertex> graph;               // Fixed map size

	// Prototype Functions
	void buildMapBody(int, int, int);
	void buildMapEdges(int, int, int);
	void buildMapCorners(int, int, int);
	void buildGameWalls(int);
	void dijkstra(Vertex*, unsigned);
	void InitializeSingleSource(Vertex* start);
	void relax(Vertex*, Vertex*, int);
	void solutionF(stringstream&, Vertex*);

	// Helper Functions
	void buildWall(int, int);                  // Helps all buildGameWall(int, vertexType) helpers
	void buildGameWall(int, pathType);       // Helps buildGameWalls(int)
	void setObjectType(int, objectType);       // Helps buildGameWalls(int)
	// anything else you need 
};

#endif // GAMEMAP_H_