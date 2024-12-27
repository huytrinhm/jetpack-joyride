#include <SFML/Graphics.hpp>
#include "AssetManager.h"
#include "Config.h"
#include "Engine/InputManager.h"
#include "GameManager.h"
#include "Utilities.h"

int main() {
  sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Jetpack Joyride",
                          sf::Style::Fullscreen);
  window.setVerticalSyncEnabled(true);
  window.setFramerateLimit(60);

  sf::RenderTexture renderTexture;
  renderTexture.create(WORLD_WIDTH, WORLD_HEIGHT);
  sf::Sprite renderSprite(renderTexture.getTexture());

  updateLetterbox(window, renderSprite);

  AssetManager::Instance().Initialize();

  GameManager& game = GameManager::Instance();
  game.renderTarget = &renderTexture;

  game.InitGame();

  while (window.isOpen() && game.gameState != GameState::QUIT) {
    if (game.gameState == GameState::GAME_OVER) {
      game.EndGame();
      game.InitGame();
    }

    // Event handling
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
      else if (event.type == sf::Event::Resized) {
        updateLetterbox(window, renderSprite);
      }
    }

    InputManager::Instance().Update(window);

    game.MainLoop();

    window.clear();
    window.draw(renderSprite);
    window.display();
  }

  game.EndGame();
  window.close();
  return 0;
}
