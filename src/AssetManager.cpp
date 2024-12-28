#include "AssetManager.h"
#include <iostream>

void AssetManager::LoadTexture(const std::string& name,
                               const std::string& filename) {
  sf::Texture texture;
  if (texture.loadFromFile(filename)) {
    textures[name] = texture;
  }
}

void AssetManager::LoadFont(const std::string& name,
                            const std::string& filename) {
  sf::Font font;
  if (font.loadFromFile(filename)) {
    fonts[name] = font;
  } else {
    std::cerr << "Failed to load font: " << filename << std::endl;
  }
}

void AssetManager::Initialize() {
  LoadTexture("barry", "assets/barry.png");
  LoadTexture("bgHallway0", "assets/bgHallway0.png");
  LoadTexture("bgLab0", "assets/bgLab0.png");
  LoadTexture("bgGlassTube0", "assets/bgGlassTube0.png");
  LoadTexture("bgStart", "assets/bgStart.png");
  LoadTexture("bullet", "assets/bullet.png");
  LoadTexture("zapperHead", "assets/zapperHead.png");
  LoadTexture("zapperEffect", "assets/zapEffects.png");
  LoadTexture("shield", "assets/shield.png");
  LoadTexture("shieldField", "assets/shieldField.png");
  LoadTexture("rocket", "assets/rocket.png");
  LoadTexture("rocketAlert", "assets/rocketAlert.png");
  LoadTexture("menuBackground", "assets/menuBackground.png");
  LoadTexture("menuButtons", "assets/menuButtons.png");

  LoadFont("Jetpackia", "assets/Jetpackia.ttf");
}

sf::Texture& AssetManager::GetTexture(const std::string& name) {
  try {
    return textures.at(name);
  } catch (const std::out_of_range& e) {
    std::cerr << "Texture not found: " << name << std::endl;
    throw;
  }
}

sf::Font& AssetManager::GetFont(const std::string& name) {
  try {
    return fonts.at(name);
  } catch (const std::out_of_range& e) {
    std::cerr << "Font not found: " << name << std::endl;
    throw;
  }
}
