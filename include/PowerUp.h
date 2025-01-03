#ifndef POWERUP_H
#define POWERUP_H

#include <deque>
#include <memory>
#include "CollidableGameObject.h"
#include "Engine/Component.h"
#include "Engine/GameObject.h"
#include "ScrollerSpawner.h"
#include "box2d/box2d.h"

class Pickup : public CollidableGameObject {
 public:
  Pickup(sf::Vector2f position,
         const std::string& textureName,
         float period,
         float phi,
         float amplitude);
  void Update() override;
  void FixedUpdate() override;
  void Render(GameRenderer& renderer) override;

 private:
  float omega;
  b2Rot phi;
  float amplitude;

 protected:
  bool isActive;
};

class ShieldPickup : public Pickup {
 public:
  ShieldPickup(sf::Vector2f position, float period, float phi, float amplitude);
  void Collide(Player* player) override;
};

class FastforwardPickup : public Pickup {
 public:
  FastforwardPickup(sf::Vector2f position,
                    float period,
                    float phi,
                    float amplitude);
  void Collide(Player* player) override;
};

class PickupSpawner : public ScrollerSpawner {
 public:
  PickupSpawner();

 private:
  void Spawn() override;

  void SpawnShieldPickup();
  void SpawnFastforwardPickup();
};

#endif  // POWERUP_H