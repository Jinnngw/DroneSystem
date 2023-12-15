#ifndef DRONE_H_
#define DRONE_H_

#include <algorithm>
#include <vector>

#include "IEntity.h"
#include "IObserver.h"
#include "IStrategy.h"
#include "PathStrategy.h"
#include "math/vector3.h"

#include "IDroneState.h"

class IDroneState;
class Package;

// Represents a drone in a physical system.
// Drones move using euler integration based on a specified
// velocity and direction.
/**
 * @class Drone
 * @brief Represents a drone in a physical system. Drones move using euler
 * integration based on a specified velocity and direction.
 */
class Drone : public IEntity {
 public:
  /**
   * @brief Drones are created with a name
   * @param obj JSON object containing the drone's information
   */
  Drone(JsonObject& obj);

  /**
   * @brief Destructor
   */
  ~Drone();

  /**
   * @brief Gets the next delivery in the scheduler
   */
  void getNextDelivery();

  /**
   * @brief Updates the drone's position
   * @param dt Delta time
   */
  void update(double dt);

  /**
   * @brief Removing the copy constructor operator
   * so that drones cannot be copied.
   */
  Drone(const Drone& drone) = delete;

  /**
   * @brief Removing the assignment operator
   * so that drones cannot be copied.
   */
  Drone& operator=(const Drone& drone) = delete;

  /**
   * @brief Subscribes an observer to receive notifications from this Drone instance.
   * @param observer A pointer to an instance of the Observer class that wishes to subscribe.
   */
  void subscribe(IObserver* observer);
  /**
   * @brief Unsubscribes an observer from receiving notifications from this Drone instance.
   * @param observer A pointer to an instance of the Observer class that wishes to unsubscribe.
   */
  void unsubscribe(IObserver* observer);
  /**
   * @brief Notifies all subscribed observers about a change in the Drone's state.
   * @param context A string providing context for the notification.
   * @return True if the notification was successful, false otherwise.
   */
  bool notifySubscribers(std::string context);

  // CUSTOM ADDED FUNCTIONS BELOW (ADD TO UML)
  void changeState(IDroneState* state);

  bool getAvailable();
  bool getPickedUp();
  Package* getPackage();
  IStrategy* getToPackage();
  PathStrategy* getToFinalDestination();

  /**
   * @brief Resets the strategy to reach the package to its initial state.
   * 
   * This method is used when the drone needs to abandon its current route to the package
   * and potentially plan a new one.
   */
  void resetToPackage();
  /**
   * @brief Resets the strategy for reaching the final destination after package pickup.
   * 
   * This is typically used when the delivery is complete or if the delivery plan changes.
   */
  void resetToFinalDestination();
  /**
   * @brief Clears the current package assignment from the drone.
   * 
   * This method is used to reset the drone's package-related information, usually after
   * delivery completion or if the package is no longer available for delivery.
   */
  void resetPackage();

  /**
   * @brief Sets the 'picked up' status of the drone.
   * 
   * This method updates the drone's status to reflect whether it has picked up a package.
   * 
   * @param val Boolean value indicating the 'picked up' status.
   */
  void setPickedUp(bool val);
  /**
   * @brief Sets the availability status of the drone.
   * 
   * This method is used to update whether the drone is available for new delivery tasks.
   * 
   * @param val Boolean value indicating the availability status.
   */
  void setAvailable(bool val);

 private:
  bool available = false;
  bool pickedUp = false;
  Package* package = nullptr;
  IStrategy* toPackage = nullptr;
  PathStrategy* toFinalDestination = nullptr;
  std::vector<IObserver*> observers;
  IDroneState* state;
};

#endif  // DRONE_H_
