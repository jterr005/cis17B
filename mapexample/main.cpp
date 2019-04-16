/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Jason
 *
 * Created on April 15, 2019, 1:07 PM
 */

#include <cstdlib>
#include <iostream>
#include <unistd.h>//usleep
#include <stdio.h>

#include "inputHandling.h"
using namespace std;



int main(int argc, char** argv) {
    bool stop = false; 
    inputHandling test; 
    do{
        int key = test.getch();
        cout << (char) key << ' ';
        usleep(33.33); //for 30ish frames per second counted in milliseconds
        if((char) key == 'p'){
            stop = true; 
        }
    }while(stop != true); 
    return 0;
}


