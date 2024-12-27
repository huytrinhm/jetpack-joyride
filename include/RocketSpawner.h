#pragma once
#include <deque>
#include "Engine/GameObject.h"
#include "Player.h"
#include "ScrollerSpawner.h"

class RocketSpawner : public ScrollerSpawner {
 public:
  RocketSpawner();

 private:
  void Spawn() override;
};
