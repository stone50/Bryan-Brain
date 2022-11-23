#include <cstdlib>

#include "Utils.h"

const float Utils::RAND_FACTOR = 2.0f / RAND_MAX;

float Utils::random() {
	return (rand() * RAND_FACTOR) - 1;
}