#include "GameMap.h"

// constructs the vector to build the verticies
GameMap::GameMap() {
	// Starting point of GameMap (upper right corner)
	//graph.push_back(Vertex(0, 0));
	// FELT CUTE, MIGHT DELETE LATER
	int edgeIndex = 0;
	int currX = 0;
	int currY = 0;
	int upCounter = -1;

	// Loop to build entire game map
	// as well as connecting all necessary verticies together
	for(unsigned i = 0; i < graph.size(); ++i) {
		if(i % 31 == 0) {
			upCounter++;
		} 


	}
}