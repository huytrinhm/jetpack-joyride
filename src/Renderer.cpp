#include "Renderer.h"

Renderer::Renderer(sf::Sprite& sprite) : sprite(sprite) {}

void Renderer::update(float deltaTime) {
  // No update logic needed for rendering
}

void Renderer::draw(sf::RenderTarget& target) {
  target.draw(sprite);
}
