#include "Vehicle.h"
#include <SFML/Graphics.hpp>
#include "AssetManager.h"
#include "Engine/GameManager.h"
#include "Engine/InputManager.h"
#include "Engine/PhysicBody.h"
#include "Player.h"
#include "Utilities.h"
#include "box2d/box2d.h"

b2BodyId createJetpackBody(sf::Vector2f position) {
  const b2Vec2 scale = pixelToMeter({18, 36});

  b2BodyDef bodyDef = b2DefaultBodyDef();
  bodyDef.type = b2_dynamicBody;
  bodyDef.position = pixelToMeter(position);
  bodyDef.linearDamping = 0.0f;
  bodyDef.fixedRotation = true;
  bodyDef.gravityScale = 2.0f;
  b2BodyId bodyId = b2CreateBody(GameManager::Instance().worldId, &bodyDef);

  b2ShapeDef shapeDef = b2DefaultShapeDef();
  shapeDef.friction = 0.0f;
  shapeDef.restitution = 0.0f;

  float radius = scale.x / 2;
  float centerOffset = scale.y / 2 - radius;
  b2Capsule capsule = {{0, -centerOffset}, {0, centerOffset}, radius};
  b2CreateCapsuleShape(bodyId, &shapeDef, &capsule);

  b2MassData massData = b2Body_GetMassData(bodyId);
  massData.mass = 1;
  b2Body_SetMassData(bodyId, massData);

  b2PrismaticJointDef jointDef = b2DefaultPrismaticJointDef();
  jointDef.bodyIdA = GameManager::Instance().playerPivotId;
  jointDef.bodyIdB = bodyId;
  jointDef.localAxisA = {0, 1};

  b2CreatePrismaticJoint(GameManager::Instance().worldId, &jointDef);

  return bodyId;
}

Vehicle::Vehicle(bool isDestroyable) : isDestroyable(isDestroyable) {}

Jetpack::Jetpack() {
  animator.SetTexture(AssetManager::Instance().GetTexture("barry"));
  Animation* animation = nullptr;

  animation = animator.AddAnimation("running");
  for (int i = 0; i < 4; i++)
    animation->frames.emplace_back(sf::IntRect{i * 48, 0 * 72, 48, 72}, 0.1f,
                                   sf::Vector2f{-5, 13});

  animation = animator.AddAnimation("flying");
  for (int i = 0; i < 4; i++)
    animation->frames.emplace_back(sf::IntRect{i * 48, 1 * 72, 48, 72}, 0.1f,
                                   sf::Vector2f{-5, 13});

  animation = animator.AddAnimation("falling", false);
  for (int i = 0; i < 4; i++)
    animation->frames.emplace_back(sf::IntRect{i * 48, 2 * 72, 48, 72}, 0.1f,
                                   sf::Vector2f{-5, 13});

  animation = animator.AddAnimation("landing", false);
  for (int i = 0; i < 4; i++)
    animation->frames.emplace_back(sf::IntRect{i * 48, 3 * 72, 48, 72}, 0.1f,
                                   sf::Vector2f{-5, 13});

  animation = animator.AddAnimation("dead", false);
  for (int i = 0; i < 4; i++)
    animation->frames.emplace_back(sf::IntRect{i * 48, 4 * 72, 48, 72}, 0.1f,
                                   sf::Vector2f{-5, 13});

  animation = animator.AddAnimation("dead_falling");
  for (int i = 0; i < 4; i++)
    animation->frames.emplace_back(sf::IntRect{i * 48, 6 * 72, 48, 72}, 0.1f,
                                   sf::Vector2f{-5, 13});

  animation = animator.AddAnimation("laying", false);
  animation->frames.emplace_back(sf::IntRect{48, 7 * 72, 48, 72}, 0.1f,
                                 sf::Vector2f{-5, 13});
  animation->frames.emplace_back(sf::IntRect{0, 7 * 72, 48, 72}, 0.1f,
                                 sf::Vector2f{-5, 13});
}

void Jetpack::Attach(Player* player) {
  this->player = player;
  animator.gameObject = (GameObject*)player;
  bodyId = createJetpackBody(player->transform.position);
  player->AddComponent<PhysicBody>(bodyId);
  animator.PlayAnimation("running");
  isThrusting = false;
}

void Jetpack::Update() {
  int bodyContactCapacity = b2Body_GetContactCapacity(bodyId);
  b2ContactData contactData[bodyContactCapacity];
  int bodyContactCount =
      b2Body_GetContactData(bodyId, contactData, bodyContactCapacity);

  onGround = false;
  for (int i = 0; i < bodyContactCount; i++) {
    b2BodyId bodyIdA = b2Shape_GetBody(contactData[i].shapeIdA);
    b2BodyId bodyIdB = b2Shape_GetBody(contactData[i].shapeIdB);
    if (B2_ID_EQUALS(bodyIdA, GameManager::Instance().groundId) ||
        B2_ID_EQUALS(bodyIdB, GameManager::Instance().groundId)) {
      onGround = true;
      break;
    }
  }

  if (InputManager::Instance().IsKeyDown(sf::Keyboard::Space)) {
    isThrusting = true;
    animator.PlayAnimation("flying");
  } else {
    isThrusting = false;
    if (onGround) {
      animator.PlayAnimation("running");
    } else {
      animator.PlayAnimation("falling");
    }
  }

  animator.Update();
}

void Jetpack::FixedUpdate() {
  if (isThrusting) {
    player->GetComponent<PhysicBody>()->ApplyForce({0, -thrustForce});
  }
}

void Jetpack::Render(GameRenderer& renderer) {
  animator.Render(renderer);
}

void Jetpack::Destroy() {}
