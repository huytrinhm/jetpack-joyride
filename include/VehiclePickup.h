#ifndef VEHICLE_PICKUP_H
#define VEHICLE_PICKUP_H

#include "CollidableGameObject.h"
#include "Engine/Animator.h"
#include "ScrollerSpawner.h"

enum VehicleType { GRAVITY_SUIT, STOMPER };

class VehiclePickup : public CollidableGameObject {
 public:
  VehiclePickup(VehicleType pickupType,
                const sf::Vector2f& position,
                bool isActive = true);
  void Update() override;
  void Render(GameRenderer& renderer) override;
  void Collide(Player* player) override;

 private:
  Animator* animator;
  VehicleType pickupType;
  bool isActive;
};

#endif  // VEHICLE_PICKUP_H