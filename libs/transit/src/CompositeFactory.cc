/**
 * @file CompositeFactory.cc
 * @brief Implementation of the CompositeFactory class for creating entities.
 */

#include "CompositeFactory.h"

/**
 * @brief Creates an entity based on the type specified in the JSON object.
 * @param entity JSON object containing entity specifications.
 * @return Pointer to the created entity, or nullptr if creation fails.
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
 * @brief Adds a factory to the composite factory.
 * @param factoryEntity Pointer to the factory to be added.
 */
void CompositeFactory::AddFactory(IEntityFactory* factoryEntity) {
  componentFactories.push_back(factoryEntity);
}

/**
 * @brief Destructor for the CompositeFactory class.
 */
CompositeFactory::~CompositeFactory() {
  for (int i = 0; i < componentFactories.size(); i++) {
    delete componentFactories[i];
  }
}
