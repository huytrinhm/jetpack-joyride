#pragma once
#include <SFML/Audio.hpp>
#include <map>
#include <memory>
#include <string>

class SoundManager {
 public:
  static SoundManager& Instance();
  void LoadSound(const std::string& name, const std::string& filename);
  void LoadMusic(const std::string& name, const std::string& filename);
  void PlaySound(const std::string& name, bool restart = false);
  void StopSound(const std::string& name);
  void PlayMusic(const std::string& name, bool loop = true);
  void StopMusic();

 private:
  SoundManager() = default;
  std::map<std::string, sf::SoundBuffer> soundBuffers;
  std::map<std::string, sf::Sound> sounds;
  std::map<std::string, std::unique_ptr<sf::Music>> musics;
  sf::Music* currentMusic = nullptr;
};
