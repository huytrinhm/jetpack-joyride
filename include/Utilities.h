#ifndef UTILITIES_H
#define UTILITIES_H

#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>

float pixelToMeter(float pixel);
float meterToPixel(float meter);
b2Vec2 pixelToMeter(sf::Vector2f pixel);
sf::Vector2f meterToPixel(b2Vec2 meter);

#endif  // UTILITIES_H