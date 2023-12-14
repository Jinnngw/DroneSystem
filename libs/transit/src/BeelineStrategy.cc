/**
 * @file BeelineStrategy.cc
 * @brief Implementation of a direct path (beeline) strategy.
 */

#include "BeelineStrategy.h"

/**
 * @brief Constructs the Beeline Strategy object.
 * @param pos Initial position.
 * @param des Destination position.
 */
BeelineStrategy::BeelineStrategy(Vector3 pos, Vector3 des): PathStrategy({
    {
      static_cast<float>(pos[0]),
      static_cast<float>(pos[1]),
      static_cast<float>(pos[2])
    },
    {
      static_cast<float>(des[0]),
      static_cast<float>(des[1]),
      static_cast<float>(des[2])
    }
  }) {}
