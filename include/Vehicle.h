#ifndef VEHICLE_H
#define VEHICLE_H

#include "Engine/Animator.h"
#include "Engine/GameRenderer.h"
#include "box2d/box2d.h"

class Player;

class Vehicle {
 public:
  Vehicle(bool isDestroyable = false);
  virtual void Attach(Player* player) = 0;
  virtual void Update() = 0;
  virtual void FixedUpdate() = 0;
  virtual void Render(GameRenderer& renderer) = 0;
  virtual void Destroy() = 0;

  bool isDestroyable;

 protected:
  Animator animator;
  Player* player;
  b2BodyId bodyId;
};

class JetpackBullet {
 public:
  JetpackBullet();
  void Update();
  void Render(GameRenderer& renderer);
  void Activate(const sf::Vector2f& position, float angle);
  bool IsActive() const;

 private:
  sf::Sprite sprite;
  float speed = 10.f;
  bool isActive = false;
};

class JetpackBulletPool {
 public:
  JetpackBulletPool(size_t poolSize);
  ~JetpackBulletPool();

  JetpackBullet* CreateBullet(const sf::Vector2f& position, float angle);
  void UpdateAll();
  void RenderAll(GameRenderer& renderer);

 private:
  std::vector<JetpackBullet*> pool;
  size_t nextFreeIndex = 0;
};

class Jetpack : public Vehicle {
 public:
  Jetpack();
  void Attach(Player* player) override;
  void Update() override;
  void FixedUpdate() override;
  void Render(GameRenderer& renderer) override;
  void Destroy() override;

 private:
  bool isThrusting;
  float thrustForce = 40.f;
  bool onGround;
  JetpackBulletPool bulletPool;
  float fireRate = 1 / 30.f;  // Fire rate in seconds
  float lastFireTime;
  float fireCounter;  // Time counter for firing bullets
};

#endif  // VEHICLE_H