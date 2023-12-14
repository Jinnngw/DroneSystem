#include "HumanFactory.h"

/**
 * @brief Creates a new Human entity based on provided JSON data.
 * @param entity JSON object containing initialization data for a human.
 * @return Pointer to the newly created IEntity (Human) object, or nullptr if creation fails.
 */
IEntity* HumanFactory::CreateEntity(JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("human") == 0) {
    std::cout << "Human Created" << std::endl;
    return new Human(entity);
  }
  return nullptr;
}
