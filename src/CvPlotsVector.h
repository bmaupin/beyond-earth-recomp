#pragma once

#include "Fireworks/FFastVector.h"

// The target's typedef uses the native plot allocation pool, not the SDK default.
typedef FStaticVector<int, 14592, true, 1256, 0> CvPlotsVector;
