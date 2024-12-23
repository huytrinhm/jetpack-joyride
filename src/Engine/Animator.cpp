#include "Engine/Animator.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Engine/GameManager.h"
#include "Engine/GameObject.h"

AnimationFrame::AnimationFrame(sf::IntRect frame,
                               float frameTime,
                               sf::Vector2f offset)
    : frame(frame), frameTime(frameTime), offset(offset) {}

sf::IntRect Animation::GetFrame(int index) {
  return frames[index].frame;
}

sf::Vector2f Animation::GetOffset(int index) {
  return frames[index].offset;
}

int Animation::GetFrameCount() {
  return frames.size();
}

float Animation::GetFrameTime(int index) {
  return frames[index].frameTime;
}

Animator::Animator(const sf::Texture& texture)
    : sprite(texture),
      currentAnimation(""),
      currentFrame(0),
      elapsedTime(0.0f) {}

void Animator::SetTexture(const sf::Texture& texture) {
  sprite.setTexture(texture);
}

Animation* Animator::AddAnimation(const std::string& name) {
  animations[name] = Animation();
  return &animations[name];
}

Animation& Animator::GetAnimation(const std::string& name) {
  if (animations.find(name) != animations.end()) {
    return animations[name];
  } else {
    throw std::runtime_error("Animation not found: " + name);
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

void Animator::Update() {
  if (currentAnimation.empty())
    return;

  float frameTime = animations[currentAnimation].GetFrameTime(currentFrame);

  elapsedTime += GameManager::Instance().deltaTime;
  while (elapsedTime >= frameTime) {
    elapsedTime -= frameTime;
    currentFrame =
        (currentFrame + 1) % animations[currentAnimation].GetFrameCount();

    frameTime = animations[currentAnimation].GetFrameTime(currentFrame);
  }
  sf::IntRect frame = animations[currentAnimation].GetFrame(currentFrame);
  sf::Vector2f offset = animations[currentAnimation].GetOffset(currentFrame);

  sprite.setTextureRect(frame);
  sprite.setPosition(Component::gameObject->transform.position + offset -
                     sf::Vector2f{frame.width / 2.f, frame.height / 2.f});
  sprite.setScale(Component::gameObject->transform.scale);
  sprite.setRotation(Component::gameObject->transform.rotation);
}

void Animator::Render(GameRenderer& renderer) {
  if (currentAnimation.empty())
    return;

  renderer.AddDrawable(2, &sprite);
}
