#include "Menu.h"
#include "AssetManager.h"
#include "Config.h"
#include "GameManager.h"

Menu::Menu() {
  auto& assetManager = AssetManager::Instance();
  background.setTexture(assetManager.GetTexture("menuBackground"));
  background.setPosition(0, 0);

  playButton.setTexture(assetManager.GetTexture("playButton"));
  playButton.setPosition(100, 100);

  quitButton.setTexture(assetManager.GetTexture("quitButton"));
  quitButton.setPosition(100, 200);
}

void Menu::DisplayMenu(sf::RenderTexture& renderTarget) {
  GameManager& game = GameManager::Instance();

  renderTarget.clear(sf::Color::Black);
  renderTarget.draw(background);
  renderTarget.draw(playButton);
  renderTarget.draw(quitButton);
  renderTarget.display();
}
