#include <iostream>
#include <string>
#include "GameMap.h"
using namespace std;

int main() {
	string solution;
	GameMap testMap;
	if(testMap.pathFind(solution, 3, 31, 28, 3) != 1) {
		cout << "ERROR 3" << endl;
	}
	cout << solution << endl << endl;

	cout << "Testing getGraph()" << endl;
	vector<Vertex>* myGraph;
	myGraph = testMap.getGraph();

	cout << "this is the starting position: " << myGraph->at(99).position.first << ", " << myGraph->at(99).position.second << endl;

	/* Test Graph with Outputs */
	//testMap.printMap();

	return 0;
}