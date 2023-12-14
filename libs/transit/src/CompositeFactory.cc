/**
 * @file CompositeFactory.cc
 * @brief Implementation of the Composite Factory pattern for entity creation.
 */

#include "CompositeFactory.h"

/**
 * @brief Creates an entity based on a given type.
 * @param entity Entity details in JsonObject form.
 * @return Pointer to created IEntity object, or nullptr if type does not match.
 */
IEntity* CompositeFactory::CreateEntity(JsonObject& entity) {
  for (int i = 0; i < componentFactories.size(); i++) {
    IEntity* createdEntity = componentFactories.at(i)->CreateEntity(entity);
    if (createdEntity != nullptr) {
      return createdEntity;
    }
  }
  std::cout << "[!] Error: Type mismatched..." << std::endl;
  return nullptr;
}

/**
 * @brief Adds a new factory to the composite factory.
 * @param factoryEntity Factory to be added.
 */
void CompositeFactory::AddFactory(IEntityFactory* factoryEntity) {
  componentFactories.push_back(factoryEntity);
}

/**
 * @brief Destructor for CompositeFactory, deallocates component factories.
 */
CompositeFactory::~CompositeFactory() {
  for (int i = 0; i < componentFactories.size(); i++) {
    delete componentFactories[i];
  }
}
