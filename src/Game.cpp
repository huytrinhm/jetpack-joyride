#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include "Animator.h"
#include "Player.h"

// Constants
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// World size constants
const int WORLD_WIDTH = 640;
const int WORLD_HEIGHT = 360;

void updateLetterbox(sf::RenderWindow& window,
                     sf::Sprite& renderSprite,
                     int windowWidth,
                     int windowHeight) {
  float scaleX = static_cast<float>(windowWidth) / WORLD_WIDTH;
  float scaleY = static_cast<float>(windowHeight) / WORLD_HEIGHT;
  float scale = std::min(scaleX, scaleY);
  float offsetX = (windowWidth - WORLD_WIDTH * scale) / 2;
  float offsetY = (windowHeight - WORLD_HEIGHT * scale) / 2;

  window.setView(sf::View(sf::FloatRect(0, 0, windowWidth, windowHeight)));

  renderSprite.setScale(scale, scale);
  renderSprite.setPosition(offsetX, offsetY);
};

int main() {
  srand(static_cast<unsigned>(time(0)));

  // Create window
  sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
                          "Jetpack Joyride Prototype");
  window.setFramerateLimit(60);

  // Create render texture
  sf::RenderTexture renderTexture;
  renderTexture.create(WORLD_WIDTH, WORLD_HEIGHT);
  sf::Sprite renderSprite(renderTexture.getTexture());

  updateLetterbox(window, renderSprite, WINDOW_WIDTH, WINDOW_HEIGHT);

  // Load player texture
  sf::Texture playerTexture;
  if (!playerTexture.loadFromFile("assets/barry.png")) {
    throw std::runtime_error("Failed to load player texture.");
  }

  // Create player
  Player player(WORLD_WIDTH / 4.f, WORLD_HEIGHT / 2.f, playerTexture,
                {sf::IntRect(0, 0, 32, 48), sf::IntRect(32, 0, 32, 48),
                 sf::IntRect(64, 0, 32, 48), sf::IntRect(96, 0, 32, 48)},
                0.1f);
  player.onCreate();

  // Main game loop
  sf::Clock clock;

  while (window.isOpen()) {
    // Event handling
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
      else if (event.type == sf::Event::Resized) {
        updateLetterbox(window, renderSprite, event.size.width,
                        event.size.height);
      }
    }

    // Update
    float deltaTime = clock.restart().asSeconds();

    player.handleInput(deltaTime);
    player.onUpdate(deltaTime);

    // Render to the render texture
    renderTexture.clear(sf::Color::Black);
    player.draw(renderTexture);

    renderTexture.display();

    window.clear();
    window.draw(renderSprite);
    window.display();
  }

  return 0;
}
