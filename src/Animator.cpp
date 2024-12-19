#include "Animator.h"

Animator::Animator(sf::Sprite& sprite,
                   const std::vector<sf::IntRect>& frames,
                   float interval)
    : sprite(sprite),
      frames(frames),
      interval(interval),
      timer(0),
      currentFrame(0) {}

void Animator::update(float deltaTime) {
  timer += deltaTime;
  if (timer >= interval) {
    currentFrame = (currentFrame + 1) % frames.size();
    sprite.setTextureRect(frames[currentFrame]);
    timer = 0.f;
  }
}
