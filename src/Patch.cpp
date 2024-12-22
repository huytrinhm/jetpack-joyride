#include "Patch.h"

Patch::Patch(const sf::Texture& texture,
             const sf::IntRect& rect,
             size_t layerIndex)
    : layerIndex(layerIndex), sprite(texture, rect) {}

const sf::Sprite& Patch::getSprite() const {
  return sprite;
}

ActivePatch::ActivePatch(const Patch& patchTemplate, float x, float y) {
  sprite = patchTemplate.getSprite();
  layerIndex = patchTemplate.layerIndex;
  sprite.setPosition(x, y);
}

void ActivePatch::move(float dx) {
  sprite.move(dx, 0);
}

bool ActivePatch::isOffScreen(float screenWidth) const {
  return sprite.getPosition().x + sprite.getGlobalBounds().width < 0;
}

void ActivePatch::Render(GameRenderer& renderer) const {
  renderer.AddDrawable(layerIndex, &sprite);
}
