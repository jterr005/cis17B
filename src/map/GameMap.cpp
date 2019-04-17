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
	for(unsigned i = 0; i < graph.size(); ++i, ++currX) {
		// Increment Y-axis & reset X-axis to 0 every 32 vertexes 
		if(i % 32 == 0) {
			currY++;
			currX = 0;
		}

		// Creates new "sqaure" that game objects can "travel" on
		graph.push_back(Vertex(currX, currY));

		/* Initializes the corner's neighbors. Static since only 4 corners.
		   Each corner vertex must have 2 neighbors */
		if(i == 0) {
			// Bottom Left Corner
			graph.at(i).neighbors.push_back(make_pair(i + 1, 1));
			graph.at(i).neighbors.push_back(make_pair(i + X_MAX, 1));
		}
		else if(i == 31) {
			// Bottom Right Corner
			graph.at(i).neighbors.push_back(make_pair(i - 1, 1));
			graph.at(i).neighbors.push_back(make_pair(i + X_MAX, 1));
		}
		else if(i == 1056) {
			// Top Left Corner
			graph.at(i).neighbors.push_back(make_pair(i - X_MAX, 1));
			graph.at(i).neighbors.push_back(make_pair(i + 1, 1));
		}
		else if(i == 1087) {
			// Top Right Corner
			graph.at(i).neighbors.push_back(make_pair(i - X_MAX, 1));
			grpah.at(i).neighbors.push_back(make_pair(i - 1, 1));
		}

		/* Initializes the side's neighbors.
		   Each side vertex must have 3 neighbors */
		if(currY == 0 && (i != 0 && i != 31)) {
			// Bottom
			graph.at(i).neighbors.push_back(make_pair(i - 1, 1));
			graph.at(i).neighbors.push_back(make_pair(i + 1, 1));
			graph.at(i).neighbors.push_back(make_pair(i + X_MAX, 1));
		}
		else if(currX == 0 && (i != 0 && i != 1056)) {
			// Left
			graph.at(i).neighbors.push_back(make_pair(i - X_MAX, 1));
			graph.at(i).neighbors.push_back(make_pair(i + X_MAX, 1));
			graph.at(i).neighbors.push_back(make_pair(i + 1, 1));
		}
		else if(currX == 31 && (i != 31 && i != 1087)) {
			// Right 
			graph.at(i).neighbors.push_back(make_pair(i - X_MAX, 1));
			graph.at(i).neighbors.push_back(make_pair(i + X_MAX, 1));
			graph.at(i).neighbors.push_back(make_pair(i - 1, 1));
		}
		else if(currY == 33 && (i != 1056 && i != 1087)) {
			// Top
			graph.at(i).neighbors.push_back(make_pair(i - 1, 1));
			graph.at(i).neighbors.push_back(make_pair(i + 1, 1));
			graph.at(i).neighbors.push_back(make_pair(i - X_MAX, 1));
		}



	}
}

GameMap::~GameMap() {
	while(!graph.empty()) {
		graph.pop_back();
	}
}