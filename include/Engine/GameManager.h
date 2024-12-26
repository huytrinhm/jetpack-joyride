#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "box2d/box2d.h"

enum class GameState { MENU, PLAYING, GAME_OVER };

class GameManager {
 public:
  static GameManager& Instance() {
    static GameManager instance;
    return instance;
  }

  float currentTime;
  float deltaTime;
  float unscaledDeltaTime;
  float timeScale = 1.0f;
  float fixedDeltaTime = 1 / 60.f;
  float scrollSpeed = 200.0f;
  sf::RenderTarget* renderTarget;
  b2WorldId worldId;
  b2BodyId playerPivotId;
  b2BodyId groundId;
  GameState gameState = GameState::PLAYING;

  void InitGame() {}
  void EndGame() { b2DestroyWorld(this->worldId); }
  void GameOver() {
    std::cout << "GameOver" << std::endl;
    gameState = GameState::GAME_OVER;
  }

 private:
  GameManager() : renderTarget(nullptr) {}
  GameManager(const GameManager&) = delete;
  GameManager& operator=(const GameManager&) = delete;
};

#endif  // GAMEMANAGER_H
