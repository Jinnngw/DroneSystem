/**
 * @file PackageFactory.cc
 * @brief Implementation of the Factory pattern for creating Package objects.
 */

#include "PackageFactory.h"

/**
 * @brief Creates a Package entity based on a given type.
 * @param entity Entity details in JsonObject form.
 * @return Pointer to created Package object, or nullptr if type does not match.
 */
IEntity* PackageFactory::CreateEntity(JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("package") == 0) {
    std::cout << "Package Created" << std::endl;
    return new Package(entity);
  }
  return nullptr;
}
