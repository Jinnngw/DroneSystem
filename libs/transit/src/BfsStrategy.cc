/**
 * @file BfsStrategy.cc
 * @brief Implementation of Breadth-First Search pathfinding strategy.
 */

#include "BfsStrategy.h"
#include "routing/breadth_first_search.h"

/**
 * @brief Constructs the BFS Strategy object.
 * @param pos Initial position.
 * @param des Destination position.
 * @param g Graph on which BFS is applied.
 */
BfsStrategy::BfsStrategy(Vector3 pos, Vector3 des,
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
  path = g->GetPath(start, end, routing::BreadthFirstSearch::Default());
}
