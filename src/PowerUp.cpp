#include "PowerUp.h"

PowerUp::PowerUp(float x, float y) {
  shape.setSize({20.f, 20.f});
  shape.setFillColor(sf::Color::Blue);
  shape.setPosition(x, y);
}

void PowerUp::update(float deltaTime) {
  shape.move(-200.f * deltaTime, 0);
}

void PowerUp::draw(sf::RenderTarget& target) {
  target.draw(shape);
}

sf::Vector2f PowerUp::getPosition() const {
  return shape.getPosition();
}
