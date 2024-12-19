#ifndef PLAYER_H
#define PLAYER_H

#include "Engine/GameObject.h"

class Player : public GameObject {
 public:
  Player(const std::string& name = "Player");

  void Start() override;
  void Update() override;
};

#endif  // PLAYER_H
