#include "GameManager.h"
#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include "AssetManager.h"
#include "BackgroundRenderer.h"
#include "Config.h"
#include "Engine/GameObjectManager.h"
#include "Engine/GameRenderer.h"
#include "Engine/InputManager.h"
#include "Player.h"
#include "PowerUp.h"
#include "Rocket.h"
#include "RocketSpawner.h"
#include "Room.h"
#include "RoomSpawner.h"
#include "SoundManager.h"
#include "b2DrawSFML.h"

GameManager::GameManager() {
  // Initialize rooms
  rooms.emplace_back("bgStart", 128 * 4, sf::IntRect(0, 0, 4 * 128, 512),
                     sf::IntRect(4 * 128, 0, 128, 512),
                     std::vector<std::pair<sf::IntRect, float>>{});

  rooms.emplace_back("bgHallway0", 128 * 20, sf::IntRect(0, 0, 3 * 128, 512),
                     sf::IntRect(3 * 128, 0, 128, 512),
                     std::vector<std::pair<sf::IntRect, float>>{
                         {sf::IntRect(4 * 128, 0, 128, 512), 0.4f},
                         {sf::IntRect(5 * 128, 0, 128, 512), 0.4f},
                         {sf::IntRect(6 * 128, 0, 128, 512), 0.1f},
                         {sf::IntRect(7 * 128, 0, 128, 512), 0.1f}});

  rooms.emplace_back("bgLab0", 128 * 20, sf::IntRect(0, 0, 128 * 2, 512),
                     sf::IntRect(3 * 128, 0, 128, 512),
                     std::vector<std::pair<sf::IntRect, float>>{
                         {sf::IntRect(2 * 128, 0, 128, 512), 0.5f},
                         {sf::IntRect(4 * 128, 0, 4 * 128, 512), 0.5f}});
}

void GameManager::InitGame() {
  srand(static_cast<unsigned>(time(0)));
  gameObjectManager = std::make_unique<GameObjectManager>();
  gameRenderer = std::make_unique<GameRenderer>(10);
  // layer 0-2: background
  // layer 3-5: backEffects
  // layer 6: player
  // layer 7-9: frontEffects

  auto backgroundRenderer =
      std::make_unique<BackgroundRenderer>("BackgroundRenderer", rooms);
  gameObjectManager->AddGameObject(std::move(backgroundRenderer));

  // Initialize box2d
  DebugDraw::debugDraw.context = renderTarget;
  b2WorldDef worldDef = b2DefaultWorldDef();
  worldDef.gravity = (b2Vec2){0.0f, 10.0f};
  worldId = b2CreateWorld(&worldDef);

  b2BodyDef bodyDef = b2DefaultBodyDef();
  bodyDef.position = pixelToMeter({WORLD_WIDTH / 2.f, WORLD_HEIGHT - 44.f});
  groundId = b2CreateBody(worldId, &bodyDef);

  b2ShapeDef shapeDef = b2DefaultShapeDef();
  shapeDef.friction = 0.0f;
  b2Segment segment = {{-WORLD_WIDTH / 2.f, 0}, {WORLD_WIDTH / 2.f, 0}};
  b2CreateSegmentShape(groundId, &shapeDef, &segment);

  bodyDef.position = pixelToMeter({WORLD_WIDTH / 2.f, 44.f});
  ceilingId = b2CreateBody(worldId, &bodyDef);
  b2CreateSegmentShape(ceilingId, &shapeDef, &segment);

  bodyDef.position = pixelToMeter({150, 0});
  playerPivotId = b2CreateBody(worldId, &bodyDef);

  // Initialize player
  vehicles.clear();
  AddVehicle("jetpack", std::make_unique<Jetpack>());
  AddVehicle("gravitySuit", std::make_unique<GravitySuit>());
  AddVehicle("stomper", std::make_unique<Stomper>());

  auto player = std::make_unique<Player>(GetVehicle("jetpack"));
  this->player = player.get();
  gameObjectManager->AddGameObject(std::move(player));

  auto roomSpawner = std::make_unique<RoomSpawner>();
  gameObjectManager->AddGameObject(std::move(roomSpawner));

  auto pickupSpawner = std::make_unique<PickupSpawner>();
  gameObjectManager->AddGameObject(std::move(pickupSpawner));

  auto rocketSpawner = std::make_unique<RocketSpawner>();
  gameObjectManager->AddGameObject(std::move(rocketSpawner));

  gameObjectManager->StartAll();

  SoundManager::Instance().PlayMusic("gameplayMusic");

  clock = sf::Clock();
  accumulatedTime = 0.0f;
  gameState = GameState::PLAYING;
}

void GameManager::MainLoop() {
  // Update
  unscaledDeltaTime = clock.restart().asSeconds();
  deltaTime = unscaledDeltaTime * timeScale;
  accumulatedTime += deltaTime;

  // std::cerr << "FPS: " << 1.0f / game.deltaTime << std::endl;

  while (accumulatedTime >= fixedDeltaTime) {
    b2World_Step(worldId, fixedDeltaTime, 4);
    gameObjectManager->FixedUpdateAll();
    accumulatedTime -= fixedDeltaTime;
  }
  gameObjectManager->UpdateAll();

  // Render
  renderTarget->clear(sf::Color::Black);
  gameObjectManager->RenderAll(*gameRenderer);
  gameRenderer->Render(*renderTarget);
  b2World_Draw(worldId, &DebugDraw::debugDraw);
  renderTarget->display();
}

void GameManager::EndGame() {
  b2DestroyWorld(worldId);
}

void GameManager::GameOver() {
  gameState = GameState::GAME_OVER;
  SoundManager::Instance().PlaySound("gameOverSound");
  std::cerr << "Game Over" << std::endl;
}

void GameManager::AddVehicle(std::string name,
                             std::unique_ptr<Vehicle>&& vehicle) {
  vehicles[name] = std::move(vehicle);
}

Vehicle* GameManager::GetVehicle(const std::string& name) {
  return vehicles[name].get();
}
