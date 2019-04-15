#ifndef JUG_H__
#define JUG_H__
#include <iostream>
#include <string>  //strings
#include <vector>  //vectors
#include <utility> //pairs
#include <climits> //INT_MAX
#include <algorithm>
#include <stack>
#include<sstream>

using namespace std;

/*vertex class inspired from lab9 - graph structure inspired from lab9 
*/


struct Vertex {
    public:
        pair<int, int> jugState;               //first stores jugA current state & second stores jugB current state
        vector<pair<int, int> > neighbors; //first will store index of connected vertex & second will store cost of edge
        int distance;
        Vertex* prevV;
        
        Vertex(int jugA, int jugB) {
            jugState.first = jugA;
            jugState.second = jugB;
            vector<pair<int, int> > neighbors;
            distance = INT_MAX;
            prevV = 0;
        }
        
        ~Vertex() {}
        
        
        
};

class Queue {
    public:
        Queue();
        void enqueue(Vertex*);
        void dequeue();
        bool empty();
        Vertex* end();
        Vertex* at(unsigned); 
        unsigned size();
        void erase(unsigned);
    
    private:
        vector<Vertex*> queue;
};

class Jug {
    public:
        Jug(int,int,int,int,int,int,int,int,int);
        ~Jug();

        //solve is used to check input and find the solution if one exists
        //returns -1 invalid inputs. solution set to empty string.
        //returns 0 if inputs are valid but a solution does not exist. solution set to empty string.
        //returns 1 if solution is found and stores solution steps in solution string.
        int solve(string &solution);
    private:
        int maxJugA;
        int maxJugB;
        int goal;
        int costFillA;
        int costFillB;
        int costEmptyA;
        int costEmptyB;
        int costPourAinB;
        int costPourBinA;
        vector<Vertex> graph;
        void dijkstra(Vertex* start);
        void InitializeSingleSource(Vertex* start);
        void relax(Vertex*, Vertex*, int);
        void solutionF(stringstream &, Vertex*);
        //anything else you need
};

#endif //JUG_H__