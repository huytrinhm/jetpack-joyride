#include "Room.h"
#include <random>
#include "AssetManager.h"

Room::Room(const std::string& atlasName,
           float roomLength,
           const sf::IntRect& startRect,
           const sf::IntRect& endRect,
           const std::vector<std::pair<sf::IntRect, float>>& mainRects)
    : roomLength(roomLength),
      startPatch(AssetManager::Instance().GetTexture(atlasName), startRect, 1),
      endPatch(AssetManager::Instance().GetTexture(atlasName), endRect, 2) {
  for (const auto& rect : mainRects) {
    mainPatches.emplace_back(AssetManager::Instance().GetTexture(atlasName),
                             rect.first, 1);
    probabilities.push_back(rect.second);
  }
}

const Patch& Room::getStartPatch() const {
  return startPatch;
}

const Patch& Room::getEndPatch() const {
  return endPatch;
}

const Patch& Room::getRandomMainPatch() const {
  static std::default_random_engine engine{std::random_device{}()};
  std::discrete_distribution<size_t> dist(probabilities.begin(),
                                          probabilities.end());
  return mainPatches[dist(engine)];
}
