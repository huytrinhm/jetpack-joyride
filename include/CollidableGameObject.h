#ifndef COLLIDABLE_GAME_OBJECT_H
#define COLLIDABLE_GAME_OBJECT_H

#include "Engine/GameObject.h"
#include "Player.h"

class CollidableGameObject : public GameObject {
 public:
  virtual void Collide(Player* player) = 0;

 protected:
  bool isActive = true;
};

#endif  // COLLIDABLE_GAME_OBJECT_H