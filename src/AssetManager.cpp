#include "AssetManager.h"
#include <iostream>

void AssetManager::LoadTexture(const std::string& name,
                               const std::string& filename) {
  sf::Texture texture;
  if (texture.loadFromFile(filename)) {
    textures[name] = texture;
  }
}

void AssetManager::Initialize() {
  LoadTexture("barry", "assets/barry.png");
}

sf::Texture& AssetManager::GetTexture(const std::string& name) {
  try {
    return textures.at(name);
  } catch (const std::out_of_range& e) {
    std::cerr << "Texture not found: " << name << std::endl;
    throw;
  }
}
