#ifndef PATCH_H
#define PATCH_H

#include <SFML/Graphics.hpp>

class Patch {
 public:
  Patch(const sf::Texture& texture, const sf::IntRect& rect);
  const sf::Sprite& getSprite() const;

 private:
  sf::Sprite sprite;
};

class ActivePatch {
 public:
  ActivePatch(const Patch& patchTemplate, float x, float y);
  void move(float dx);
  bool isOffScreen(float screenWidth) const;
  void Render(sf::RenderTarget& target) const;

  sf::Sprite sprite;
};

#endif  // PATCH_H
