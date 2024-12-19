#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SFML/Graphics.hpp>

const sf::Vector2f OBSTACLE_SIZE(30.f, 30.f);

class Obstacle {
 public:
  Obstacle(float x, float y);

  void update(float deltaTime);
  void draw(sf::RenderTarget& target);
  sf::Vector2f getPosition() const;

 private:
  sf::RectangleShape shape;
};

#endif
