#include "Engine/GameRenderer.h"

GameRenderer::GameRenderer(size_t layersCount) {
  layers.resize(layersCount);
}

void GameRenderer::AddDrawable(size_t layer, const sf::Drawable* drawable) {
  if (layer < layers.size()) {
    layers[layer].push_back(drawable);
  } else {
    throw std::out_of_range("Layer index out of range");
  }
}

void GameRenderer::Render(sf::RenderTarget& target) {
  for (const auto& layer : layers) {
    for (const auto& drawable : layer) {
      target.draw(*drawable);
    }
  }
  // Clear layers after rendering
  for (auto& layer : layers) {
    layer.clear();
  }
}
