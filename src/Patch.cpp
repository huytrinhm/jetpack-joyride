#include "Patch.h"

Patch::Patch(const sf::Texture& texture, const sf::IntRect& rect) {
  sprite.setTexture(texture);
  sprite.setTextureRect(rect);
}

const sf::Sprite& Patch::getSprite() const {
  return sprite;
}

ActivePatch::ActivePatch(const Patch& patchTemplate, float x, float y) {
  sprite = patchTemplate.getSprite();
  sprite.setPosition(x, y);
}

void ActivePatch::move(float dx) {
  sprite.move(dx, 0);
}

bool ActivePatch::isOffScreen(float screenWidth) const {
  return sprite.getPosition().x + sprite.getGlobalBounds().width < 0;
}

void ActivePatch::Render(sf::RenderTarget& target) const {
  target.draw(sprite);
}