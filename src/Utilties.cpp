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
