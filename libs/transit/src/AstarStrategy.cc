/**
 * @file AstarStrategy.cc
 * @brief Implementation of A* pathfinding strategy.
 */

#include "AstarStrategy.h"
#include "routing/astar.h"

/**
 * @brief Constructs the A* Strategy object.
 * @param pos Initial position.
 * @param des Destination position.
 * @param g Graph on which A* is applied.
 */
AstarStrategy::AstarStrategy(Vector3 pos, Vector3 des,
                             const routing::IGraph* g) {
  std::vector<float> start = {
    static_cast<float>(pos[0]),
    static_cast<float>(pos[1]),
    static_cast<float>(pos[2])
  };
  std::vector<float> end = {
    static_cast<float>(des[0]),
    static_cast<float>(des[1]),
    static_cast<float>(des[2])
  };
  path = g->GetPath(start, end, routing::AStar::Default());
}
