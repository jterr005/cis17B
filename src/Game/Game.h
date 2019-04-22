/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Game.h
 * Author: Eric Perez
 *
 * Created on April 21, 2019, 1:56 PM
 */

#ifndef GAME_H
#define GAME_H
#include "Pacman.h"
#include "GameMap.h"
#include "Items.h"
#include <climits> 
class Game {
public:
    Game();
    Game(const Game& orig);
    virtual ~Game();
    void checkMove(char);
private:
    Pacman *pac;
    Items *item;
    GameMap *map;
         
};

#endif /* GAME_H */

