#ifndef BACKGROUNDRENDERER_H
#define BACKGROUNDRENDERER_H

#include <deque>
#include <vector>
#include "Engine/GameObject.h"
#include "Engine/GameRenderer.h"
#include "Patch.h"
#include "Room.h"

class BackgroundRenderer : public GameObject {
 public:
  BackgroundRenderer(const std::string& name, const std::vector<Room>& rooms);
  void Start() override;
  void Update() override;
  void Render(GameRenderer& renderer) override;

 private:
  std::deque<ActivePatch> activePatches;
  std::vector<Room> rooms;
  size_t currentRoomIndex;
  float currentLength;
};

#endif  // BACKGROUNDRENDERER_H
