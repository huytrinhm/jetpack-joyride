#ifndef HARMFUL_H
#define HARMFUL_H

#include "CollidableGameObject.h"

class HarmfulGameObject : public CollidableGameObject {
 public:
  void Collide(Player* player) override {
    if (!isActive)
      return;

    player->HandleHarmfulCollision();
  }
};

#endif  // HARMFUL_H
