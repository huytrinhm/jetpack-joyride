#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class GameRenderer {
 public:
  GameRenderer(size_t layersCount);

  void AddDrawable(size_t layer, const sf::Drawable* drawable);
  void Render(sf::RenderTarget& target);

 private:
  std::vector<std::vector<const sf::Drawable*>> layers;
};
