#include "commons.h"

static bool seed = false;

int randomInt(int min, int max) {
  if (!seed) {
    srand((unsigned int) time(NULL));
    seed = true;
  }
  return (rand() % (max - min + 1)) + min;
}

float randomFloat(float min, float max) {
  float scale = rand() / (float) RAND_MAX;
  return min + scale * (max - min);
}

int clamp(int value, int min, int max) {
  int newValue = value;
  if (value < min) {
    value = min;
  } else if (value > max) {
    value = max;
  }

  return newValue;
}
