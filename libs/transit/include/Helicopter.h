#ifndef Helicopter_H_
#define Helicopter_H_

#include "IEntity.h"
#include "IStrategy.h"

/**
 * @class Helicopter
 * @brief Represents a helicopter in the simulation.
 *
 * This class models the behavior and attributes of a helicopter in the 
 * simulation environment. Helicopters can move and interact within the 
 * simulation, similar to other entities.
 */
class Helicopter : public IEntity {
 public:
  /**
   * @brief Helicopter are created with a name
   * @param obj JSON object containing the drone's information
   */
  Helicopter(JsonObject& obj);
  /**
   * @brief Destructor for Helicopter.
   */
  ~Helicopter();
  /**
   * @brief Updates the helicopter's state.
   * 
   * This method is responsible for updating the helicopter's position and state
   * based on its current strategy and the time step provided.
   * 
   * @param dt Time step for the update (type: double).
   */
  void update(double dt);
  /**
   * @brief Subscribes an observer to receive notifications from this Helicopter instance.
   * @param observer A pointer to an instance of the Observer class that wishes to subscribe.
   */
  void subscribe(IObserver* observer);
  /**
   * @brief Unsubscribes an observer from receiving notifications from this Helicopter instance.
   * @param observer A pointer to an instance of the Observer class that wishes to unsubscribe.
   */
  void unsubscribe(IObserver* observer);
  /**
   * @brief Notifies all subscribed observers about a change in the Helicopter's state.
   * @param context A string providing context for the notification.
   * @return True if the notification was successful, false otherwise.
   */
  bool notifySubscribers(std::string context);

 private:
  IStrategy* movement = nullptr;
};

#endif
