#include "RoomSpawner.h"
#include "Config.h"
#include "Utilities.h"
#include "Zapper.h"

RoomSpawner::RoomSpawner() : ScrollerSpawner(400) {}

void RoomSpawner::Spawn() {
  ZapperType type = static_cast<ZapperType>(rand() % 4);
  int length = rand() % 6 + 1;
  float w, h;
  if (type == ZAPPER_HORIZONTAL) {
    w = 16 * length + 2 * 32;
    h = 32;
  } else if (type == ZAPPER_VERTICAL) {
    w = 32;
    h = 16 * length + 2 * 32;
  } else {
    w = 16 * length + 2 * 32;
    h = 16 * length + 2 * 32;
  }
  float remainingW = spawnDistance - w;
  float remainingH = WORLD_HEIGHT - 88 - h;
  float dx = randomIntInRange(-remainingW / 2, remainingW / 2);
  float dy = randomIntInRange(-remainingH / 2, remainingH / 2);
  float x = WORLD_WIDTH + 200 + dx;
  float y = WORLD_HEIGHT / 2 + dy;

  objects.emplace_back(
      std::make_unique<Zapper>(type, sf::Vector2f(x, y), length));
}
