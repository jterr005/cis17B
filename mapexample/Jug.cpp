#include "Jug.h"

Jug::Jug(int cA, int cB, int N, int cfA, int cfB, int ceA, int ceB, int cpAB, int cpBA) {
    maxJugA = cA;
    maxJugB = cB;
    goal = N;
    costFillA = cfA;
    costFillB = cfB;
    costEmptyA = ceA;
    costEmptyB = ceB;
    costPourAinB = cpAB;
    costPourBinA = cpBA;
    
    //constructs the vector to build the vertexes
    //that store the different states the jugs will be in (e.g. jugA == 3 && jugB == 5)
    
     if (maxJugA < 1 || maxJugB < 1 || goal < 1 || costFillA < 1 || costFillB < 1 || costEmptyA < 1 || costEmptyB < 1 || costPourAinB < 1 || costPourBinA < 1) {
        return;
    }
    
    graph.push_back(Vertex(0, 0));
    
    int edgeIndex = 0;
    
    for(unsigned i = 0; i < graph.size(); ++i) {
        
        //checks if jugA is full or not
        if(graph.at(i).jugState.first != maxJugA) {
            bool exist = true;
            //loops through Vertex vector
            for(unsigned scan = 0; scan < graph.size(); ++scan) {
                //checks if the state of jugA being full exists in Vertex vector & that jugB is unaltered
                if(graph.at(scan).jugState.first == maxJugA && graph.at(scan).jugState.second == graph.at(i).jugState.second) {
                    edgeIndex = scan;
                    exist = false;
                    break;
                }
            }
            
            //if the new state doesn't exist, Vertex is push_back
            if(exist) {
                graph.push_back(Vertex(maxJugA, graph.at(i).jugState.second));
                edgeIndex = graph.size() - 1;
            }
            
            graph.at(i).neighbors.push_back(make_pair(edgeIndex, costFillA));
        }
        
        //if jugA is already full, index to self in first and cost set to infinity in second
        else {
            graph.at(i).neighbors.push_back(make_pair(i, INT_MAX));
        }
        
        //checks if jugB is full or not
        if(graph.at(i).jugState.second !=maxJugB) {
            bool exist = true;
            //loops through Vertex vector
            for(unsigned scan = 0; scan < graph.size(); ++scan) {
                //checks if the state of jugB being full & jugA is unaltered exists in Vertex vector
                if(graph.at(scan).jugState.first == graph.at(i).jugState.first && graph.at(scan).jugState.second == maxJugB) {
                    edgeIndex = scan;
                    exist = false;
                    break;
                }
            }
            
            //if new state doesn't exist, Vertex is push_back
            if(exist) {
                graph.push_back(Vertex(graph.at(i).jugState.first, maxJugB));
                edgeIndex = graph.size() - 1;
            }
            
            graph.at(i).neighbors.push_back(make_pair(edgeIndex, costFillB));
        }
        
        //if jugB is already full, index to self in first and cost to infinity in second
        else {
            graph.at(i).neighbors.push_back(make_pair(i, INT_MAX));
        }
        
        //checks if jugA is empty
        if(graph.at(i).jugState.first != 0) {
            bool exist = true;
            
            //loops through Vertex vector
            for(unsigned scan = 0; scan < graph.size(); ++scan) {
                //checks if the state of jugA being empty & jugB is unaltered exists in Vertex vector
                if(graph.at(scan).jugState.first == 0 && graph.at(scan).jugState.second == graph.at(i).jugState.second) {
                    edgeIndex = scan;
                    exist = false;
                    break;
                }
            }
            
            //if new state doesn't exist, Vertex is push_back
            if(exist) {
                graph.push_back(Vertex(0, graph.at(i).jugState.second));
                edgeIndex = graph.size() - 1;
            }
            
            graph.at(i).neighbors.push_back(make_pair(edgeIndex, costEmptyA));
        }
        
        else {
            graph.at(i).neighbors.push_back(make_pair(i, INT_MAX));
        }
        
        //checks if jugB is empmty
        if(graph.at(i).jugState.second != 0) {
            bool exist = true;
            
            //loops through Vertex vector
            for(unsigned scan = 0; scan < graph.size(); ++scan) {
                //checks if the state of jugA is unaltered & jugB is empty exists in Vertex vector
                if(graph.at(scan).jugState.first == graph.at(i).jugState.first && graph.at(scan).jugState.second == 0) {
                    edgeIndex = scan;
                    exist = false;
                    break;
                }
            }
            
            //if new state doesn't exist, Vertex is push_back
            if(exist) {
                graph.push_back(Vertex(graph.at(i).jugState.first, 0));
                edgeIndex = graph.size() - 1;
            }
            
            graph.at(i).neighbors.push_back(make_pair(edgeIndex, costEmptyB));
        }
        
        else {
            graph.at(i).neighbors.push_back(make_pair(i, INT_MAX));
        }
        
        //checks if jugA is not empty & jugB is not full
        if(graph.at(i).jugState.first != 0 && graph.at(i).jugState.second != maxJugB) {
            bool exist = true;
            
            int volumeA = graph.at(i).jugState.first;
            int volumeB = graph.at(i).jugState.second;
            if(volumeA + volumeB <= maxJugB) {
                /*loops through vector of all Vertecies*/
                for(unsigned scan = 0; scan < graph.size(); ++scan) {
                    if(graph.at(scan).jugState.first == 0 && graph.at(scan).jugState.second == volumeA + volumeB) {
                        edgeIndex = scan;
                        exist = false;
                        break;
                    }
                }
                
                if(exist) {
                    graph.push_back(Vertex(0, volumeA + volumeB));
                    edgeIndex = graph.size() - 1;
                }
            }
            
            else {
                int newA = volumeA - (maxJugB - volumeB);
                int newB = maxJugB;
                for(unsigned scan = 0; scan < graph.size(); ++scan) {
                    if(graph.at(scan).jugState.first == newA && graph.at(scan).jugState.second == newB) {
                        edgeIndex = scan;
                        exist = false;
                        break;
                    }
                }
                
                if(exist) {
                    graph.push_back(Vertex(newA, newB));
                    edgeIndex = graph.size() - 1;
                }
            }
            
            graph.at(i).neighbors.push_back(make_pair(edgeIndex, costPourAinB));
        }
        
        else {
            graph.at(i).neighbors.push_back(make_pair(i, INT_MAX));
        }
        
        //checks if jugA is not full & jugB is not empty
        if(graph.at(i).jugState.first != maxJugA && graph.at(i).jugState.second != 0) {
            bool exist = true;
            
            int volumeA = graph.at(i).jugState.first;
            int volumeB = graph.at(i).jugState.second;
            if(volumeA + volumeB <= maxJugA) {
                /*loops through vector of all Vertecies*/
                for(unsigned scan = 0; scan < graph.size(); ++scan) {
                    if(graph.at(scan).jugState.first == volumeA + volumeB && graph.at(scan).jugState.second == 0) {
                        edgeIndex = scan;
                        exist = false;
                        break;
                    }
                }
                
                if(exist) {
                    graph.push_back(Vertex(volumeA + volumeB, 0));
                    edgeIndex = graph.size() - 1;
                }
            }
            
            else {
                int newA = maxJugA;
                int newB = volumeB - (maxJugA - volumeA);
                for(unsigned scan = 0; scan < graph.size(); ++scan) {
                    if(graph.at(scan).jugState.first == newA && graph.at(scan).jugState.second == newB) {
                        edgeIndex = scan;
                        exist = false;
                        break;
                    }
                }
                
                if(exist) {
                    graph.push_back(Vertex(newA, newB));
                    edgeIndex = graph.size() - 1;
                }
            }
            
            graph.at(i).neighbors.push_back(make_pair(edgeIndex, costPourBinA));
        }
        
        else {
            graph.at(i).neighbors.push_back(make_pair(i, INT_MAX));
        }
        
        
    }
    
    // for(unsigned i = 0; i < graph.size(); ++i) {
    //     cout <<"| " << i << " | - | " << graph.at(i).jugState.first << ", " << graph.at(i).jugState.second << " | -> ";
    //     for(unsigned j = 0; j < graph.at(i).neighbors.size(); ++j) {
    //         cout << "| " << graph.at(i).neighbors.at(j).first << ", "; 
    //         if(graph.at(i).neighbors.at(j).second == INT_MAX) {
    //             cout << "INF" << " | -> ";    
    //         }    
    //         else {
    //             cout <<graph.at(i).neighbors.at(j).second << " | -> ";
    //         }
    //     }
    //     cout << endl;
    // }
    
    
} 

