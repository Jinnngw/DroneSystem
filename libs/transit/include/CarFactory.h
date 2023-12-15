#ifndef CAR_FACTORY_H_
#define CAR_FACTORY_H_

#include <vector>

#include "Car.h"
#include "IEntityFactory.h"

/**
 *@brief Car Factory to produce car class.
 **/
class CarFactory : public IEntityFactory {
 public:
  /**
   * @brief Destructor for carFactory class.
   **/
  virtual ~CarFactory() {}
  /**
   * @brief Creates entity using the given JSON object, if possible.
   * @param entity - JsonObject to be used to create the new entity.
   * @return Entity that was created if it was created successfully, or a
   * nullpointer if creation failed.
   **/
  IEntity* CreateEntity(JsonObject& entity);
};

#endif