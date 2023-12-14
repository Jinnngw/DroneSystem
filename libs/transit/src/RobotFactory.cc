#include "RobotFactory.h"

/**
 * @brief Creates a new Robot entity based on provided JSON data.
 * @param entity JSON object containing initialization data for a robot.
 * @return Pointer to the newly created IEntity (Robot) object, or nullptr if creation fails.
 */
IEntity* RobotFactory::CreateEntity(JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("robot") == 0) {
    std::cout << "Robot Created" << std::endl;
    return new Robot(entity);
  }
  return nullptr;
}
