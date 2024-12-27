#include "ScrollerSpawner.h"
#include "Config.h"
#include "Engine/GameManager.h"
#include "Utilities.h"

ScrollerSpawner::ScrollerSpawner(float spawnDistance, float variance)
    : scrollerDistance(0), spawnDistance(spawnDistance), variance(variance) {}

void ScrollerSpawner::Update() {
  scrollerDistance +=
      GameManager::Instance().scrollSpeed * GameManager::Instance().deltaTime;

  float spawnVariation =
      (variance > 0) ? randomFloatInRange(-variance, variance) : 0;

  if (scrollerDistance > spawnDistance + spawnVariation) {
    scrollerDistance = 0;
    Spawn();
  }

  for (auto& obj : objects) {
    obj->DoUpdate();
  }

  Cleanup();
}

void ScrollerSpawner::Cleanup() {
  while (!objects.empty() && objects.front()->transform.position.x < -100) {
    objects.pop_front();
  }
}

void ScrollerSpawner::Render(GameRenderer& renderer) {
  for (auto& obj : objects) {
    obj->Render(renderer);
  }
}

void ScrollerSpawner::FixedUpdate() {
  for (auto& obj : objects) {
    obj->DoFixedUpdate();
  }
}