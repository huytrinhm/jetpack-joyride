#ifndef VEHICLE_H
#define VEHICLE_H

#include "Engine/Animator.h"
#include "Engine/GameRenderer.h"

class Player;

class Vehicle {
 public:
  Vehicle(bool isDestroyable = false);
  virtual void Attach(Player* player) = 0;
  virtual void Update() = 0;
  virtual void Render(GameRenderer& renderer) = 0;
  virtual void Destroy() = 0;

  bool isDestroyable;

 protected:
  Animator animator;
  Player* player;
};

class Jetpack : public Vehicle {
 public:
  Jetpack();
  void Attach(Player* player) override;
  void Update() override;
  void Render(GameRenderer& renderer) override;
  void Destroy() override;
};

#endif  // VEHICLE_H