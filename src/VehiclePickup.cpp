#include "VehiclePickup.h"
#include <iostream>
#include "AssetManager.h"
#include "Config.h"
#include "Engine/Animator.h"
#include "Engine/PhysicBody.h"
#include "GameManager.h"
#include "Utilities.h"
#include "box2d/box2d.h"

VehiclePickup::VehiclePickup(VehicleType pickupType,
                             const sf::Vector2f& position,
                             bool isActive)
    : pickupType(pickupType), isActive(isActive) {
  transform.position = position;

  b2BodyDef bodyDef = b2DefaultBodyDef();
  bodyDef.type = b2_kinematicBody;
  bodyDef.linearVelocity = {-pixelToMeter(GameManager::Instance().scrollSpeed),
                            0};
  bodyDef.position = pixelToMeter(position);

  b2BodyId bodyId = b2CreateBody(GameManager::Instance().worldId, &bodyDef);

  b2ShapeDef shapeDef = b2DefaultShapeDef();
  shapeDef.isSensor = true;
  shapeDef.userData = static_cast<CollidableGameObject*>(this);

  b2Polygon box = b2MakeBox(pixelToMeter(20), pixelToMeter(20));
  b2CreatePolygonShape(bodyId, &shapeDef, &box);

  this->AddComponent<PhysicBody>(bodyId);

  animator = this->AddComponent<Animator>(
      AssetManager::Instance().GetTexture("vehiclePickup"));
  auto anim = animator->AddAnimation("default", true, 5);
  for (int i = 0; i < 8; i++)
    anim->frames.emplace_back(sf::IntRect{i * 64, 0, 64, 64}, 0.1f);
  animator->PlayAnimation("default");
}

void VehiclePickup::Render(GameRenderer& renderer) {
  if (!isActive)
    return;
  animator->Render(renderer);
}

void VehiclePickup::Update() {
  if (GameManager::Instance().player->InVehicle()) {
    isActive = false;
  }
}

void VehiclePickup::Collide(Player* player) {
  if (!isActive)
    return;

  switch (pickupType) {
    case VehicleType::GRAVITY_SUIT:
      player->Equip(GameManager::Instance().GetVehicle("gravitySuit"));
      break;
    case VehicleType::STOMPER:
      player->Equip(GameManager::Instance().GetVehicle("stomper"));
      break;
  }

  isActive = false;
}
