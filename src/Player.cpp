#include "Player.h"
#include "AssetManager.h"
#include "Engine/Animator.h"
#include "Engine/GameManager.h"
#include "Engine/PhysicBody.h"
#include "Utilities.h"

Player::Player(const std::string& name, Vehicle* defaultVehicle)
    : GameObject(name), vehicle(defaultVehicle) {}

void Player::Start() {
  transform.position = {150, 100};
  Equip(vehicle);
}

void Player::Update() {
  vehicle->Update();
}

void Player::Render(GameRenderer& renderer) {
  vehicle->Render(renderer);
}

void Player::Equip(Vehicle* vehicle) {
  this->vehicle = vehicle;
  vehicle->Attach(this);
}
