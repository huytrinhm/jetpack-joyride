#include "Engine/GameObjectManager.h"

void GameObjectManager::AddGameObject(std::unique_ptr<GameObject> gameObject) {
  gameObjects.push_back(std::move(gameObject));
}

void GameObjectManager::Start() {
  for (const auto& gameObject : gameObjects) {
    gameObject->Start();
  }
}

void GameObjectManager::Update() {
  for (const auto& gameObject : gameObjects) {
    gameObject->Update();
  }
}
