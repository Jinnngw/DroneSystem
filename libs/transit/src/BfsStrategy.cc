/**
 * @file BfsStrategy.cc
 * @brief Implements the Breadth-First Search strategy.
 */

#include "BfsStrategy.h"
#include "routing/breadth_first_search.h"

/**
 * @brief Constructor for BfsStrategy.
 * @param pos Starting position.
 * @param des Destination position.
 * @param g Pointer to the graph used for BFS routing.
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
