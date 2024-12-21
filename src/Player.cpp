#include "Player.h"
#include "AssetManager.h"
#include "Engine/Animator.h"

Player::Player(const std::string& name) : GameObject(name) {
  auto& texture = AssetManager::Instance().GetTexture("barry");
  auto animator = AddComponent<Animator>(texture);

  animator->AddAnimation("running");
  for (int i = 0; i < 4; i++)
    animator->AddFrameToAnimation("running", i * 48, 0 * 72, 48, 72, 0.1f);

  animator->AddAnimation("flying");
  for (int i = 0; i < 4; i++)
    animator->AddFrameToAnimation("flying", i * 48, 1 * 72, 48, 72, 0.1f);

  animator->AddAnimation("falling");
  for (int i = 0; i < 4; i++)
    animator->AddFrameToAnimation("falling", i * 48, 2 * 72, 48, 72, 0.1f);

  animator->AddAnimation("landing");
  for (int i = 0; i < 4; i++)
    animator->AddFrameToAnimation("landing", i * 48, 3 * 72, 48, 72, 0.1f);

  animator->AddAnimation("dead");
  for (int i = 0; i < 4; i++)
    animator->AddFrameToAnimation("dead", i * 48, 4 * 72, 48, 72, 0.1f);

  animator->AddAnimation("dead_falling");
  for (int i = 0; i < 4; i++)
    animator->AddFrameToAnimation("dead_falling", i * 48, 6 * 72, 48, 72, 0.1f);

  animator->AddAnimation("laying");
  animator->AddFrameToAnimation("laying", 48, 7 * 72, 48, 72, 0.1f);
  animator->AddFrameToAnimation("laying", 0, 7 * 72, 48, 72, 0.1f);

  animator->PlayAnimation("dead_falling");
}

void Player::Start() {
  transform.position = sf::Vector2f(0, 0);
}

void Player::Update() {}
