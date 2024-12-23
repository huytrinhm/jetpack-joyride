#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Engine/GameObject.h"
#include "Engine/GameRenderer.h"
#include "Vehicle.h"

class Player : public GameObject {
 public:
  Player(const std::string& name, Vehicle* defaultVehicle);

  void Start() override;
  void Update() override;
  void Render(GameRenderer& renderer) override;
  void Equip(Vehicle* vehicle);

 private:
  Vehicle* vehicle;
};

#endif  // PLAYER_H
