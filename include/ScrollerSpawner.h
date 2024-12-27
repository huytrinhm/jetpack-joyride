#ifndef SCROLLER_SPAWNER_H
#define SCROLLER_SPAWNER_H

#include <deque>
#include "Engine/GameObject.h"
#include "Zapper.h"

class ScrollerSpawner : public GameObject {
 public:
  ScrollerSpawner(const std::string& name);
  // void Start() override;
  void Update() override;
  void FixedUpdate() override;
  void Render(GameRenderer& renderer) override;

 private:
  float scrollerDistance;
  float spawnDistance;
  std::deque<Zapper> zappers;
  void SpawnRandomZapper();
  void RemovePassedZappers();
};

#endif  // SCROLLER_SPAWNER_H