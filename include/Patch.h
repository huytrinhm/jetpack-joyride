#ifndef PATCH_H
#define PATCH_H

#include <SFML/Graphics.hpp>
#include "Engine/GameRenderer.h"

class Patch {
 public:
  Patch(const sf::Texture& texture, const sf::IntRect& rect, size_t layerIndex);
  const sf::Sprite& getSprite() const;
  size_t layerIndex;

 private:
  sf::Sprite sprite;
};

class ActivePatch {
 public:
  ActivePatch(const Patch& patchTemplate, float x, float y);
  void move(float dx);
  bool isOffScreen(float screenWidth) const;
  void Render(GameRenderer& renderer) const;

  sf::Sprite sprite;
  size_t layerIndex;
};

#endif  // PATCH_H
