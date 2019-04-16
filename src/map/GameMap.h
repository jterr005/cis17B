#ifndef GAMEMAP_H_
#define GAMEMAP_H_
#include <iostream>
#include <string>		// strings
#include <vector>		// vectors
#include <utility>	// pairs
#include <climits>	// INT_MAX
#include <algorithm>
#include <stack>		// stacks
using namespace std;

struct Vertex {
public:
	pair<int, int> position;      // x & y coordinates
	vector<int> neighbors;        // list of the indexes of connected vertexes
	int distance;                 // FELT CUTE, MIGHT DELETE LATER
	Vertex* prevV;                // FELT CUTE, MIGHT DELETE LATER

	Vertex(int x, int y) {
		position.first = x;
		position.second = y;
		vector<int> neighbors;
		distance = INT_MAX;         // FELT CUTE, MIGHT DELETE LATER
		prevV = 0;                  // FELT CUTE, MIGHT DELETE LATER
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
	int pathFind(string &solution); // Finds shortest path to specified coordinates

private:
	int goal;
	vector<Vertex> graph;
	// anything else you need
};

#endif // GAMEMAP_H_