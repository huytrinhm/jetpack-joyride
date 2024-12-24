#include "Vehicle.h"
#include <SFML/Graphics.hpp>
#include "AssetManager.h"
#include "Config.h"
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

JetpackBullet::JetpackBullet() {
  sprite.setTexture(AssetManager::Instance().GetTexture("bullet"));
  sprite.setOrigin(sprite.getLocalBounds().width / 2,
                   sprite.getLocalBounds().height / 2);
}

void JetpackBullet::Update() {
  if (!isActive)
    return;

  sprite.move(speed * cos(sprite.getRotation() * B2_PI / 180.0f),
              speed * sin(sprite.getRotation() * B2_PI / 180.0f));
  if (sprite.getPosition().y >= WORLD_HEIGHT - 40 + randomFloatInRange(-7, 5)) {
    isActive = false;
  }
}

void JetpackBullet::Render(GameRenderer& renderer) {
  if (!isActive)
    return;
  renderer.AddDrawable(3, &sprite);
}

void JetpackBullet::Activate(const sf::Vector2f& position, float angle) {
  sprite.setPosition(position);
  sprite.setRotation(angle);
  isActive = true;
}

bool JetpackBullet::IsActive() const {
  return isActive;
}

JetpackBulletPool::JetpackBulletPool(size_t poolSize) {
  pool.resize(poolSize);
  for (size_t i = 0; i < poolSize; ++i) {
    pool[i] = new JetpackBullet();
  }
}

JetpackBulletPool::~JetpackBulletPool() {
  for (auto bullet : pool) {
    delete bullet;
  }
}

JetpackBullet* JetpackBulletPool::CreateBullet(const sf::Vector2f& position,
                                               float angle) {
  if (nextFreeIndex >= pool.size())
    return nullptr;

  JetpackBullet* bullet = pool[nextFreeIndex++];
  bullet->Activate(position, angle);
  return bullet;
}

void JetpackBulletPool::UpdateAll() {
  for (size_t i = 0; i < nextFreeIndex; ++i) {
    if (!pool[i]->IsActive()) {
      std::swap(pool[i], pool[--nextFreeIndex]);
      continue;
    }
    pool[i]->Update();
  }
}

void JetpackBulletPool::RenderAll(GameRenderer& renderer) {
  for (auto bullet : pool) {
    bullet->Render(renderer);
  }
}

Jetpack::Jetpack() : bulletPool(30) {
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

  fireCounter = 0;
}

void Jetpack::Attach(Player* player) {
  this->player = player;
  animator.gameObject = (GameObject*)player;
  bodyId = createJetpackBody(player->transform.position);
  player->AddComponent<PhysicBody>(bodyId);
  animator.PlayAnimation("running");
  isThrusting = false;
  lastFireTime = 0;
  fireCounter = 0;
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

  if (isThrusting) {
    fireCounter += GameManager::Instance().deltaTime;
    if (fireCounter >= fireRate) {
      float angle = 90 + randomFloatInRange(-8, 8);
      bulletPool.CreateBullet(player->transform.position +
                                  sf::Vector2f{-10 + -(angle - 90) * 0.8f, 32},
                              angle);
      fireCounter = 0;
    }
  } else {
    fireCounter = 0;
  }

  bulletPool.UpdateAll();
  animator.Update();
}

void Jetpack::FixedUpdate() {
  if (isThrusting) {
    player->GetComponent<PhysicBody>()->ApplyForce({0, -thrustForce});
  }
}

void Jetpack::Render(GameRenderer& renderer) {
  animator.Render(renderer);
  bulletPool.RenderAll(renderer);
}

void Jetpack::Destroy() {}
