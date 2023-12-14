/**
 * @file DijkstraStrategy.cc
 * @brief Implementation of Dijkstra pathfinding strategy.
 */

#include "DijkstraStrategy.h"
#include "routing/dijkstra.h"

/**
 * @brief Constructs the Dijkstra Strategy object.
 * @param pos Initial position.
 * @param des Destination position.
 * @param g Graph on which Dijkstra's algorithm is applied.
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
