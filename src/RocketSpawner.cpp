#include "RocketSpawner.h"
#include "Rocket.h"
#include "Utilities.h"

RocketSpawner::RocketSpawner() : ScrollerSpawner(1600, 300) {}

void RocketSpawner::Spawn() {
  int rng = randomIntInRange(0, 4);
  if (rng != 0)
    objects.emplace_back(std::make_unique<Rocket>());
  else {
    objects.emplace_back(std::make_unique<Rocket>(0.0f, 0.5f));
    objects.emplace_back(std::make_unique<Rocket>(0.5f, 0.5f));
    objects.emplace_back(std::make_unique<Rocket>(1.0f, 0.5f));
    objects.emplace_back(std::make_unique<Rocket>(1.5f, 0.5f));
  }
}
