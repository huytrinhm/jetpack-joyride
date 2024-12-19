#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Module.h"

class Animator : public Module {
 public:
  Animator(sf::Sprite& sprite,
           const std::vector<sf::IntRect>& frames,
           float interval);

  void update(float deltaTime) override;

 private:
  sf::Sprite& sprite;
  std::vector<sf::IntRect> frames;
  float interval;
  float timer;
  size_t currentFrame;
};

#endif
