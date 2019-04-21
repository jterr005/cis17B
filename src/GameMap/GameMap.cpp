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
		buildMapCorners(currX, currY, i);

		/* Initializes the side's neighbors.
		   Each side vertex must have 3 neighbors */
		buildMapEdges(currX, currY, i);

		/* Initializes the body's neighbors. 
		   Each body vertex must have 4 neighbors */
		if(currY != 0 && currY != (Y_MAX - 1) && currX != 0 && currX != (X_MAX - 1)) {
			buildMapBody(currX, currY, i);
		}
	}

	/* Generates game walls */
	for(unsigned i = X_MAX*3; i < TOTALSIZE; ++i) {
		buildGameWalls(i);
	}


}

/* Deconstructor */
GameMap::~GameMap() {
	while(!graph.empty()) {
		graph.pop_back();
	}
}

// Function prints all vertexes, their neighbors and their costs to travel
void GameMap::printMap() {
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
			if(j == 0) {
				cout << "| " << "LEFT" << ", ";
			}
			if(j == 1) {
				cout << "| " << "RIGHT" << ", ";
			}
			if(j == 2) {
				cout << "| " << "DOWN" << ", ";
			}
			if(j == 3) {
				cout << "| " << "UP" << ", ";
			}
			//cout << "| " << graph.at(i).neighbors.at(j).first << ", ";
			if(graph.at(i).neighbors.at(j).second == INT_MAX) {
				cout << "INF" << "| -> ";
			}
			else {
				cout << graph.at(i).neighbors.at(j).second << " | -> ";
			}
		}
		cout << endl;
	}
	cout << "GameMap Test Complete" << endl << endl;
	return;
}

/* Initializes the body's neighbors. 
   Each body vertex must have 4 neighbors */
