#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include "Config.h"
#include "Engine/AssetManager.h"
#include "Engine/GameManager.h"
#include "Engine/GameObjectManager.h"
#include "Player.h"

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
  auto player = std::make_unique<Player>();
  gameObjectManager.AddGameObject(std::move(player));

  gameObjectManager.StartAll();

  // Main game loop
  sf::Clock clock;

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
    game.deltaTime = clock.restart().asSeconds();

    renderTexture.clear(sf::Color::Black);
    gameObjectManager.UpdateAll();
    renderTexture.display();

    window.clear();
    window.draw(renderSprite);
    window.display();
  }

  return 0;
}
