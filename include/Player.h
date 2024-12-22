#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Engine/GameObject.h"
#include "Engine/GameRenderer.h"

class Player : public GameObject {
 public:
  Player(const std::string& name = "Player");

  void Start() override;
  void Update() override;
  void Render(GameRenderer& renderer) override;
};

#endif  // PLAYER_H
