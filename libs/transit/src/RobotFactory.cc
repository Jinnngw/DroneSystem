/**
 * @file RobotFactory.cc
 * @brief Implementation of the Factory pattern for creating Robot objects.
 */

#include "RobotFactory.h"

/**
 * @brief Creates a Robot entity based on a given type.
 * @param entity Entity details in JsonObject form.
 * @return Pointer to created Robot object, or nullptr if type does not match.
 */
IEntity* RobotFactory::CreateEntity(JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("robot") == 0) {
    std::cout << "Robot Created" << std::endl;
    return new Robot(entity);
  }
  return nullptr;
}
