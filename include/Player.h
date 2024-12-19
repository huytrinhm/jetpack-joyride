#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Engine/GameObject.h"

class Player : public GameObject {
 public:
  Player(const std::string& name = "Player");

  void Start() override;
  void Update() override;

  sf::Texture texture;
};

#endif  // PLAYER_H
