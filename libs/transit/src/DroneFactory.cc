/**
 * @file DroneFactory.cc
 * @brief Implementation of the Factory pattern for creating Drone objects.
 */

#include "DroneFactory.h"

/**
 * @brief Creates a Drone entity based on a given type.
 * @param entity Entity details in JsonObject form.
 * @return Pointer to created Drone object, or nullptr if type does not match.
 */
IEntity* DroneFactory::CreateEntity(JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("drone") == 0) {
    std::cout << "Drone Created" << std::endl;
    return new Drone(entity);
  }
  return nullptr;
}
