/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Pacman.h
 * Author: Eric Perez
 *
 * Created on April 19, 2019, 5:20 AM
 */

#ifndef PACMAN_H
#define PACMAN_H
using namespace std;

class Pacman {
public:
    Pacman();
    Pacman(const Pacman& orig);
    virtual ~Pacman();
    //Sets the location of Pacman at the start of the game

    void setLocation(int i) {
        position = i;
    };
    //gets location of pacman
    int getLocation() {
        return position;
    };
    void updateScore(int s){
        score+=s;
    };
private:
    int position=114;//spawn location of pacman
    int lives=3;
    int score=0;
    
};

#endif /* PACMAN_H */

