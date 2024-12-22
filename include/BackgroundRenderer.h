#ifndef BACKGROUNDRENDERER_H
#define BACKGROUNDRENDERER_H

#include <deque>
#include <vector>
#include "Engine/GameObject.h"
#include "Patch.h"
#include "Room.h"

class BackgroundRenderer : public GameObject {
 public:
  BackgroundRenderer(const std::string& name,
                     const std::vector<Room>& rooms,
                     float scrollSpeed);
  void Start() override;
  void Update() override;
  void Render(sf::RenderTarget& target) override;

 private:
  std::deque<ActivePatch> activePatches;
  std::vector<Room> rooms;
  float scrollSpeed;
  size_t currentRoomIndex;
};

#endif  // BACKGROUNDRENDERER_H
