#include "Player.h"
#include "Engine/Animator.h"

Player::Player(const std::string& name) : GameObject(name) {
  texture.loadFromFile("assets/barry.png");
  auto animator = AddComponent<Animator>(texture);
  animator->AddAnimation("idle");
  animator->AddFrameToAnimation("idle", 0, 0, 32, 48, 0.1f);
  animator->AddFrameToAnimation("idle", 32, 0, 32, 48, 0.1f);
  animator->AddFrameToAnimation("idle", 64, 0, 32, 48, 0.1f);
  animator->AddFrameToAnimation("idle", 96, 0, 32, 48, 0.1f);
  animator->PlayAnimation("idle");
}

void Player::Start() {
  transform.position = sf::Vector2f(0, 0);
}

void Player::Update() {}
