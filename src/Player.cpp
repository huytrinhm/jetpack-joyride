#include "Player.h"
#include <iostream>
#include "AssetManager.h"
#include "Engine/Animator.h"
#include "Engine/PhysicBody.h"
#include "GameManager.h"
#include "Harmful.h"
#include "PowerUp.h"
#include "Utilities.h"
#include "Vehicle.h"
#include "box2d/box2d.h"

Player::Player(Vehicle* defaultVehicle) : defaultVehicle(defaultVehicle) {
  shieldAnimator = this->AddComponent<Animator>(
      AssetManager::Instance().GetTexture("shieldField"));
  auto animation = shieldAnimator->AddAnimation("default", true, 7);
  animation->frames.emplace_back(sf::IntRect{0, 0, 64, 64}, 1.0f,
                                 sf::Vector2f{-4, 0});
  animation->frames.emplace_back(sf::IntRect{64, 0, 64, 64}, 1.0f,
                                 sf::Vector2f{-4, 0});
  for (int i = 2; i < 5; i++)
    animation->frames.emplace_back(
        sf::IntRect{(i % 4) * 64, (i / 4) * 64, 64, 64}, 0.1f,
        sf::Vector2f{-4, 0});
  shieldAnimator->PlayAnimation("default");
}

void Player::Start() {
  transform.position = {150, 100};
  Equip(defaultVehicle);
}

void Player::Update() {
  vehicle->Update();
}

void Player::FixedUpdate() {
  b2SensorEvents sensorEvents =
      b2World_GetSensorEvents(GameManager::Instance().worldId);
  for (int i = 0; i < sensorEvents.beginCount; i++) {
    b2SensorBeginTouchEvent* beginTouch = sensorEvents.beginEvents + i;
    void* visitorData = b2Shape_GetUserData(beginTouch->visitorShapeId);
    void* sensorData = b2Shape_GetUserData(beginTouch->sensorShapeId);
    if (visitorData != this)
      continue;

    CollidableGameObject* other =
        static_cast<CollidableGameObject*>(sensorData);
    other->Collide(this);
  }

  vehicle->FixedUpdate();
}

void Player::Render(GameRenderer& renderer) {
  vehicle->Render(renderer);
  if (isShielded && !vehicle->isDestroyable)
    shieldAnimator->Render(renderer);
}

void Player::Equip(Vehicle* vehicle) {
  RemoveComponent<PhysicBody>();
  this->vehicle = vehicle;
  vehicle->Attach(this);
}

void Player::HandleHarmfulCollision() {
  if (vehicle->isDestroyable) {
    vehicle->Destroy();
    Equip(defaultVehicle);
  } else if (isShielded) {
    SetShield(false);
  } else {
    GameManager::Instance().GameOver();
  }
}

void Player::HandlePickupCollision() {}

void Player::SetShield(bool isShielded) {
  this->isShielded = isShielded;
}

bool Player::IsShielded() {
  return isShielded;
}

bool Player::InVehicle() {
  return vehicle != defaultVehicle;
}

sf::Vector2f Player::GetPosition() const {
  return transform.position;
}
