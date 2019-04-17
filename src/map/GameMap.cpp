#include "GameMap.h"

// constructs the vector to build the verticies
GameMap::GameMap() {
	// Starting point of GameMap (upper right corner)
	//graph.push_back(Vertex(0, 0));
	// FELT CUTE, MIGHT DELETE LATER
	int edgeIndex = 0;
	int currX = 0;
	int currY = -1;
	//int upCounter = -1;

	// Loop to build entire game map
	// as well as connecting all necessary verticies together
	// static limits of map are 32 nodes across and 34 nodes up
	for(unsigned int i = 0; i < graph.size(); ++i) {
		// Increasing Y-axis every 32 Vertexes
		if(i % 32 == 0) {
			currY++;
			currX = 0;
		}

		// Creates new "sqaure" that game objects can "travel" on
		graph.push_back(Vertex(currX, currY));

		// BUGS MIGHT EXIST HERE WITH MAP LIMITS AND SETTING COST TO INFI
		// If current Vertex is at the edge of map, then set cost to INFI
		// if(currX == 0 || currY == 0 || currX == 31 || currY == 33) {
		// 	graph.at(i).neighbors.second = INT_MAX;
		// }

		// If current Vertex is the edge of map
		if(graph.at(i).neighbors.second == INT_MAX) {
			// If current Vertex is a corner, then limit edges to 2
			if(i == 0 || i == 31 || i == 1056 || i == 1087) {
				setCornerNeighbors()
			}
		}




	}
}

GameMap::~GameMap() {
	while(!graph.empty()) {
		graph.pop_back();
	}
}