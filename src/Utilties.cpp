#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include "Config.h"
#include "Utilities.h"

float pixelToMeter(float pixel) {
  return pixel / PIXELS_PER_METER;
}

float meterToPixel(float meter) {
  return meter * PIXELS_PER_METER;
}

b2Vec2 pixelToMeter(sf::Vector2f pixel) {
  return b2Vec2{pixelToMeter(pixel.x), pixelToMeter(pixel.y)};
}

sf::Vector2f meterToPixel(b2Vec2 meter) {
  return sf::Vector2f{meterToPixel(meter.x), meterToPixel(meter.y)};
}

int randomIntInRange(int min, int max) {
  return min + rand() % ((max + 1) - min);
}

float randomFloatInRange(float min, float max) {
  return min + static_cast<float>(rand()) /
                   (static_cast<float>(RAND_MAX / (max - min)));
}

b2Capsule makeHorizontalCapsule(float w, float h) {
  float radius = h / 2;
  float centerOffset = w / 2 - radius;
  b2Capsule capsule = {{-centerOffset, 0}, {centerOffset, 0}, radius};
  return capsule;
}

void updateLetterbox(sf::RenderWindow& window, sf::Sprite& renderSprite) {
  float windowWidth = static_cast<float>(window.getSize().x);
  float windowHeight = static_cast<float>(window.getSize().y);
  float scaleX = windowWidth / WORLD_WIDTH;
  float scaleY = windowHeight / WORLD_HEIGHT;
  float scale = std::min(scaleX, scaleY);
  float offsetX = (windowWidth - WORLD_WIDTH * scale) / 2;
  float offsetY = (windowHeight - WORLD_HEIGHT * scale) / 2;

  window.setView(sf::View(sf::FloatRect(0, 0, windowWidth, windowHeight)));

  renderSprite.setScale(scale, scale);
  renderSprite.setPosition(offsetX, offsetY);
}