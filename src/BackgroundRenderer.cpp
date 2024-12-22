#include "BackgroundRenderer.h"
#include "Config.h"
#include "Engine/GameManager.h"

void BackgroundRenderer::Start() {
  transform.position = sf::Vector2f(0, -76);

  currentRoomIndex = 0;
  activePatches.emplace_back(rooms[currentRoomIndex].getStartPatch(), 0,
                             transform.position.y);
}

BackgroundRenderer::BackgroundRenderer(const std::string& name,
                                       const std::vector<Room>& rooms,
                                       float scrollSpeed)
    : GameObject(name) {
  this->rooms = rooms;
  this->scrollSpeed = scrollSpeed;
}

void BackgroundRenderer::Update() {
  float dx = -scrollSpeed * GameManager::Instance().deltaTime;

  // Move all active patches
  for (auto& patch : activePatches) {
    patch.move(dx);
  }

  // Remove patches that are off-screen
  while (!activePatches.empty() &&
         activePatches.front().isOffScreen(WORLD_WIDTH)) {
    activePatches.pop_front();
  }

  // Add new patches if necessary
  if (activePatches.empty() ||
      activePatches.back().sprite.getPosition().x +
              activePatches.back().sprite.getGlobalBounds().width <
          WORLD_WIDTH) {
    float newPatchX =
        activePatches.empty()
            ? WORLD_WIDTH
            : activePatches.back().sprite.getPosition().x +
                  activePatches.back().sprite.getGlobalBounds().width;
    if (currentRoomIndex < rooms.size()) {
      activePatches.emplace_back(rooms[currentRoomIndex].getRandomMainPatch(),
                                 transform.position.x + newPatchX,
                                 transform.position.y);
    } else {
      // Handle room transition
      activePatches.emplace_back(rooms[currentRoomIndex].getEndPatch(),
                                 transform.position.x + newPatchX,
                                 transform.position.y);
      currentRoomIndex = (currentRoomIndex + 1) % rooms.size();
      activePatches.emplace_back(
          rooms[currentRoomIndex].getStartPatch(),
          transform.position.x + newPatchX +
              activePatches.back().sprite.getGlobalBounds().width - 128,
          transform.position.y);
    }
  }
}

void BackgroundRenderer::Render(GameRenderer& renderer) {
  for (const auto& patch : activePatches) {
    patch.Render(renderer);
  }
}
