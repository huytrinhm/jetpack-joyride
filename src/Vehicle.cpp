#include "Vehicle.h"
#include "AssetManager.h"
#include "Engine/PhysicBody.h"
#include "Player.h"
#include "Utilities.h"
#include "box2d/box2d.h"

Vehicle::Vehicle(bool isDestroyable) : isDestroyable(isDestroyable) {}

Jetpack::Jetpack() {
  animator.SetTexture(AssetManager::Instance().GetTexture("barry"));
  Animation* animation = nullptr;

  animation = animator.AddAnimation("running");
  for (int i = 0; i < 4; i++)
    animation->frames.emplace_back(sf::IntRect{i * 48, 0 * 72, 48, 72}, 0.1f,
                                   sf::Vector2f{-5, 13});

  animation = animator.AddAnimation("flying");
  for (int i = 0; i < 4; i++)
    animation->frames.emplace_back(sf::IntRect{i * 48, 1 * 72, 48, 72}, 0.1f,
                                   sf::Vector2f{-5, 13});

  animation = animator.AddAnimation("falling");
  for (int i = 0; i < 4; i++)
    animation->frames.emplace_back(sf::IntRect{i * 48, 2 * 72, 48, 72}, 0.1f,
                                   sf::Vector2f{-5, 13});

  animation = animator.AddAnimation("landing");
  for (int i = 0; i < 4; i++)
    animation->frames.emplace_back(sf::IntRect{i * 48, 3 * 72, 48, 72}, 0.1f,
                                   sf::Vector2f{-5, 13});

  animation = animator.AddAnimation("dead");
  for (int i = 0; i < 4; i++)
    animation->frames.emplace_back(sf::IntRect{i * 48, 4 * 72, 48, 72}, 0.1f,
                                   sf::Vector2f{-5, 13});

  animation = animator.AddAnimation("dead_falling");
  for (int i = 0; i < 4; i++)
    animation->frames.emplace_back(sf::IntRect{i * 48, 6 * 72, 48, 72}, 0.1f,
                                   sf::Vector2f{-5, 13});

  animation = animator.AddAnimation("laying");
  animation->frames.emplace_back(sf::IntRect{48, 7 * 72, 48, 72}, 0.1f,
                                 sf::Vector2f{-5, 13});
  animation->frames.emplace_back(sf::IntRect{0, 7 * 72, 48, 72}, 0.1f,
                                 sf::Vector2f{-5, 13});
}

void Jetpack::Attach(Player* player) {
  this->player = player;
  animator.gameObject = (GameObject*)player;
  player->AddComponent<PhysicBody>(pixelToMeter(player->transform.position),
                                   pixelToMeter({18, 36}));
  animator.PlayAnimation("running");
}

void Jetpack::Update() {
  animator.Update();
}

void Jetpack::Render(GameRenderer& renderer) {
  animator.Render(renderer);
}

void Jetpack::Destroy() {}
