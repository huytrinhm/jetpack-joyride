#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Engine/Animator.h"
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
  void SetShield(bool isShielded);
  bool IsShielded();
  bool InVehicle();
  sf::Vector2f GetPosition() const;

 private:
  void SetInvincible(bool isInvincible, float duration);
  Vehicle* vehicle;
  Vehicle* defaultVehicle;
  bool isShielded = false;
  Animator* shieldAnimator;
  bool isInvincible = false;
  float invincibleTimer;
};

#endif  // PLAYER_H
