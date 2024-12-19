#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "Animator.h"
#include "Entity.h"
#include "Module.h"
#include "Renderer.h"
#include "Transform.h"

class Player : public Entity {
 public:
  Player(float x,
         float y,
         const sf::Texture& texture,
         const std::vector<sf::IntRect>& frames,
         float interval);

  void handleInput(float deltaTime);
  void onCreate() override;
  void onUpdate(float deltaTime) override;
  void draw(sf::RenderTarget& target);

 private:
  sf::Sprite sprite;
  std::vector<std::unique_ptr<Module>> modules;
  float x, y;
  const sf::Texture& texture;
  std::vector<sf::IntRect> frames;
  float interval;
};

#endif
