#include "Player.h"
#include <stdexcept>

Player::Player(float x,
               float y,
               const sf::Texture& texture,
               const std::vector<sf::IntRect>& frames,
               float interval)
    : x(x), y(y), texture(texture), frames(frames), interval(interval) {}

void Player::handleInput(float deltaTime) {
  auto transform = dynamic_cast<Transform*>(modules[0].get());
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
      transform->getPosition().y > 0)
    transform->move(0, -300.f * deltaTime);

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
      transform->getPosition().y < 600 - sprite.getGlobalBounds().height)
    transform->move(0, 300.f * deltaTime);
}

void Player::onCreate() {
  sprite.setTexture(texture);
  modules.push_back(std::make_unique<Transform>(sprite, x, y));
  modules.push_back(std::make_unique<Animator>(sprite, frames, interval));
  modules.push_back(std::make_unique<Renderer>(sprite));
}

void Player::onUpdate(float deltaTime) {
  for (auto& module : modules) {
    module->update(deltaTime);
  }
}

void Player::draw(sf::RenderTarget& target) {
  for (auto& module : modules) {
    if (auto renderer = dynamic_cast<Renderer*>(module.get())) {
      renderer->draw(target);
    }
  }
}
