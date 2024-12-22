#include "Player.h"
#include "AssetManager.h"
#include "Engine/Animator.h"
#include "Engine/PhysicBody.h"

Player::Player(const std::string& name) : GameObject(name) {
  auto& texture = AssetManager::Instance().GetTexture("barry");
  auto animator = AddComponent<Animator>(texture);
  Animation* animation = nullptr;

  animation = animator->AddAnimation("running");
  for (int i = 0; i < 4; i++)
    animation->frames.emplace_back(sf::IntRect{i * 48, 0 * 72, 48, 72}, 0.1f,
                                   sf::Vector2f{-5, 13});

  animation = animator->AddAnimation("flying");
  for (int i = 0; i < 4; i++)
    animation->frames.emplace_back(sf::IntRect{i * 48, 1 * 72, 48, 72}, 0.1f,
                                   sf::Vector2f{-5, 13});

  animation = animator->AddAnimation("falling");
  for (int i = 0; i < 4; i++)
    animation->frames.emplace_back(sf::IntRect{i * 48, 2 * 72, 48, 72}, 0.1f,
                                   sf::Vector2f{-5, 13});

  animation = animator->AddAnimation("landing");
  for (int i = 0; i < 4; i++)
    animation->frames.emplace_back(sf::IntRect{i * 48, 3 * 72, 48, 72}, 0.1f,
                                   sf::Vector2f{-5, 13});

  animation = animator->AddAnimation("dead");
  for (int i = 0; i < 4; i++)
    animation->frames.emplace_back(sf::IntRect{i * 48, 4 * 72, 48, 72}, 0.1f,
                                   sf::Vector2f{-5, 13});

  animation = animator->AddAnimation("dead_falling");
  for (int i = 0; i < 4; i++)
    animation->frames.emplace_back(sf::IntRect{i * 48, 6 * 72, 48, 72}, 0.1f,
                                   sf::Vector2f{-5, 13});

  animation = animator->AddAnimation("laying");
  animation->frames.emplace_back(sf::IntRect{48, 7 * 72, 48, 72}, 0.1f,
                                 sf::Vector2f{-5, 13});
  animation->frames.emplace_back(sf::IntRect{0, 7 * 72, 48, 72}, 0.1f,
                                 sf::Vector2f{-5, 13});

  animator->PlayAnimation("running");

  AddComponent<PhysicBody>(b2Vec2{70, 50}, b2Vec2{18, 36});
}

void Player::Start() {
  // transform.position = sf::Vector2f(50, 50);
}

void Player::Update() {}

void Player::Render(GameRenderer& renderer) {
  GetComponent<Animator>()->Render(renderer);
}
