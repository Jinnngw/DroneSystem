#ifndef CAR_H_
#define CAR_H_

#include <stdio.h>

#include "IEntity.h"
#include "IStrategy.h"
#include "math/vector3.h"
#include "ICarState.h"
#include "ICarSubscriber.h"
#include "Package.h"
/**
 * @class Car
 * @brief Represents a car in a physical system. cars move using euler
 * integration based on a specified velocity and direction.
 */
class Car : public IEntity, public ICarSubscriber{
 public:
  /**
   * @brief Cars are created with a name
   * @param obj JSON object containing the car's information
   * @param initialState Car's initial State (type:ICarState)
   */
  Car(JsonObject& obj, ICarState* initialState);

  /**
   * @brief Destructor
   */
  ~Car();

  /**
   * @brief Updates the Car's position
   * @param dt Delta time (type: double)
   */
  void update(double dt);

  /**
   * @brief Gets the next destination in the scheduler
   */
  void getNextDestination();

  /**
   * @brief Change the state of car
   * @param state Car's state(type: ICarState)
   */
  void changeState(ICarState* state);

  /**
   * @brief Removing the copy constructor operator
   * so that cars cannot be copied.
   */
  Car(const Car& car) = delete;


  /**
   * @brief Removing the assignment operator
   * so that cars cannot be copied.
   */
  Car& operator=(const Car& car) = delete;

 private:
  ICarState* state;
  IStrategy* toNextDestination = nullptr;
  Package* package = nullptr;

  // XYZ Bounding limits
  const double minX = -1400.0;
  const double maxX = 1500.0;
  const double minY = 270.0;
  const double maxY = 270.0;
  const double minZ = -800.0;
  const double maxZ = 800.0;

  Vector3 destination;
};

#endif