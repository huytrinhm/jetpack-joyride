#include "ScrollerSpawner.h"
#include "Config.h"
#include "Engine/GameManager.h"
#include "Utilities.h"

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