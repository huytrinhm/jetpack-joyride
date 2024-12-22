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
  LoadTexture("bgHallway0", "assets/bgHallway0.png");
  LoadTexture("bgLab0", "assets/bgLab0.png");
  LoadTexture("bgGlassTube0", "assets/bgGlassTube0.png");
  LoadTexture("bgStart", "assets/bgStart.png");
}

sf::Texture& AssetManager::GetTexture(const std::string& name) {
  try {
    return textures.at(name);
  } catch (const std::out_of_range& e) {
    std::cerr << "Texture not found: " << name << std::endl;
    throw;
  }
}
