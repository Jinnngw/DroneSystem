#ifndef CAR_H_
#define CAR_H_

#include <stdio.h>

#include "IEntity.h"
#include "IStrategy.h"
#include "math/vector3.h"

/**
 * @class Car
 * @brief Represents a car in a physical system. cars move using euler
 * integration based on a specified velocity and direction.
 */
class Car : public IEntity {
 public:
  /**
   * @brief Cars are created with a name
   * @param obj JSON object containing the car's information
   */
  Car(JsonObject& obj);

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
   * @brief Subscribes an observer to receive notifications from this Car instance.
   * @param observer A pointer to an instance of the Observer class that wishes to subscribe.
   */
  void subscribe(IObserver* observer);

  /**
   * @brief Unsubscribes an observer from receiving notifications from this Car instance.
   * @param observer A pointer to an instance of the Observer class that wishes to subscribe.
   */
  void unsubscribe(IObserver* observer);

  /**
   * @brief Notifies all subscribed observers about a change in the Car's state.
    * @return A boolean indicating the success of the notification process.
    *         - Returns true if the notification was successful.
    *         - Returns false if there was an issue during the notification process.
   */
  bool notifySubscribers(std::string context);

 private:
  IStrategy* toNextDestination = nullptr;
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