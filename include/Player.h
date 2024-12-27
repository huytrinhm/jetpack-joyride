#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Engine/GameObject.h"
#include "Engine/GameRenderer.h"
#include "Vehicle.h"

class Player : public GameObject {
 public:
  Player(Vehicle* defaultVehicle);

  void Start() override;
  void Update() override;
  void FixedUpdate() override;
  void Render(GameRenderer& renderer) override;
  void Equip(Vehicle* vehicle);
  void HandleHarmfulCollision();
  void HandlePickupCollision();

 private:
  Vehicle* vehicle;
  Vehicle* defaultVehicle;
};

#endif  // PLAYER_H
