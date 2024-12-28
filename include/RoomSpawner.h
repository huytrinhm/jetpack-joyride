#ifndef ROOM_SPAWNER_H
#define ROOM_SPAWNER_H

#include "ScrollerSpawner.h"

class RoomSpawner : public ScrollerSpawner {
 public:
  RoomSpawner();

 private:
  void Spawn() override;
  void SpawnZapper();
  void SpawnVehiclePickup();
};

#endif  // ROOM_SPAWNER_H