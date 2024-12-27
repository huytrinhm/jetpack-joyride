#ifndef MENU_H
#define MENU_H
#include <SFML/Graphics.hpp>

class Menu {
 public:
  Menu();
  void DisplayMenu(sf::RenderTexture& renderTarget);

 private:
  sf::Sprite background;
  sf::Sprite playButton;
  sf::Sprite quitButton;
};

#endif  // MENU_H