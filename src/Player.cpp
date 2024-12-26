#include "Player.h"
#include <iostream>
#include "AssetManager.h"
#include "Engine/Animator.h"
#include "Engine/GameManager.h"
#include "Engine/PhysicBody.h"
#include "Harmful.h"
#include "Utilities.h"
#include "Vehicle.h"
#include "box2d/box2d.h"

Player::Player(const std::string& name, Vehicle* defaultVehicle)
    : GameObject(name), defaultVehicle(defaultVehicle) {}

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

    // Check if sensorData is Harmful
    Harmful* harmful = static_cast<Harmful*>(sensorData);
    if (harmful) {
      if (vehicle->isDestroyable) {
        vehicle->Destroy();
        Equip(defaultVehicle);
      } else {
        GameManager::Instance().GameOver();
      }
    }
  }
  vehicle->FixedUpdate();
}

void Player::Render(GameRenderer& renderer) {
  vehicle->Render(renderer);
}

void Player::Equip(Vehicle* vehicle) {
  this->vehicle = vehicle;
  vehicle->Attach(this);
}
