#include "Transform.h"

Transform::Transform(sf::Sprite& sprite, float x, float y)
    : sprite(sprite), position(x, y) {
  sprite.setPosition(position);
}

void Transform::move(float dx, float dy) {
  position.x += dx;
  position.y += dy;
  sprite.setPosition(position);
}

sf::Vector2f Transform::getPosition() const {
  return position;
}

void Transform::update(float deltaTime) {
  // No update logic for now
}
