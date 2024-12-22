#ifndef ROOM_H
#define ROOM_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Patch.h"

class Room {
 public:
  Room(const std::string& atlasName,
       const sf::IntRect& startRect,
       const sf::IntRect& endRect,
       const std::vector<std::pair<sf::IntRect, float>>& mainRects);
  const Patch& getStartPatch() const;
  const Patch& getEndPatch() const;
  const Patch& getRandomMainPatch() const;

 private:
  Patch startPatch;
  Patch endPatch;
  std::vector<Patch> mainPatches;
  std::vector<float> probabilities;
};

#endif  // ROOM_H
