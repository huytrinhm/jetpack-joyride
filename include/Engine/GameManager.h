#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "box2d/box2d.h"

class GameManager {
 public:
  static GameManager& Instance() {
    static GameManager instance;
    return instance;
  }

  float deltaTime;
  float unscaledDeltaTime;
  float timeScale = 1.0f;
  float fixedDeltaTime = 1 / 60.f;
  sf::RenderTarget* renderTarget;
  b2WorldId worldId;
  b2BodyId playerPivotId;

 private:
  GameManager() : renderTarget(nullptr) {}
  GameManager(const GameManager&) = delete;
  GameManager& operator=(const GameManager&) = delete;
};

#endif  // GAMEMANAGER_H
