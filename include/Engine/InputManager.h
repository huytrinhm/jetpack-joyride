#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SFML/Graphics.hpp>

class InputManager {
 public:
  static InputManager& Instance() {
    static InputManager instance;
    return instance;
  }

  void Update(sf::RenderWindow& window) {
    // Reset events
    keyPressedEvents.clear();
    keyReleasedEvents.clear();
    isLeftClick = false;
    isRightClick = false;

    sf::Event event;
    while (window.pollEvent(event)) {
      switch (event.type) {
        case sf::Event::KeyPressed:
          keyPressedEvents[event.key.code] = true;
          break;
        case sf::Event::KeyReleased:
          keyReleasedEvents[event.key.code] = true;
          break;
        case sf::Event::MouseButtonPressed:
          if (event.mouseButton.button == sf::Mouse::Left) {
            isLeftClick = true;
          } else if (event.mouseButton.button == sf::Mouse::Right) {
            isRightClick = true;
          }
          break;
        default:
          break;
      }
    }

    for (auto& key : keys)
      key.second = sf::Keyboard::isKeyPressed(key.first);
  }

  bool IsKeyPressed(sf::Keyboard::Key key) {
    if (keyPressedEvents.find(key) == keyPressedEvents.end()) {
      return false;
    }
    return keyPressedEvents[key];
  }

  bool IsKeyReleased(sf::Keyboard::Key key) {
    if (keyReleasedEvents.find(key) == keyReleasedEvents.end()) {
      return false;
    }
  }

  bool IsKeyDown(sf::Keyboard::Key key) {
    if (keys.find(key) == keys.end()) {
      return false;
    }
    return keys[key];
  }

  bool isLeftClick;
  bool isRightClick;

 private:
  InputManager() { keys.insert({sf::Keyboard::Space, false}); }
  std::unordered_map<sf::Keyboard::Key, bool> keys;
  std::unordered_map<sf::Keyboard::Key, bool> keyPressedEvents;
  std::unordered_map<sf::Keyboard::Key, bool> keyReleasedEvents;
};

#endif  // INPUTMANAGER_H