Jug::~Jug() {
    while(!graph.empty()) {
        graph.pop_back();
    }
}

    //solve is used to check input and find the solution if one exists
    //returns -1 invalid inputs. solution set to empty string.
    //returns 0 if inputs are valid but a solution does not exist. solution set to empty string.
    //returns 1 if solution is found and stores solution steps in solution string.

int Jug::solve(string& solution) {
    //involid inputs because 0 < Ca ≤ Cb and N ≤ Cb ≤ 1000
    if (maxJugA > maxJugB || goal > maxJugB || maxJugB > 1000 || goal > 1000)  {
        solution = "";
        return -1;
    }
    
    //invalid inputs because Dijkstra's will bug with negative weights 
    if(maxJugA < 1 || maxJugB < 1 || goal < 1 || costFillA < 1 || costFillB < 1 || costEmptyA < 1 || costEmptyB < 1 || costPourAinB < 1 || costPourBinA < 1) {
        solution = "";
        return -1;
    }
    
    stringstream SS;
    
    dijkstra(&graph.at(0));
    
    for (unsigned i = 0; i < graph.size(); ++i) {
        if (graph.at(i).jugState.second == goal && graph.at(i).jugState.first == 0) {
            solutionF(SS, &graph.at(i));
            solution = SS.str();
            return 1;
        }
    }
    
    solution = "";
    
    
    return 0;
}

