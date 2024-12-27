#ifndef ZAPPER_H
#define ZAPPER_H

#include <deque>
#include "Engine/Animator.h"
#include "Engine/GameObject.h"
#include "Harmful.h"

enum ZapperType {
  ZAPPER_HORIZONTAL,
  ZAPPER_VERTICAL,
  ZAPPER_MAIN_DIAGONAL,
  ZAPPER_SUB_DIAGONAL
};

class Zapper : public HarmfulGameObject {
 public:
  Zapper(ZapperType zapperType,
         const sf::Vector2f& position,
         int length,
         bool isActive = true);
  //   void Start() override;
  void Update() override;
  //   void FixedUpdate() override;
  void Render(GameRenderer& renderer) override;

 private:
  sf::RenderTexture zapperRenderTexture;
  sf::Sprite zapperSprite;
  sf::Sprite zapperEffectSprite;
  sf::Sprite zapperHeadSprite;
  int length;
  bool isActive;
  int currentFrame;
};

class ScrollerSpawner : public GameObject {
 public:
  ScrollerSpawner(const std::string& name);
  // void Start() override;
  void Update() override;
  void FixedUpdate() override;
  void Render(GameRenderer& renderer) override;

 private:
  float scrollerDistance;
  float spawnDistance;
  std::deque<Zapper> zappers;
  void SpawnRandomZapper();
  void RemovePassedZappers();
};

#include <iostream>
#include "AssetManager.h"
#include "Config.h"
#include "Engine/Animator.h"
#include "Engine/GameManager.h"
#include "Engine/PhysicBody.h"
#include "Utilities.h"
#include "box2d/box2d.h"

Zapper::Zapper(ZapperType zapperType,
               const sf::Vector2f& position,
               int length,
               bool isActive)
    : length(length), isActive(isActive), currentFrame(0) {
  transform.position = position;

  zapperRenderTexture.create(length * 16 + 2 * 32, 32);
  zapperSprite.setTexture(zapperRenderTexture.getTexture());
  zapperSprite.setOrigin(zapperSprite.getLocalBounds().width / 2,
                         zapperSprite.getLocalBounds().height / 2);
  zapperEffectSprite.setTexture(
      AssetManager::Instance().GetTexture("zapperEffect"));
  zapperHeadSprite.setTexture(
      AssetManager::Instance().GetTexture("zapperHead"));
  zapperHeadSprite.setOrigin(16, 16);

  float pixelLength = length * 16 + 32;
  float pixelWidth = 22;
  const b2Vec2 scale = pixelToMeter({pixelWidth, pixelLength});

  b2BodyDef bodyDef = b2DefaultBodyDef();
  bodyDef.type = b2_kinematicBody;
  bodyDef.linearVelocity = {-pixelToMeter(GameManager::Instance().scrollSpeed),
                            0};
  bodyDef.position = pixelToMeter(position);

  if (zapperType == ZAPPER_HORIZONTAL) {
    bodyDef.rotation = b2MakeRot(0);
    zapperSprite.setRotation(0);
  } else if (zapperType == ZAPPER_MAIN_DIAGONAL) {
    bodyDef.rotation = b2MakeRot(B2_PI / 4);
    zapperSprite.setRotation(45);
  } else if (zapperType == ZAPPER_SUB_DIAGONAL) {
    bodyDef.rotation = b2MakeRot(-B2_PI / 4);
    zapperSprite.setRotation(-45);
  } else {
    bodyDef.rotation = b2MakeRot(B2_PI / 2);
    zapperSprite.setRotation(90);
  }

  b2BodyId bodyId = b2CreateBody(GameManager::Instance().worldId, &bodyDef);

  b2ShapeDef shapeDef = b2DefaultShapeDef();
  shapeDef.isSensor = true;
  shapeDef.userData = static_cast<CollidableGameObject*>(this);

  float radius = scale.x / 2;
  float centerOffset = scale.y / 2 - radius;
  b2Capsule capsule = {{-centerOffset, 0}, {centerOffset, 0}, radius};
  b2CreateCapsuleShape(bodyId, &shapeDef, &capsule);

  this->AddComponent<PhysicBody>(bodyId);
}

sf::IntRect getZapperEffectFrame(int frame) {
  return {frame * 16, 0, 16, 29};
}

sf::IntRect getZapperHeadFrame(int frame) {
  return {(frame % 4) * 32, (frame / 4) * 32, 32, 32};
}

void Zapper::Render(GameRenderer& renderer) {
  zapperRenderTexture.clear(sf::Color::Transparent);

  for (int i = 0; i < length; i++) {
    zapperEffectSprite.setPosition({32 + 16.f * i, 1});
    zapperEffectSprite.setTextureRect(getZapperEffectFrame(i));
    zapperRenderTexture.draw(zapperEffectSprite);
  }

  // Render head
  zapperHeadSprite.setPosition({16 + 8, 16});
  zapperHeadSprite.setTextureRect(getZapperHeadFrame(0));
  zapperHeadSprite.setRotation(90);
  zapperRenderTexture.draw(zapperHeadSprite);

  zapperHeadSprite.setPosition({length * 16.f + 32 + 16 - 8, 16});
  zapperHeadSprite.setTextureRect(getZapperHeadFrame(0));
  zapperHeadSprite.setRotation(-90);
  zapperRenderTexture.draw(zapperHeadSprite);

  zapperRenderTexture.display();

  renderer.AddDrawable(4, &zapperSprite);
}

void Zapper::Update() {
  zapperSprite.setPosition(transform.position);
}

ScrollerSpawner::ScrollerSpawner(const std::string& name)
    : GameObject(name), scrollerDistance(0), spawnDistance(500) {}

void ScrollerSpawner::Update() {
  scrollerDistance +=
      GameManager::Instance().scrollSpeed * GameManager::Instance().deltaTime;

  if (scrollerDistance > spawnDistance) {
    scrollerDistance = 0;
    SpawnRandomZapper();
  }

  for (auto& zapper : zappers) {
    zapper.DoUpdate();
  }

  RemovePassedZappers();
}

void ScrollerSpawner::SpawnRandomZapper() {
  ZapperType type = static_cast<ZapperType>(rand() % 4);
  int length = rand() % 6 + 1;
  float w, h;
  if (type == ZAPPER_HORIZONTAL) {
    w = 16 * length + 2 * 32;
    h = 32;
  } else if (type == ZAPPER_VERTICAL) {
    w = 32;
    h = 16 * length + 2 * 32;
  } else {
    w = 16 * length + 2 * 32;
    h = 16 * length + 2 * 32;
  }
  float remainingW = spawnDistance - w;
  float remainingH = WORLD_HEIGHT - 88 - h;
  float dx = randomIntInRange(-remainingW / 2, remainingW / 2);
  float dy = randomIntInRange(-remainingH / 2, remainingH / 2);
  float x = WORLD_WIDTH + 200 + dx;
  float y = WORLD_HEIGHT / 2 + dy;

  zappers.emplace_back(type, sf::Vector2f(x, y), length);
}

void ScrollerSpawner::RemovePassedZappers() {
  while (!zappers.empty() && zappers.front().transform.position.x < -100) {
    zappers.pop_front();
  }
}

void ScrollerSpawner::Render(GameRenderer& renderer) {
  for (auto& zapper : zappers) {
    zapper.Render(renderer);
  }
}

void ScrollerSpawner::FixedUpdate() {
  for (auto& zapper : zappers) {
    zapper.DoFixedUpdate();
  }
}

#endif  // ZAPPER_H