#ifndef GAMEMAP_H_
#define GAMEMAP_H_
#include <iostream>
#include <string>   // strings
#include <vector>   // vectors
#include <utility>  // pairs
#include <climits>  // INT_MAX
#include <algorithm>
#include <stack>    // stacks
using namespace std;

// Global Variables
const int X_MAX = 32;
const int Y_MAX = 34;
const int TOTALSIZE = X_MAX * Y_MAX;

struct Vertex {
public:
	pair<int, int> position;            // x & y coordinates
	vector<pair<int, int> > neighbors;  // list of the indexes of connected verticies and the cost to travel that edge
	int distance;                       // FELT CUTE, MIGHT DELETE LATER FOR PATHFINDING 
	Vertex* prevV;                      // FELT CUTE, MIGHT DELETE LATER FOR PATHFINDING

	Vertex(int x, int y) {
		position.first = x;
		position.second = y;
		vector<pair<int, int> > neighbors;
		distance = INT_MAX;               // FELT CUTE, MIGHT DELETE LATER FOR PATHFINDING
		prevV = 0;                        // FELT CUTE, MIGHT DELETE LATER FOR PATHFINDING
	}

	~Vertex() {}
};

class GameMap {
public:
	GameMap();
	~GameMap();

	//solve is used to check input and find the solution if one exists
	//returns -1 invalid inputs. solution set to empty string.
	//returns 0 if inputs are valid but a solution does not exist. solution set to empty string.
	//returns 1 if solution is found and stores solution steps in solution string.
	int pathFind(string &solution);     // Finds shortest path to specified coordinates

	// Helper Functions

private:
	int goal;
	vector<Vertex> graph;               // Fixed map size
	// anything else you need 
};

#endif // GAMEMAP_H_