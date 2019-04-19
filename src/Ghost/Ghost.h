#ifndef GHOST_H
#define GHOST_H

class Ghost
{
private:
  int startX;
  int startY;
  int newPos;
  int dir;
 public:
  Ghost();
  void randGhost();
  void scatter();
  void chase();
  void fear();
  void death();
  
}

#endif
