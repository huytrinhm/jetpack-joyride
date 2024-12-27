#include "PowerUp.h"
#include <SFML/Graphics.hpp>
#include "AssetManager.h"
#include "Engine/Animator.h"
#include "Engine/GameManager.h"
#include "Engine/PhysicBody.h"
#include "Player.h"
#include "Utilities.h"
#include "box2d/box2d.h"

Pickup::Pickup(sf::Vector2f position,
               const std::string& textureName,
               float period,
               float phi,
               float amplitude)
    : omega(2 * B2_PI / period),
      phi(b2MakeRot(phi)),
      amplitude(pixelToMeter(amplitude)),
      isActive(true) {
  transform.position = position;

  auto animator = this->AddComponent<Animator>(
      AssetManager::Instance().GetTexture(textureName));
  auto animation = animator->AddAnimation("default", true, 5);
  for (int i = 0; i < 8; i++)
    animation->frames.emplace_back(
        sf::IntRect{(i % 4) * 32, (i / 4) * 32, 32, 32}, 0.1f);
  animator->PlayAnimation("default");

  b2BodyDef bodyDef = b2DefaultBodyDef();
  bodyDef.type = b2_kinematicBody;
  bodyDef.position = pixelToMeter(position);

  b2BodyId bodyId = b2CreateBody(GameManager::Instance().worldId, &bodyDef);

  b2ShapeDef shapeDef = b2DefaultShapeDef();
  shapeDef.isSensor = true;
  shapeDef.userData = this;

  b2Circle circle = {b2Vec2_zero, pixelToMeter(16)};
  b2CreateCircleShape(bodyId, &shapeDef, &circle);

  this->AddComponent<PhysicBody>(bodyId);
}

void Pickup::Update() {}

void Pickup::FixedUpdate() {
  if (!isActive)
    return;

  auto physicBody = GetComponent<PhysicBody>();
  phi =
      b2IntegrateRotation(phi, omega * GameManager::Instance().fixedDeltaTime);
  float v_y = amplitude * omega * phi.c;

  physicBody->SetVelocity(
      {-pixelToMeter(GameManager::Instance().scrollSpeed * 0.7), v_y});
}

void Pickup::Render(GameRenderer& renderer) {
  if (!isActive)
    return;

  this->GetComponent<Animator>()->Render(renderer);
}

void ShieldPickup::Collide(Player* player) {
  std::cerr << "Shield applied" << std::endl;
  isActive = false;
  CollidableGameObject::isActive = false;
}

ShieldPickup::ShieldPickup(sf::Vector2f position,
                           float period,
                           float phi,
                           float amplitude)
    : Pickup(position, "shield", period, phi, amplitude) {}
