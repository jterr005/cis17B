
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

