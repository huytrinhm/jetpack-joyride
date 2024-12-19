#ifndef UTILITIES_H
#define UTILITIES_H

#include <cstdlib>

inline float getRandomFloat(float min, float max) {
  return min + static_cast<float>(rand()) /
                   (static_cast<float>(RAND_MAX / (max - min)));
}

#endif
