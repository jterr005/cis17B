// the compile code is g++ main.cpp Jug.cpp -o main 

#include <iostream>
#include <string>
#include "Jug.h"

using namespace std;

int main () {

   string solution;
   Jug bead(3, 5, 4, 1, 2, 3, 4, 5, 6);
   if (bead.solve(solution) != 1) {
      cout << "Error 3" << endl;
   }
   cout << solution << endl << endl;


   solution = "";
   Jug hea(3, 5, 4, 1, 1, 1, 1, 1, 2);         
   if(hea.solve(solution) != 1) {
      cout << "Error 3" << endl;
   }
   cout << solution << endl;


return 0;
}