/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Game.cpp
 * Author: op
 * 
 * Created on April 21, 2019, 1:56 PM
 */

#include "Game.h"

Game::Game() {
    map = new GameMap;
    pac = new Pacman;
    item = new Items;
}

Game::Game(const Game& orig) {
}

Game::~Game() {
}

void Game::checkMove(char key) {
    //Will later add event listener to call checkMove
    int thatPos;
    int limit;
    int pacPos = pac->getLocation();
    switch (key) {
        case 'a'://Left key
            thatPos = map->getGraph().at(pacPos).neighbors[0].first;
            limit = map->getGraph().at(pacPos).neighbors[0].second;
            break;
        case 'd'://Right key
            thatPos = map->getGraph().at(pacPos).neighbors[1].first;
            limit = map->getGraph().at(pacPos).neighbors[0].second;

            break;
        case 's'://Down key
            thatPos = map->getGraph().at(pacPos).neighbors[2].first;
            limit = map->getGraph().at(pacPos).neighbors[0].second;

            break;
        case 'w'://Up key
            thatPos = map->getGraph().at(pacPos).neighbors[3].first;
            limit = map->getGraph().at(pacPos).neighbors[0].second;

            break;
        default:
            break;
    }
    if (map->getGraph().at(thatPos).type == PACDOT) {
        map->getGraph().at(thatPos).type = EMPTY;
        pac->updateScore(10);
    } else if (map->getGraph().at(thatPos).type == POWER) {
        map->getGraph().at(thatPos).type = EMPTY;
        pac->updateScore(50);
    }
    pac->setLocation(thatPos);//Changes position of pacman to the location of the item
}
