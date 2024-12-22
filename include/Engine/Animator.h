#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <vector>
#include "Component.h"
#include "Engine/GameRenderer.h"

class Animation {
 public:
  Animation() = default;  // Default constructor

  void AddFrame(const sf::IntRect& frame, float frameTime) {
    frames.push_back(frame);
    frameTimes.push_back(frameTime);
  }

  const sf::IntRect& GetFrame(int index) const { return frames[index]; }
  int GetFrameCount() const { return frames.size(); }
  float GetFrameTime(int index) const { return frameTimes[index]; }

 private:
  std::vector<sf::IntRect> frames;
  std::vector<float> frameTimes;
};

class Animator : public Component {
 public:
  Animator(const sf::Texture& texture);

  void AddAnimation(const std::string& name);
  void AddFrameToAnimation(const std::string& name,
                           int x,
                           int y,
                           int width,
                           int height,
                           float frameTime);
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
