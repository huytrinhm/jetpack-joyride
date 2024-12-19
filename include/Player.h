#pragma once

#include "Engine/GameObject.h"

class Player : public GameObject {
 public:
  Player(const std::string& name = "Player");

  void Start() override;
  void Update() override;
};
