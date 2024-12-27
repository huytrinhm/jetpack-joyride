#ifndef SCROLLER_SPAWNER_H
#define SCROLLER_SPAWNER_H

#include <deque>
#include <memory>
#include "Engine/GameObject.h"

class ScrollerSpawner : public GameObject {
 public:
  ScrollerSpawner(float spawnDistance, float variance = 0);
  void Update() override;
  void FixedUpdate() override;
  void Render(GameRenderer& renderer) override;

 protected:
  float scrollerDistance;
  float spawnDistance;
  float variance;
  std::deque<std::unique_ptr<GameObject>> objects;
  virtual void Spawn() = 0;
  virtual void Cleanup();
};

#endif  // SCROLLER_SPAWNER_H