void Jug::solutionF(stringstream & solution, Vertex * current) { //assigns steps to solution in string
    Vertex * pre = current->prevV;
    Vertex * cur = current;
    stack<string> stacks;
    
    stringstream success;
    success << "success " << current->distance;
    stacks.push(success.str());
    
    while (cur != 0 && pre != 0) {
        if (cur->jugState == graph.at(pre->neighbors.at(0).first).jugState) {
            stacks.push("fill A");
        } else if (cur->jugState == graph.at(pre->neighbors.at(1).first).jugState) {
            stacks.push("fill B");
        } else if (cur->jugState == graph.at(pre->neighbors.at(2).first).jugState) {
            stacks.push("empty A");
        } else if (cur->jugState == graph.at(pre->neighbors.at(3).first).jugState) {
            stacks.push("empty B");
        } else if (cur->jugState == graph.at(pre->neighbors.at(4).first).jugState) {
            stacks.push("pour A B");
        } else if (cur->jugState == graph.at(pre->neighbors.at(5).first).jugState) {
            stacks.push("pour B A");
        }
        
        cur = pre;
        if (cur != 0) {
            pre = cur->prevV;
        }
    }
    
    while (!stacks.empty()) {
        solution << stacks.top();
        stacks.pop();
        if (!stacks.empty()) {
            solution << endl;
        }        
    }
}

void Jug::dijkstra(Vertex* start) {
    InitializeSingleSource(start);
    vector<Vertex*> cloud;
    Queue priorityQueue;
    
    for(unsigned i = 1; i < graph.size(); ++i) {
        priorityQueue.enqueue(&graph.at(i));
    }
    
    priorityQueue.enqueue(&graph.at(0));
    
    while(!priorityQueue.empty()) {
        Vertex* u = priorityQueue.end(); //points to lowest distance in queue
        priorityQueue.dequeue();
        cloud.push_back(u);
        
        for(unsigned yTho = 0; yTho < u->neighbors.size(); ++yTho) {
            int currRelax;
            if(yTho == 0) {
                currRelax = costFillA;
            }
            else if(yTho == 1) {
                currRelax = costFillB;
            }
            else if(yTho == 2) {
                currRelax = costEmptyA;
            }
            else if(yTho == 3) {
                currRelax = costEmptyB;
            }
            else if(yTho == 4) {
                currRelax = costPourAinB;
            }
            else {
                currRelax = costPourBinA;
            }
            
            relax(u, &graph.at(u->neighbors.at(yTho).first), currRelax);
            
            for(unsigned k = 0; k < priorityQueue.size(); ++k) {
                Vertex* end = priorityQueue.end();
                if(priorityQueue.at(k)->distance < end->distance) {
                    Vertex* v = priorityQueue.at(k);
                    priorityQueue.erase(k);
                    priorityQueue.enqueue(v);
                }
            }
            
        }
    }
    
    
    
}

void Jug::InitializeSingleSource(Vertex* start) {
    //all verticies distances = INT_MAX and prevV* = 0 in construction
    start->distance = 0;
}

Queue::Queue() {
    
}

void Queue::enqueue(Vertex* curr) {
    queue.push_back(curr);
}

void Queue::dequeue() {
    queue.pop_back();
}

bool Queue::empty() {
    if(queue.empty()) {
        return true;
    }
    return false;
}

Vertex* Queue::end() {
    return queue.at(queue.size() - 1);
}

void Jug::relax(Vertex* u, Vertex* v, int w) {
    if(v->distance > u->distance + w) {
        v->distance = u->distance + w;
        v->prevV = u;
    }
}

Vertex* Queue::at(unsigned i) {
    return queue.at(i);
} 

unsigned Queue::size() {
    return queue.size();
}

void Queue::erase(unsigned i) {
    queue.erase(queue.begin() + i);
}



