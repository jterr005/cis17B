#include "GameMap.h"

// constructs the vector to build the verticies
GameMap::GameMap() {
	// FELT CUTE, MIGHT DELETE LATER
	int edgeIndex = 0;
	int currX = 0;
	int currY = -1;
	graph.reserve(TOTALSIZE);
	//int upCounter = -1;

	// Loop to build entire game map
	// as well as connecting all necessary verticies together
	// static limits of map are 32 nodes across and 34 nodes up
	for(unsigned i = 0; i < TOTALSIZE; ++i, ++currX) {
		// Increment Y-axis & reset X-axis to 0 every 32 vertexes 
		if(i % X_MAX == 0) {
			currY++;
			currX = 0;
		}

		// Creates new "sqaure" that game objects can "travel" on
		graph.push_back(Vertex(currX, currY));

		/* Initializes the corner's neighbors. Static since only 4 corners.
		   Each corner vertex must have 2 neighbors */
		if(i == 0) {
			// Bottom Left Corner
			graph.at(i).neighbors.push_back(make_pair(i + 1, INT_MAX));
			graph.at(i).neighbors.push_back(make_pair(i + X_MAX, INT_MAX));
		}
		else if(i == 31) {
			// Bottom Right Corner
			graph.at(i).neighbors.push_back(make_pair(i - 1, INT_MAX));
			graph.at(i).neighbors.push_back(make_pair(i + X_MAX, INT_MAX));
		}
		else if(i == 1056) {
			// Top Left Corner
			graph.at(i).neighbors.push_back(make_pair(i - X_MAX, INT_MAX));
			graph.at(i).neighbors.push_back(make_pair(i + 1, INT_MAX));
		}
		else if(i == 1087) {
			// Top Right Corner
			graph.at(i).neighbors.push_back(make_pair(i - X_MAX, INT_MAX));
			graph.at(i).neighbors.push_back(make_pair(i - 1, INT_MAX));
		}

		/* Initializes the side's neighbors.
		   Each side vertex must have 3 neighbors */
		if(currY == 0 && (i != 0 && i != 31)) {
			// Bottom Side
			graph.at(i).neighbors.push_back(make_pair(i - 1, INT_MAX));
			graph.at(i).neighbors.push_back(make_pair(i + 1, INT_MAX));
			graph.at(i).neighbors.push_back(make_pair(i + X_MAX, INT_MAX));
		}
		else if(currX == 0 && (i != 0 && i != 1056)) {
			// Left Side
			graph.at(i).neighbors.push_back(make_pair(i - X_MAX, INT_MAX));
			graph.at(i).neighbors.push_back(make_pair(i + X_MAX, INT_MAX));
			graph.at(i).neighbors.push_back(make_pair(i + 1, INT_MAX));
		}
		else if(currX == (X_MAX - 1) && (i != 31 && i != 1087)) {
			// Right Side
			graph.at(i).neighbors.push_back(make_pair(i - X_MAX, INT_MAX));
			graph.at(i).neighbors.push_back(make_pair(i + X_MAX, INT_MAX));
			graph.at(i).neighbors.push_back(make_pair(i - 1, INT_MAX));
		}
		else if(currY == (Y_MAX - 1) && (i != 1056 && i != 1087)) {
			// Top Side
			graph.at(i).neighbors.push_back(make_pair(i - 1, INT_MAX));
			graph.at(i).neighbors.push_back(make_pair(i + 1, INT_MAX));
			graph.at(i).neighbors.push_back(make_pair(i - X_MAX, INT_MAX));
		}

		/* Initializes the body's neighbors. 
		   Each body vertex must have 4 neighbors */
		if(currY != 0 && currY != (Y_MAX - 1) && currX != 0 && currX != (X_MAX - 1)) {
			// **Special Case** Bottom Body Vertexes
			if(currY == 1) {
				if(i == X_MAX + 1) {
					// Bottom Left Corner of Body Set
					graph.at(i).neighbors.push_back(make_pair(i - 1, INT_MAX)); 
					graph.at(i).neighbors.push_back(make_pair(i + 1, 1)); 
					graph.at(i).neighbors.push_back(make_pair(i - X_MAX, INT_MAX));
					graph.at(i).neighbors.push_back(make_pair(i + X_MAX, 1));
				}

				else if(i == X_MAX*2 - 2) {
					// Bottom Right Corner of Body Set
					graph.at(i).neighbors.push_back(make_pair(i - 1, 1));
					graph.at(i).neighbors.push_back(make_pair(i + 1, INT_MAX));
					graph.at(i).neighbors.push_back(make_pair(i - X_MAX, INT_MAX));
					graph.at(i).neighbors.push_back(make_pair(i + X_MAX, 1));
				}

				else {
					// Rest of Bottom Edge of Body Set
					graph.at(i).neighbors.push_back(make_pair(i - 1, 1));
					graph.at(i).neighbors.push_back(make_pair(i + 1, 1));
					graph.at(i).neighbors.push_back(make_pair(i - X_MAX, INT_MAX));
					graph.at(i).neighbors.push_back(make_pair(i + X_MAX, 1));
				}
			}

			// **Special Case** Top Body Vertexes
			else if(currY == 32) {
				if(i == X_MAX*currY + 1) {
					// Top Left Corner of Body Set
					graph.at(i).neighbors.push_back(make_pair(i - 1, INT_MAX));
					graph.at(i).neighbors.push_back(make_pair(i + 1, 1));
					graph.at(i).neighbors.push_back(make_pair(i - X_MAX, 1));
					graph.at(i).neighbors.push_back(make_pair(i + X_MAX, INT_MAX));
				}

				else if(i == X_MAX* (Y_MAX - 1) - 2) {
					// Top Right Corner of Body Set
					graph.at(i).neighbors.push_back(make_pair(i - 1, 1));
					graph.at(i).neighbors.push_back(make_pair(i + 1, INT_MAX));
					graph.at(i).neighbors.push_back(make_pair(i - X_MAX, 1));
					graph.at(i).neighbors.push_back(make_pair(i + X_MAX, INT_MAX));
				}

				else {
					// Rest of Top Edge of Body Set
					graph.at(i).neighbors.push_back(make_pair(i - 1, 1));
					graph.at(i).neighbors.push_back(make_pair(i + 1, 1));
					graph.at(i).neighbors.push_back(make_pair(i - X_MAX, 1));
					graph.at(i).neighbors.push_back(make_pair(i + X_MAX, INT_MAX));

				}
			}

			// **Special Case** Left Body Vertexes
			else if(currX == 1) {
				if(!(i == X_MAX + 1) && !(i == X_MAX*2 - 2)) {
					graph.at(i).neighbors.push_back(make_pair(i - 1, INT_MAX));
					graph.at(i).neighbors.push_back(make_pair(i + 1, 1));
					graph.at(i).neighbors.push_back(make_pair(i - X_MAX, 1));
					graph.at(i).neighbors.push_back(make_pair(i + X_MAX, 1));
				}
			}

			// **Special Case** Right Body Vertexes
			else if(currX == X_MAX-2) {
				if(!(i == X_MAX*currY + 1) && !(i == X_MAX* (Y_MAX - 1) - 2)) {
					graph.at(i).neighbors.push_back(make_pair(i - 1, 1));
					graph.at(i).neighbors.push_back(make_pair(i + 1, INT_MAX));
					graph.at(i).neighbors.push_back(make_pair(i - X_MAX, 1));
					graph.at(i).neighbors.push_back(make_pair(i + X_MAX, 1));
				}
			}

			else {
				// Normal Body Vertexes
				graph.at(i).neighbors.push_back(make_pair(i - 1, 1));
				graph.at(i).neighbors.push_back(make_pair(i + 1, 1));
				graph.at(i).neighbors.push_back(make_pair(i - X_MAX, 1));
				graph.at(i).neighbors.push_back(make_pair(i + X_MAX, 1));
			}
		}
	}

	// Start spawning

	// Test Graph with Outputs
	for(unsigned i = 0; i < graph.size(); ++i) {
		if(i % 32 == 0) {
			cout << endl;
		}
		cout << i << " ";
	}

	cout << endl << endl;

	// Output neighbors
	for(unsigned i = 0; i < graph.size(); ++i) {
		cout << "| " << i << " | - | " << graph.at(i).position.first << ", " << graph.at(i).position.second << " | -> ";
		for(unsigned j = 0; j < graph.at(i).neighbors.size(); ++j) {
			cout << "| " << graph.at(i).neighbors.at(j).first << ", ";
			if(graph.at(i).neighbors.at(j).second == INT_MAX) {
				cout << "INF" << "| -> ";
			}
			else {
				cout << graph.at(i).neighbors.at(j).second << " | -> ";
			}
		}
		cout << endl;
	}
}

GameMap::~GameMap() {
	while(!graph.empty()) {
		graph.pop_back();
	}
}