#ifndef POWERUP_H
#define POWERUP_H

#include <SFML/Graphics.hpp>

const sf::Vector2f POWERUP_SIZE(20.f, 20.f);

class PowerUp {
 public:
  PowerUp(float x, float y);

  void update(float deltaTime);
  void draw(sf::RenderTarget& target);
  sf::Vector2f getPosition() const;

 private:
  sf::RectangleShape shape;
};

#endif
