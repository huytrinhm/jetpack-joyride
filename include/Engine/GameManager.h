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
  sf::RenderTarget* renderTarget;

 private:
  GameManager() : renderTarget(nullptr) {}
  GameManager(const GameManager&) = delete;
  GameManager& operator=(const GameManager&) = delete;
};

#endif  // GAMEMANAGER_H
