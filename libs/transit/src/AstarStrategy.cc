/**
 * @file AstarStrategy.cc
 * @brief Implements the A* pathfinding strategy.
 */

#include "AstarStrategy.h"
#include "routing/astar.h"


/**
 * @brief Constructor for AstarStrategy.
 * @param pos Starting position.
 * @param des Destination position.
 * @param g Pointer to the graph used for A* routing.
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
