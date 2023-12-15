#ifndef SIMULATION_MODEL_H_
#define SIMULATION_MODEL_H_

#include "CompositeFactory.h"
#include "Drone.h"
#include "IController.h"
#include "IEntity.h"
#include "IObserver.h"
#include "Robot.h"
#include "graph.h"
#include <deque>
#include <map>
#include <set>

//--------------------  Model ----------------------------

/// Simulation Model handling the transit simulation.  The model can communicate
/// with the controller.
/**
 * @brief Class SimulationModel handling the transit simulation. it can
 * communicate with the controller
 **/
class SimulationModel : public IObserver{
 public:
  /**
   * @brief Default constructor that create the SimulationModel object
   **/
  SimulationModel(IController& controller);

  /**
   * @brief Destructor
   */
  ~SimulationModel();

  /**
   * @brief Set the Graph for the SimulationModel
   * @param graph Type IGraph* contain the new graph for SimulationModel
   **/
  void setGraph(const routing::IGraph* graph) { this->graph = graph; }

  /**
   * @brief Creates a new simulation entity
   * @param entity Type JsonObject contain the entity's reference to decide
   *which entity to create
   **/
  IEntity* createEntity(JsonObject& entity);

  /**
   * @brief Removes entity with given ID from the simulation
   * 
   * @param id of the entity to be removed
  */
  void removeEntity(int id);

  /**
   * @brief Schedule a trip for an object in the scene
   * @param detail Type JsonObject contain the entity's reference to schedule
   *the detail of the trip being scheduled
   **/
  void scheduleTrip(JsonObject& details);

  /**
   * @brief Update the simulation
   * @param dt Type double contain the time since update was last called.
   **/
  void update(double dt);

  /**
   * @brief Stops the simulation
   * @return Void
   **/
  void stop();

  /**
   * @brief Returns the graph of the map
   *
   * @returns IGraph* graph pointer
  */
  const routing::IGraph* getGraph();

  /**
   * @brief Sends a notification to the controller about a change in context.
   * @param context Pointer to the IEntity that is the context of the notification.
   * @param moreContext Additional context provided as a string.
   */
  void sendNotif(IEntity* context, std::string moreContext);

  /**
   * @brief Queue of packages scheduled for delivery.
   */
  std::deque<Package*> scheduledDeliveries;

  /**
   * @brief Removes an entity from the simulation using its ID.
   * @param id The unique identifier of the entity to be removed.
   */
  void removeFromSim(int id);

  /**
   * @brief Retrieves a map of all entities in the simulation.
   * @return A map where the key is the entity ID and the value is a pointer to the IEntity.
   */
  std::map<int, IEntity*> getEntities();

 protected:
  IController& controller;
  std::map<int, IEntity*> entities;
  std::set<int> removed;
  const routing::IGraph* graph;
  CompositeFactory entityFactory;
};

#endif
