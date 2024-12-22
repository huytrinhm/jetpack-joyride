#include "Room.h"
#include <random>
#include "AssetManager.h"

Room::Room(const std::string& atlasName,
           const sf::IntRect& startRect,
           const sf::IntRect& endRect,
           const std::vector<std::pair<sf::IntRect, float>>& mainRects)
    : startPatch(AssetManager::Instance().GetTexture(atlasName), startRect),
      endPatch(AssetManager::Instance().GetTexture(atlasName), endRect) {
  for (const auto& rect : mainRects) {
    mainPatches.emplace_back(AssetManager::Instance().GetTexture(atlasName),
                             rect.first);
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
