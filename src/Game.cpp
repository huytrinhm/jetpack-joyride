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
#include "Engine/GameManager.h"
#include "Engine/GameObjectManager.h"
#include "Engine/GameRenderer.h"
#include "Player.h"
#include "Room.h"
#include "b2DrawSFML.h"

void updateLetterbox(sf::RenderWindow& window, sf::Sprite& renderSprite) {
  float windowWidth = static_cast<float>(window.getSize().x);
  float windowHeight = static_cast<float>(window.getSize().y);
  float scaleX = windowWidth / WORLD_WIDTH;
  float scaleY = windowHeight / WORLD_HEIGHT;
  float scale = std::min(scaleX, scaleY);
  float offsetX = (windowWidth - WORLD_WIDTH * scale) / 2;
  float offsetY = (windowHeight - WORLD_HEIGHT * scale) / 2;

  window.setView(sf::View(sf::FloatRect(0, 0, windowWidth, windowHeight)));

  renderSprite.setScale(scale, scale);
  renderSprite.setPosition(offsetX, offsetY);
};

int main() {
  srand(static_cast<unsigned>(time(0)));

  // Create window in fullscreen mode
  sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Jetpack Joyride",
                          sf::Style::Fullscreen);
  window.setVerticalSyncEnabled(true);
  window.setFramerateLimit(60);

  // Create render texture
  sf::RenderTexture renderTexture;
  renderTexture.create(WORLD_WIDTH, WORLD_HEIGHT);
  sf::Sprite renderSprite(renderTexture.getTexture());

  updateLetterbox(window, renderSprite);

  AssetManager::Instance().Initialize();

  GameManager& game = GameManager::Instance();
  game.renderTarget = &renderTexture;

  GameObjectManager gameObjectManager;

  GameRenderer gameRenderer(3);

  // Initialize rooms
  std::vector<Room> rooms;

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

  auto backgroundRenderer =
      std::make_unique<BackgroundRenderer>("BackgroundRenderer", rooms, 200.0f);
  gameObjectManager.AddGameObject(std::move(backgroundRenderer));

  // Initialize box2d
  DebugDraw::debugDraw.context = &renderTexture;
  b2WorldDef worldDef = b2DefaultWorldDef();
  worldDef.gravity = (b2Vec2){0.0f, 9.8f};
  game.worldId = b2CreateWorld(&worldDef);

  b2BodyDef groundBodyDef = b2DefaultBodyDef();
  groundBodyDef.position =
      pixelToMeter({WORLD_WIDTH / 2.f, WORLD_HEIGHT - 22.f});
  b2BodyId groundId = b2CreateBody(game.worldId, &groundBodyDef);

  b2Polygon groundBox =
      b2MakeBox(pixelToMeter(WORLD_WIDTH / 2.f), pixelToMeter(22.f));
  b2ShapeDef groundShapeDef = b2DefaultShapeDef();
  b2CreatePolygonShape(groundId, &groundShapeDef, &groundBox);

  // Initialize player
  std::vector<std::shared_ptr<Vehicle>> vehicles;
  vehicles.push_back(std::make_shared<Jetpack>());

  auto player = std::make_unique<Player>("Player", vehicles[0].get());
  gameObjectManager.AddGameObject(std::move(player));

  gameObjectManager.StartAll();

  // Main game loop
  sf::Clock clock;
  float accumulatedTime = 0.0f;

  while (window.isOpen()) {
    // Event handling
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
      else if (event.type == sf::Event::Resized) {
        updateLetterbox(window, renderSprite);
      }
    }

    // Update
    InputManager::Instance().Update(window);

    game.unscaledDeltaTime = clock.restart().asSeconds();
    game.deltaTime = game.unscaledDeltaTime * game.timeScale;
    accumulatedTime += game.deltaTime;

    // std::cerr << "FPS: " << 1.0f / game.deltaTime << std::endl;

    while (accumulatedTime >= game.fixedDeltaTime) {
      b2World_Step(game.worldId, game.fixedDeltaTime, 4);
      gameObjectManager.FixedUpdateAll();
      accumulatedTime -= game.fixedDeltaTime;
    }

    gameObjectManager.UpdateAll();

    // Render
    renderTexture.clear(sf::Color::Black);
    gameObjectManager.RenderAll(gameRenderer);
    gameRenderer.Render(renderTexture);
    b2World_Draw(game.worldId, &DebugDraw::debugDraw);
    renderTexture.display();

    window.clear();
    window.draw(renderSprite);
    window.display();
  }

  b2DestroyWorld(game.worldId);

  return 0;
}
