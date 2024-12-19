#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <SFML/Graphics.hpp>
#include "Module.h"

class Transform : public Module {
 public:
  Transform(sf::Sprite& sprite, float x, float y);
  void move(float dx, float dy);
  sf::Vector2f getPosition() const;
  void update(float deltaTime) override;

 private:
  sf::Sprite& sprite;
  sf::Vector2f position;
};

#endif
