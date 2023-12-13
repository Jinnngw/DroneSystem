/**
 * @file BeelineStrategy.cc
 * @brief Implements the Beeline pathfinding strategy.
 */

#include "BeelineStrategy.h"

/**
 * @brief Constructor for BeelineStrategy.
 * @param pos Starting position.
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
