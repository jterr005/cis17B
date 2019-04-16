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
	pair<int, int> coordinates; 		// x & y coordinates
	vector<int> neighbors;					// list of the indexes of connected vertexes
	int distance;										// FELT CUTE, MIGHT DELETE LATER
	Vertex* prevV;									// FELT CUTE, MIGHT DELETE LATER

	Vertex(int x, int y) {
		coordinates.first = x;
		coordinates.second = y;
		vector<int> neighbors;
		distance = INT_MAX;						// FELT CUTE, MIGHT DELETE LATER
		prevV = 0;										// FELT CUTE, MIGHT DELETE LATER
	}

	~Vertex() {}
};

class GameMap {
public:
	GameMap();
	~GameMap();
}