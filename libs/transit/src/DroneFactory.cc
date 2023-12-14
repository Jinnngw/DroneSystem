#include "DroneFactory.h"

/**
 * @brief Creates a new Drone entity based on provided JSON data.
 * @param entity JSON object containing initialization data for a drone.
 * @return Pointer to the newly created IEntity (Drone) object.
 */
IEntity* DroneFactory::CreateEntity(JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("drone") == 0) {
    std::cout << "Drone Created" << std::endl;
    return new Drone(entity);
  }
  return nullptr;
}
