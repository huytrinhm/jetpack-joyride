#include "Player.h"
#include "Engine/Animator.h"

Player::Player(const std::string& name) : GameObject(name) {
  texture.loadFromFile("assets/barry.png");
  auto animator = AddComponent<Animator>(texture);

  animator->AddAnimation("running");
  animator->AddFrameToAnimation("running", 0, 0, 32, 48, 0.1f);
  animator->AddFrameToAnimation("running", 32, 0, 32, 48, 0.1f);
  animator->AddFrameToAnimation("running", 64, 0, 32, 48, 0.1f);
  animator->AddFrameToAnimation("running", 96, 0, 32, 48, 0.1f);

  animator->AddAnimation("flying");
  animator->AddFrameToAnimation("flying", 0, 48, 32, 48, 0.1f);
  animator->AddFrameToAnimation("flying", 32, 48, 32, 48, 0.1f);
  animator->AddFrameToAnimation("flying", 64, 48, 32, 48, 0.1f);
  animator->AddFrameToAnimation("flying", 96, 48, 32, 48, 0.1f);

  animator->AddAnimation("falling");
  animator->AddFrameToAnimation("falling", 0, 96, 32, 48, 0.1f);
  animator->AddFrameToAnimation("falling", 32, 96, 32, 48, 0.1f);
  animator->AddFrameToAnimation("falling", 64, 96, 32, 48, 0.1f);
  animator->AddFrameToAnimation("falling", 96, 96, 32, 48, 0.1f);

  animator->AddAnimation("landing");
  animator->AddFrameToAnimation("landing", 0, 144, 32, 48, 0.1f);
  animator->AddFrameToAnimation("landing", 32, 144, 32, 48, 0.1f);
  animator->AddFrameToAnimation("landing", 64, 144, 32, 48, 0.1f);
  animator->AddFrameToAnimation("landing", 96, 144, 32, 48, 0.1f);

  animator->AddAnimation("dead");
  animator->AddFrameToAnimation("dead", 0, 288, 32, 48, 0.1f);
  animator->AddFrameToAnimation("dead", 32, 288, 32, 48, 0.1f);
  animator->AddFrameToAnimation("dead", 64, 288, 32, 48, 0.1f);
  animator->AddFrameToAnimation("dead", 96, 288, 32, 48, 0.1f);

  animator->AddAnimation("laying");
  animator->AddFrameToAnimation("laying", 32, 336, 32, 48, 0.1f);
  animator->AddFrameToAnimation("laying", 0, 336, 32, 48, 0.1f);

  animator->PlayAnimation("laying");
}

void Player::Start() {
  transform.position = sf::Vector2f(0, 0);
}

void Player::Update() {}
