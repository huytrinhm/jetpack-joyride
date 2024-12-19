#include "Player.h"
#include "Engine/Animator.h"

Player::Player(const std::string& name) : GameObject(name) {}

void Player::Start() {
  auto texture = std::make_shared<sf::Texture>();
  texture->loadFromFile("path/to/spritesheet.png");
  AddComponent<Animator>(*texture);
}

void Player::Update() {}
