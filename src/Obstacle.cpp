#include "Obstacle.h"

Obstacle::Obstacle(float x, float y) {
  shape.setSize({30.f, 30.f});
  shape.setFillColor(sf::Color::Red);
  shape.setPosition(x, y);
}

void Obstacle::update(float deltaTime) {
  shape.move(-200.f * deltaTime, 0);
}

void Obstacle::draw(sf::RenderTarget& target) {
  target.draw(shape);
}

sf::Vector2f Obstacle::getPosition() const {
  return shape.getPosition();
}
