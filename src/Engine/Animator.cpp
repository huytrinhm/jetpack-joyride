#include "Engine/Animator.h"
#include <SFML/Graphics.hpp>
#include "Engine/GameManager.h"
#include "Engine/GameObject.h"

Animator::Animator(const sf::Texture& texture)
    : sprite(texture),
      currentAnimation(""),
      currentFrame(0),
      elapsedTime(0.0f) {}

void Animator::AddAnimation(const std::string& name) {
  animations[name] = Animation();
}

void Animator::AddFrameToAnimation(const std::string& name,
                                   int x,
                                   int y,
                                   int width,
                                   int height,
                                   float frameTime) {
  if (animations.find(name) != animations.end()) {
    animations[name].AddFrame(sf::IntRect(x, y, width, height), frameTime);
  }
}

void Animator::PlayAnimation(const std::string& name) {
  if (animations.find(name) != animations.end()) {
    currentAnimation = name;
    currentFrame = 0;
    elapsedTime = 0.0f;
    sprite.setTextureRect(animations[name].GetFrame(0));
  }
}

void Animator::Start() {
  // Initialization code if needed
}

void Animator::Update() {
  if (currentAnimation.empty())
    return;

  elapsedTime += GameManager::Instance().deltaTime;
  if (elapsedTime >= animations[currentAnimation].GetFrameTime(currentFrame)) {
    elapsedTime = 0.0f;
    currentFrame =
        (currentFrame + 1) % animations[currentAnimation].GetFrameCount();
    sprite.setTextureRect(animations[currentAnimation].GetFrame(currentFrame));
  }
  sprite.setPosition(Component::gameObject->transform.position);
  GameManager::Instance().renderTarget->draw(sprite);
}
