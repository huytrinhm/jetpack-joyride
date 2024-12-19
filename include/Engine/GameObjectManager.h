#pragma once

#include <memory>
#include <vector>
#include "GameObject.h"

class GameObjectManager {
 private:
  std::vector<std::unique_ptr<GameObject>> gameObjects;

 public:
  void AddGameObject(std::unique_ptr<GameObject> gameObject);
  void Start();
  void Update();
};
