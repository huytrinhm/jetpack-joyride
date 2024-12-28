#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Engine/GameObjectManager.h"
#include "Player.h"
#include "Room.h"
#include "box2d/box2d.h"

enum class GameState { MENU, PLAYING, GAME_OVER, QUIT };

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
  sf::RenderTexture* renderTarget;
  b2WorldId worldId;
  b2BodyId playerPivotId;
  b2BodyId groundId;
  b2BodyId ceilingId;
  GameState gameState = GameState::PLAYING;
  Player* player;

  void InitGame();
  void MainLoop();
  void EndGame();
  void GameOver();

  void AddVehicle(std::string name, std::unique_ptr<Vehicle>&& vehicle);
  Vehicle* GetVehicle(const std::string& name);

 private:
  GameManager();
  GameManager(const GameManager&) = delete;
  GameManager& operator=(const GameManager&) = delete;

  std::unique_ptr<GameObjectManager> gameObjectManager;
  std::unique_ptr<GameRenderer> gameRenderer;
  std::vector<Room> rooms;
  std::unordered_map<std::string, std::unique_ptr<Vehicle>> vehicles;

  sf::Clock clock;
  float accumulatedTime;
  sf::Text distanceText;
  float distanceTravelled;
};

#endif  // GAMEMANAGER_H
