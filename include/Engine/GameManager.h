#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <SFML/Graphics.hpp>

class GameManager {
 public:
  static GameManager& Instance() {
    static GameManager instance;
    return instance;
  }

  float deltaTime;
  float unscaledDeltaTime;
  float timeScale = 1.0f;
  float fixedDeltaTime = 0.02f;
  sf::RenderTarget* renderTarget;

 private:
  GameManager() : renderTarget(nullptr) {}
  GameManager(const GameManager&) = delete;
  GameManager& operator=(const GameManager&) = delete;
};

#endif  // GAMEMANAGER_H
