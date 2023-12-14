/**
 * @file DfsStrategy.cc
 * @brief Implementation of Depth-First Search pathfinding strategy.
 */

#include "DfsStrategy.h"
#include "routing/depth_first_search.h"

/**
 * @brief Constructs the DFS Strategy object.
 * @param pos Initial position.
 * @param des Destination position.
 * @param g Graph on which DFS is applied.
 */
DfsStrategy::DfsStrategy(Vector3 pos, Vector3 des,
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
  path = g->GetPath(start, end, routing::DepthFirstSearch::Default());
}
