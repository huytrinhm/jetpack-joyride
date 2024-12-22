#include "Engine/GameObjectManager.h"

void GameObjectManager::AddGameObject(std::unique_ptr<GameObject> gameObject) {
  gameObjects.push_back(std::move(gameObject));
}

void GameObjectManager::StartAll() {
  for (const auto& gameObject : gameObjects) {
    gameObject->DoStart();
  }
}

void GameObjectManager::UpdateAll() {
  for (auto& gameObject : gameObjects) {
    gameObject->DoUpdate();
  }
}

void GameObjectManager::FixedUpdateAll() {
  for (auto& gameObject : gameObjects) {
    gameObject->DoFixedUpdate();
  }
}

void GameObjectManager::RenderAll(GameRenderer& renderer) {
  for (const auto& gameObject : gameObjects) {
    gameObject->Render(renderer);
  }
}
