#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <SFML/System/Vector2.hpp>
#include "Component.h"

class Transform : public Component {
 public:
  sf::Vector2f position;
  sf::Vector2f rotation;
  sf::Vector2f scale;

  Transform();
};

#endif  // TRANSFORM_H
