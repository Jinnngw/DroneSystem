/**
 * @file DijkstraStrategy.cc
 * @brief Implements the Dijkstra pathfinding strategy.
 */

#include "DijkstraStrategy.h"
#include "routing/dijkstra.h"

/**
 * @brief Constructor for DijkstraStrategy.
 * @param pos Starting position.
 * @param des Destination position.
 * @param g Pointer to the graph used for Dijkstra routing.
 */
DijkstraStrategy::DijkstraStrategy(Vector3 pos, Vector3 des,
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
  path = g->GetPath(start, end, routing::Dijkstra::Instance());
}
