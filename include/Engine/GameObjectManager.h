#ifndef GAMEOBJECTMANAGER_H
#define GAMEOBJECTMANAGER_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "GameObject.h"

class GameObjectManager {
 private:
  std::vector<std::unique_ptr<GameObject>> gameObjects;

 public:
  void AddGameObject(std::unique_ptr<GameObject> gameObject);
  void StartAll();
  void UpdateAll();
  void FixedUpdateAll();
  void RenderAll(sf::RenderTarget& target);
};

#endif  // GAMEOBJECTMANAGER_H
