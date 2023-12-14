/**
 * @file HumanFactory.cc
 * @brief Implementation of the Factory pattern for creating Human objects.
 */

#include "HumanFactory.h"

/**
 * @brief Creates a Human entity based on a given type.
 * @param entity Entity details in JsonObject form.
 * @return Pointer to created Human object, or nullptr if type does not match.
 */
IEntity* HumanFactory::CreateEntity(JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("human") == 0) {
    std::cout << "Human Created" << std::endl;
    return new Human(entity);
  }
  return nullptr;
}