void GameMap::buildMapBody(int currX, int currY, int i) {
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

/* Initializes the side's neighbors.
		Each side vertex must have 3 neighbors */
void GameMap::buildMapEdges(int currX, int currY, int i) {
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
	return;
}

/* Initializes the corner's neighbors. Static since only 4 corners.
   Each corner vertex must have 2 neighbors */
void GameMap::buildMapCorners(int currX, int currY, int i) {
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
}

/* Generates game walls */
void GameMap::buildGameWalls(int i) {
	// Assign current x,y to respective variables
	int currX = graph.at(i).position.first;
	int currY = graph.at(i).position.second;

	// Left side of playable paths
	if(currX == 3) {
		// Generates entire column's walls
		if(currY == 3 || currY == 9 || currY == 24) {
			buildGameWall(i, BOTLEFT);
			setObjectType(i, PACDOT);
		}

		else if(currY == 6 || currY == 12 || currY == 31) {
			buildGameWall(i, TOPLEFT);
			setObjectType(i, PACDOT);
		}

		else if(currY == 4 || currY == 5 || currY == 10 || currY == 11 || currY == 25 || currY == 26 || currY == 28 || currY == 29 || currY == 30) {
			buildGameWall(i, VERTHALL);
			setObjectType(i, PACDOT);
		}

		else if(currY == 27) {
			buildGameWall(i, T_2RGHT);
			setObjectType(i, PACDOT);
			return;
		}

		else if(currY == 18) {
			buildGameWall(i, HORIHALL);
			setObjectType(i, PACDOT);
		}

		// sets powerup vertexes
		if(currY == 9 || currY == 29) {
			setObjectType(i, PACPOWER);
		}
		// Sets Empty vertexes
		else if(currY == 18) {
			setObjectType(i, EMPTY);
		}

		return;
	}

	// Right side of playable paths
	if(currX == 28) {
		if(currY == 3 || currY == 9 || currY == 24) {
			buildGameWall(i, BOTRGHT);
			setObjectType(i, PACDOT);
		}
		else if(currY == 6 || currY == 12 || currY == 31) {
			buildGameWall(i, TOPRGHT);
			setObjectType(i, PACDOT);
		}
		else if(currY == 4 || currY == 5 || currY == 10 || currY == 11 || currY == 25 || currY == 26 || currY == 28 || currY == 29 || currY == 30) {
			buildGameWall(i, VERTHALL);
			setObjectType(i, PACDOT);
		}
		else if(currY == 27) {
			buildGameWall(i, T_2LEFT);
			setObjectType(i, PACDOT);
		}
		else if(currY == 18) {
			buildGameWall(i, HORIHALL);
			setObjectType(i, PACDOT);
		}

		// set's PowerUp Vertexes
		if(currY == 9 || currY == 29) {
			setObjectType(i, PACPOWER);
		}
		// Sets Empty vertexes
		else if(currY == 18) {
			setObjectType(i, EMPTY);
		}

		return;
	}

	// When x = 4 or 27
	if(currX == 4 || currX == 27) {
		if(currY == 3 || currY == 6 || currY == 9 || currY == 12 || currY == 18 || currY == 24 || currY == 27 || currY == 31) {
			buildGameWall(i, HORIHALL);
			setObjectType(i, PACDOT);
		}

		if(currY == 18) {
			setObjectType(i, EMPTY);
		}

		return;
	}

	// When x = 5 or 26
	if(currX == 5 || currX == 26) {
		if(currY == 3 || currY == 12 || currY == 18 || currY == 24 || currY == 27 || currY == 31) {
			buildGameWall(i, HORIHALL);
			setObjectType(i, PACDOT);
		}

		else if(currY == 6) {
			buildGameWall(i, T_UP);
			setObjectType(i, PACDOT);
		}

		else if(currY == 7 || currY == 8) {
			buildGameWall(i, VERTHALL);
			setObjectType(i, PACDOT);
		}

		else if(currY == 9) {
			if(currX == 5) {
				buildGameWall(i, TOPRGHT);
				setObjectType(i, PACDOT);
			}
			else if(currY == 26) {
				buildGameWall(i, TOPLEFT);
				setObjectType(i, PACDOT);
			}
		}

		if(currY == 18) {
			setObjectType(i, EMPTY);
		}

		return;
	}

	// When x = 6 or 25
	if(currX == 6 || currX == 25) {
		if(currY == 3 || currY == 6 || currY == 12 || currY == 18 || currY == 24 || currY == 27 || currY == 31) {
			buildGameWall(i, HORIHALL);
			setObjectType(i, PACDOT);
		}

		if(currY == 18) {
			setObjectType(i, EMPTY);
		}

		return;
	}

	// When x = 7 or 24
	if(currX == 7 || currX == 24) {
		if(currY == 3 || currY == 6 || currY == 12 || currY == 18 || currY == 24 || currY == 27 || currY == 31) {
			buildGameWall(i, HORIHALL);
			setObjectType(i, PACDOT);
		}

		if(currY == 18) {
			setObjectType(i, EMPTY);
		}

		return;
	}

	// When x = 8 or 23
	if(currX == 8 || currX == 23) {
		if(currY == 3) {
			buildGameWall(i, HORIHALL);
			setObjectType(i, PACDOT);
		}
		if(currY == 6) {
			if(currX == 8) {
				buildGameWall(i, BOTRGHT);
				setObjectType(i, PACDOT);
			}
			else if(currX == 23) {
				buildGameWall(i, BOTLEFT);
				setObjectType(i, PACDOT);
			}
		}
		if(currY == 7 || currY == 8 || currY == 10 || currY == 11 || currY == 13 || currY == 14 || currY == 15 || currY == 16 || currY == 17 || currY == 19 || currY == 20 || currY == 21 || currY == 22 || currY == 23 || currY == 25 || currY == 26 || currY == 28 || currY == 29 || currY == 30) {
			buildGameWall(i, VERTHALL);
			setObjectType(i, PACDOT);
		}
		if(currY == 12 || currY == 18 || currY == 27) {
			buildGameWall(i, INTRSECTNS);
			setObjectType(i, PACDOT);
		}
		if(currY == 9) {
			if(currX == 8) {
				buildGameWall(i, T_2RGHT);
				setObjectType(i, PACDOT);
			}

			if(currX == 23) {
				buildGameWall(i, T_2LEFT);
				setObjectType(i, PACDOT);
			}
		}
		if(currY == 24) {
			if(currX == 8) {
				buildGameWall(i, T_2LEFT);
				setObjectType(i, PACDOT);
			}
			if(currX == 23) {
				buildGameWall(i, T_2RGHT);
				setObjectType(i, PACDOT);
			}
		}
		if(currY == 31) {
			buildGameWall(i, T_DOWN);
			setObjectType(i, PACDOT);
		}

		return;
	}

	// When x = 9 or 22
	if(currX == 9 || currX == 22) {
		if(currY == 3 || currY == 9 || currY == 12 || currY == 18 || currY == 27 || currY == 31) {
			buildGameWall(i, HORIHALL);
			setObjectType(i, PACDOT);
		}

		if(currY == 18) {
			setObjectType(i, EMPTY);
		}

		return;
	}

	// When x = 10 or 21
	if(currX == 10 || currX == 21) {
		if(currY == 3 || currY == 9 || currY == 12 || currY == 18 || currY == 27 || currY == 31) {
			buildGameWall(i, HORIHALL);
			setObjectType(i, PACDOT);
		}

		if(currY == 18) {
			setObjectType(i, EMPTY);
		}

		return;
	}

	// When x = 11 or 20
	if(currX == 11 || currX == 20) {
		if(currY == 3 || currY == 31) {
			buildGameWall(i, HORIHALL);
			setObjectType(i, PACDOT);
		}
		if(currY == 6 || currY == 24) {
			if(currX == 11) {
				buildGameWall(i, BOTLEFT);
				setObjectType(i, PACDOT);
			}
			if(currX == 20) {
				buildGameWall(i, BOTRGHT);
				setObjectType(i, PACDOT);
			}
		}
		if(currY == 7 || currY == 8 || currY == 13 || currY == 14 || currY == 16 || currY == 17 || currY == 19 || currY == 20 || currY == 25 || currY == 26) {
			buildGameWall(i, VERTHALL);
			setObjectType(i, PACDOT);
		}
		if(currY == 9 || currY == 27) {
			buildGameWall(i, T_DOWN);
			setObjectType(i, PACDOT);
		}
		if(currY == 12) {
			buildGameWall(i, T_UP);
			setObjectType(i, PACDOT);
		}
		if(currY == 15) {
			if(currX == 11) {
				buildGameWall(i, T_2RGHT);
				setObjectType(i, PACDOT);
			}
			if(currX == 20) {
				buildGameWall(i, T_2LEFT);
				setObjectType(i, PACDOT);
			}
		}
		if(currY == 18) {
			if(currX == 11) {
				buildGameWall(i, T_2LEFT);
				setObjectType(i, PACDOT);
			}
			if(currX == 20) {
				buildGameWall(i, T_2RGHT);
				setObjectType(i, PACDOT);
			}
		}
		if(currY == 21) {
			if(currX == 11) {
				buildGameWall(i, TOPLEFT);
				setObjectType(i, PACDOT);
			}
			if(currX == 20) {
				buildGameWall(i, TOPRGHT);
				setObjectType(i, PACDOT);
			}
		}

		if(currY > 12 || currY < 22) {
			setObjectType(i, EMPTY);
		}

		return;
	}

	// When x = 12 or 19
	if(currX == 12 || currX == 19) {
		if(currY == 3 || currY == 6 || currY == 9 || currY == 12 || currY == 15 || currY == 21 || currY == 24 || currY == 27 || currY == 31) {
			buildGameWall(i, HORIHALL);
			setObjectType(i, PACDOT);
		}

		if(currY == 15 || currY == 21) {
			setObjectType(i, EMPTY);
		}

		return;
	}

	// When x = 13 or 18
	if(currX == 13 || currX == 18) {
		if(currY == 3 || currY == 6 || currY == 9 || currY == 12 || currY == 15 || currY == 21 || currY == 24 || currY == 27 || currY == 31) {
			buildGameWall(i, HORIHALL);
			setObjectType(i, PACDOT);		
		}
		if(currY == 15 || currY == 21) {
			setObjectType(i, EMPTY);
		}

		return;
	}

	// When x = 14 or 17
	if(currX == 14 || currX == 17) {
		if(currY == 3 || currY == 9 || currY == 21 || currY == 27) {
			buildGameWall(i, T_UP);
			setObjectType(i, PACDOT);
		}

		if(currY == 4 || currY == 5 || currY == 10 || currY == 11 || currY == 22 || currY == 23 || currY == 28 || currY == 29 || currY == 30) {
			buildGameWall(i, VERTHALL);
			setObjectType(i, PACDOT);
		}

		if(currY == 15) {
			buildGameWall(i, HORIHALL);
			setObjectType(i, PACDOT);
		}

		if(currY == 6 || currY == 12 || currY == 24 || currY == 31) {
			if(currX == 14) {
				buildGameWall(i, TOPRGHT);
				setObjectType(i, PACDOT);
			}
			if(currX == 17) {
				buildGameWall(i, TOPLEFT);
				setObjectType(i, PACDOT);
			}
		}

		if(currY == 15 || currY == 21 || currY == 22 || currY == 23) {
			setObjectType(i, EMPTY);
		}

		return;
	}

	// When x = 15 or 16
	if(currX == 15 || currX == 16) {
		if(currY == 3 || currY == 9 || currY == 15 || currY == 21 || currY == 27) {
			buildGameWall(i, HORIHALL);
			setObjectType(i, PACDOT);
		}

		if(currY == 15 || currY == 21) {
			setObjectType(i, EMPTY);
		}

		return;
	}


	return;
}

/* Sets boundaries for corners in playable zone */
void GameMap::buildGameWall(int i, pathType type) {
	switch(type) {
		case BOTRGHT:
			buildWall(i, 1);
			buildWall(i, 2);
			graph.at(i).patType = BOTRGHT;
			break;

		case BOTLEFT:
			buildWall(i, 0);
			buildWall(i, 2);
			graph.at(i).patType = BOTLEFT;
			break;

		case TOPRGHT:
			buildWall(i, 1);
			buildWall(i, 3);
			graph.at(i).patType = TOPRGHT;
			break;

		case TOPLEFT:
			buildWall(i, 0);
			buildWall(i, 3);
			graph.at(i).patType = TOPLEFT;
			break;

		case VERTHALL:
			buildWall(i, 0);
			buildWall(i, 1);
			graph.at(i).patType = VERTHALL;
			break;

		case HORIHALL:
			buildWall(i, 2);
			buildWall(i, 3);
			graph.at(i).patType = HORIHALL;
			break;

		case T_DOWN:
			buildWall(i, 3);
			graph.at(i).patType = T_DOWN;
			break;

		case T_UP:
			buildWall(i, 2);
			graph.at(i).patType = T_UP;
			break;

		case T_2RGHT:
			buildWall(i, 0);
			graph.at(i).patType = T_2RGHT;
			break;

		case T_2LEFT:
			buildWall(i, 1);
			graph.at(i).patType = T_2LEFT;
			break;

		case INTRSECTNS:
			graph.at(i).patType = INTRSECTNS;
			break;

		default:
			cout << "ERROR: UNKNOWN PATH TYPE DETECTED AT i = " << i;
			break;

		// next case

	}
}

void GameMap::setObjectType(int currVertex, objectType oType) {
	graph.at(currVertex).itemType = oType;
	return;
}

void GameMap::buildWall(int currVertex, int currNeighbor) {
	graph.at(currVertex).neighbors.at(currNeighbor).second = INT_MAX;
	return;
}