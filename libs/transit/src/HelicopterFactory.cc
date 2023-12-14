#include "HelicopterFactory.h"

/**
 * @brief Creates a new Helicopter entity based on provided JSON data.
 * @param entity JSON object containing initialization data for a helicopter.
 * @return Pointer to the newly created IEntity (Helicopter) object, or nullptr if creation fails.
 */
IEntity* HelicopterFactory::CreateEntity(JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("helicopter") == 0) {
    std::cout << "Helicopter Created" << std::endl;
    return new Helicopter(entity);
  }
  return nullptr;
}
