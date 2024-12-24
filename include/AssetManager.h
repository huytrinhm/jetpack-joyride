#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class AssetManager {
 public:
  static AssetManager& Instance() {
    static AssetManager instance;
    return instance;
  }

  sf::Texture& GetTexture(const std::string& name);
  sf::Font& GetFont(const std::string& name);
  void Initialize();

 private:
  AssetManager() = default;
  AssetManager(const AssetManager&) = delete;
  AssetManager& operator=(const AssetManager&) = delete;
  void LoadTexture(const std::string& name, const std::string& filename);
  void LoadFont(const std::string& name, const std::string& filename);

  std::map<std::string, sf::Texture> textures;
  std::map<std::string, sf::Font> fonts;
};

#endif  // ASSETMANAGER_H
