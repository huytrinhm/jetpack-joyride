#include "Menu.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "AssetManager.h"
#include "Config.h"
#include "GameManager.h"

Menu::Menu() {
  auto& assetManager = AssetManager::Instance();
  background.setTexture(assetManager.GetTexture("menuBackground"));
  background.setPosition(0, 0);

  playButton.setTexture(assetManager.GetTexture("menuButtons"));
  playButton.setTextureRect(sf::IntRect(0, 0, 160, 64));
  playButton.setPosition(277, 110);

  quitButton.setTexture(assetManager.GetTexture("menuButtons"));
  quitButton.setTextureRect(sf::IntRect(0, 64, 160, 64));
  quitButton.setPosition(277, 190);
}

void Menu::DisplayMenu(sf::RenderTexture& renderTarget,
                       const sf::FloatRect& renderBounds) {
  GameManager& game = GameManager::Instance();

  sf::Vector2f mousePosition =
      renderTarget.mapPixelToCoords(sf::Mouse::getPosition());

  // Map global coords to render target coords
  mousePosition.x =
      (mousePosition.x - renderBounds.left) / renderBounds.width * WORLD_WIDTH;
  mousePosition.y =
      (mousePosition.y - renderBounds.top) / renderBounds.height * WORLD_HEIGHT;

  // Hover
  if (playButton.getGlobalBounds().contains(mousePosition)) {
    playButton.setTextureRect(sf::IntRect(160, 0, 160, 64));

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      game.InitGame();
      game.gameState = GameState::PLAYING;
    }
  } else {
    playButton.setTextureRect(sf::IntRect(0, 0, 160, 64));
  }

  if (quitButton.getGlobalBounds().contains(mousePosition)) {
    quitButton.setTextureRect(sf::IntRect(160, 64, 160, 64));

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      game.gameState = GameState::QUIT;
    }
  } else {
    quitButton.setTextureRect(sf::IntRect(0, 64, 160, 64));
  }

  renderTarget.clear(sf::Color::Black);
  renderTarget.draw(background);
  renderTarget.draw(playButton);
  renderTarget.draw(quitButton);
  renderTarget.display();
}
