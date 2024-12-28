#include "SoundManager.h"
#include <iostream>

SoundManager& SoundManager::Instance() {
  static SoundManager instance;
  return instance;
}

void SoundManager::LoadSound(const std::string& name,
                             const std::string& filename) {
  sf::SoundBuffer buffer;
  if (buffer.loadFromFile(filename)) {
    soundBuffers[name] = buffer;
    sounds[name].setBuffer(soundBuffers[name]);
  } else {
    std::cerr << "Failed to load sound: " << filename << std::endl;
  }
}

void SoundManager::LoadMusic(const std::string& name,
                             const std::string& filename) {
  auto music = std::make_unique<sf::Music>();
  if (music->openFromFile(filename)) {
    musics[name] = std::move(music);
  } else {
    std::cerr << "Failed to load music: " << filename << std::endl;
  }
}

void SoundManager::PlaySound(const std::string& name, bool restart) {
  try {
    auto currentSound = &sounds.at(name);
    if (restart || currentSound->getStatus() == sf::Sound::Stopped) {
      currentSound->play();
    }
  } catch (const std::out_of_range& e) {
    std::cerr << "Sound not found: " << name << std::endl;
  }
}

void SoundManager::StopSound(const std::string& name) {
  try {
    auto currentSound = &sounds.at(name);
    if (currentSound->getStatus() == sf::Sound::Playing) {
      currentSound->stop();
    }
  } catch (const std::out_of_range& e) {
    std::cerr << "Sound not found: " << name << std::endl;
  }
}

void SoundManager::PlayMusic(const std::string& name, bool loop) {
  try {
    if (currentMusic) {
      currentMusic->stop();
    }
    currentMusic = musics.at(name).get();
    currentMusic->setLoop(loop);
    currentMusic->play();
  } catch (const std::out_of_range& e) {
    std::cerr << "Music not found: " << name << std::endl;
  }
}

void SoundManager::StopMusic() {
  if (currentMusic) {
    currentMusic->stop();
  }
}
