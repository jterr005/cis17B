
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

