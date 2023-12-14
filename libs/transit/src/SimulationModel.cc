#include "SimulationModel.h"

#include "DroneFactory.h"
#include "HelicopterFactory.h"
#include "HumanFactory.h"
#include "IEntity.h"
#include "PackageFactory.h"
#include "RobotFactory.h"
#include "HumanFactory.h"
#include "HelicopterFactory.h"
#include "CarFactory.h"


SimulationModel::SimulationModel(IController& controller)
    : controller(controller) {
  entityFactory.AddFactory(new DroneFactory());
  entityFactory.AddFactory(new PackageFactory());
  entityFactory.AddFactory(new RobotFactory());
  entityFactory.AddFactory(new HumanFactory());
  entityFactory.AddFactory(new HelicopterFactory());
  entityFactory.AddFactory(new CarFactory());
}

SimulationModel::~SimulationModel() {
  // Delete dynamically allocated variables
  for (auto& [id, entity] : entities) {
    delete entity;
  }
  delete graph;
}

/**
 * @brief Creates a new entity based on provided JSON data.
 * @param entity JSON object containing initialization data for an entity.
 * @return Pointer to the newly created IEntity object, or nullptr if creation fails.
 */
IEntity* SimulationModel::createEntity(JsonObject& entity) {
  std::string name = entity["name"];
  JsonArray position = entity["position"];
  std::cout << name << ": " << position << std::endl;

  IEntity* myNewEntity = nullptr;
  if (myNewEntity = entityFactory.CreateEntity(entity)) {
    // Call AddEntity to add it to the view
    myNewEntity->linkModel(this);
    controller.addEntity(*myNewEntity);
    entities[myNewEntity->getId()] = myNewEntity;

    // Subscribe the model to the new entity
    myNewEntity->subscribe(this);
  }

  return myNewEntity;
}

/**
 * @brief Removes an entity from the simulation model.
 * @param id The unique ID of the entity to be removed.
 */
void SimulationModel::removeEntity(int id) { removed.insert(id); }

/**
 * @brief Schedules a delivery for an object in the simulation.
 * @param details JSON object containing the delivery details.
 */
void SimulationModel::scheduleTrip(JsonObject& details) {
  std::string name = details["name"];
  JsonArray start = details["start"];
  JsonArray end = details["end"];
  std::cout << name << ": " << start << " --> " << end << std::endl;

  Robot* receiver = nullptr;

  for (auto& [id, entity] : entities) {
    if (name == entity->getName()) {
      if (Robot* r = dynamic_cast<Robot*>(entity)) {
        if (r->requestedDelivery) {
          receiver = r;
          break;
        }
      }
    }
  }

  Package* package = nullptr;

  for (auto& [id, entity] : entities) {
    if (name + "_package" == entity->getName()) {
      if (Package* p = dynamic_cast<Package*>(entity)) {
        if (p->requiresDelivery) {
          package = p;
          break;
        }
      }
    }
  }

  if (receiver && package) {
    package->initDelivery(receiver);
    std::string strategyName = details["search"];
    package->setStrategyName(strategyName);
    scheduledDeliveries.push_back(package);
    controller.sendEventToView("DeliveryScheduled", details);
  }
}

/**
 * @brief Retrieves the graph used for routing in the simulation.
 * @return Pointer to the routing graph.
 */
const routing::IGraph* SimulationModel::getGraph() { return graph; }

/**
 * @brief Updates the simulation.
 * @param dt Time step for the update.
 */
void SimulationModel::update(double dt) {
  for (auto& [id, entity] : entities) {
    entity->update(dt);
    // entity->subscribe(this);
    // std::cout << "!!" << std::endl;
    controller.updateEntity(*entity);

    // std::cout << entity->getName() << " has been updated" << std::endl;
  }
  for (int id : removed) {
    removeFromSim(id);
  }
  removed.clear();
}

/**
 * @brief Stops the simulation.
 */
void SimulationModel::stop(void) { controller.stop(); }

/**
 * @brief Removes an entity from the simulation based on its ID.
 * @param id The unique ID of the entity to be removed.
 */
void SimulationModel::removeFromSim(int id) {
  IEntity* entity = entities[id];
  if (entity) {
    for (auto i = scheduledDeliveries.begin(); i != scheduledDeliveries.end();
         ++i) {
      if (*i == entity) {
        scheduledDeliveries.erase(i);
        break;
      }
    }
    controller.removeEntity(*entity);
    entities.erase(id);
    delete entity;
  }
}

/**
 * @brief Retrieves a map of all entities in the simulation.
 * @return Map of entity IDs to IEntity pointers.
 */
std::map<int, IEntity*> SimulationModel::getEntities(){
  return entities;
}
// Backend to frontend process:
// Concrete publisher of type IEntity calls SimulationModel's sendNotif()
// SimulationModel can use sendEventToView() from transit_service.cc
// because of its controller member variable sendEventToView() will send a
// command along with entity details to main.js's onmessage() function
// onmessage() will format and display details as text in notification bar

/**
 * @brief Sends a notification with additional context.
 * @param context Pointer to the IEntity context.
 * @param moreContext Additional context as a string.
 */
void SimulationModel::sendNotif(IEntity* context, std::string moreContext) {
  // // Print debugging
  // std::cout << "In sendNotif()\n";
  // std::cout << "There are " << this->entities.size() << " entities in the
  // model\n"; std::cout << "The newest entity is a " <<
  // this->entities[entities.size()-1]->getName() << std::endl;

  // Sending to front end
  this->controller.sendEventToView(moreContext, context->getDetails());
}