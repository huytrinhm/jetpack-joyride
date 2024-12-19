#ifndef RENDERER_H
#define RENDERER_H

#include <SFML/Graphics.hpp>
#include "Module.h"

class Renderer : public Module {
 public:
  Renderer(sf::Sprite& sprite);

  void update(float deltaTime) override;
  void draw(sf::RenderTarget& target);

 private:
  sf::Sprite& sprite;
};

#endif
