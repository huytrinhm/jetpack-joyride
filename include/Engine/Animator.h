#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <vector>
#include "Component.h"
#include "Engine/GameRenderer.h"

class AnimationFrame {
 public:
  AnimationFrame(sf::IntRect frame,
                 float frameTime,
                 sf::Vector2f offset = {0, 0});

  sf::IntRect frame;
  float frameTime;
  sf::Vector2f offset;
};

class Animation {
 public:
  sf::IntRect GetFrame(int index);
  sf::Vector2f GetOffset(int index);
  int GetFrameCount();
  float GetFrameTime(int index);

  std::vector<AnimationFrame> frames;
};

class Animator : public Component {
 public:
  Animator(const sf::Texture& texture);

  Animation* AddAnimation(const std::string& name);
  Animation& GetAnimation(const std::string& name);
  void PlayAnimation(const std::string& name);
  void Update() override;
  void Render(GameRenderer& renderer);

 private:
  sf::Sprite sprite;
  std::unordered_map<std::string, Animation> animations;
  std::string currentAnimation;
  int currentFrame;
  float elapsedTime;
};

#endif  // ANIMATOR_H
