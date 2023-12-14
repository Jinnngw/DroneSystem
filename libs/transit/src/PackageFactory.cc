#include "PackageFactory.h"

/**
 * @brief Creates a new Package entity based on provided JSON data.
 * @param entity JSON object containing initialization data for a package.
 * @return Pointer to the newly created IEntity (Package) object, or nullptr if creation fails.
 */
IEntity* PackageFactory::CreateEntity(JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("package") == 0) {
    std::cout << "Package Created" << std::endl;
    return new Package(entity);
  }
  return nullptr;
}
