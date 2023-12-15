#ifndef HUMAN_H_
#define HUMAN_H_

#include <vector>

#include "ICarSubscriber.h"
#include "IEntity.h"
#include "IHumanState.h"
#include "IStrategy.h"
#include "IObserver.h"
#include "PackageDataController.h"
#include "Package.h"
#include "SimulationModel.h"
#include "IHumanPublisher.h"
#include "math/vector3.h"

class IHumanState;
/**
 * @class Human
 * @brief Represents a human in a physical system. humans move using euler
 * integration based on a specified velocity and direction.
 */
class Human : public IEntity, public IHumanPublisher {
 public:
  /**
   * @brief Human are created with a name
   * @param obj JSON object containing the human's information
   */
  Human(JsonObject& obj);
  /**
   * @brief Destructor for Human class
   */
  ~Human();
  /**
   * @brief Retrieves the next destination for the Human.
   *
   * This method is used to update the Human's next destination based on the current situation
   * or state in the simulation.
   */
  void getNextDestination();
  /**
   * @brief Updates the human's position
   * @param dt Delta time (type: double)
   */
  void update(double dt);
  /**
   * @brief Changes the current state of the Human.
   *
   * @param state New state to be set for the Human.
   */
  void changeState(IHumanState* state);
  /**
  * @brief Retrieves the current movement strategy of the human.
  * @return Pointer to the current IStrategy object.
  */
  IStrategy* getMovement();
  /**
  * @brief Sets the movement strategy for the human.
  * @param movement Pointer to the IStrategy to be set.
  */
  void setMovement(IStrategy* movement);
  /**
   * @brief Deletes the current movement strategy of the Human.
   *
   * This method is used to clean up the movement strategy when it is no longer needed.
   */
  void deleteMovement();
  /**
   * @brief Retrieves the list of packages known to the Human.
   *
   * @return A vector containing pointers to the packages.
   */
  std::vector<Package*> getPackages();
  /**
  * @brief Retrieves the package currently assigned to the human.
  * @return Pointer to the assigned Package object.
  */
  Package* getPackage();

  void setPackage(Package* package);

  SimulationModel* getModel();
  /**
   * @brief Retrieves the list of Car subscribers known to the Human.
   *
   * @return A vector containing pointers to the Car subscribers.
   */
  std::vector<ICarSubscriber*> getCars();
   /**
   * @brief Determines the next delivery task for the Human.
   *
   * This method is used to update the Human's delivery task based on the current simulation state.
   */
  void getNextDelivery();

    // EXTENSION 1 subscription functions
  
  /**
   * @brief Subscribes a car subscriber to receive notifications from this Human instance.
   * @param observer A pointer to an instance of ICarSubscriber that wishes to subscribe.
   */
  void subscribe(ICarSubscriber* observer);
  /**
   * @brief Unsubscribes a car subscriber from receiving notifications from this Human instance.
   * @param observer A pointer to an instance of ICarSubscriber that wishes to unsubscribe.
   */
  void unsubscribe(ICarSubscriber* observer);
   /**
   * @brief Notifies all Car subscribers about a specific location.
   *
   * @param location The location relevant to the notification.
   */
  void notifySubscribers(Vector3 location);
  /**
   * @brief Updates the Car subscribers based on the Human's current state and position.
   */
  void updateSubscribers();
  /**
   * @brief Adds a package to the Human's list of found packages.
   *
   * @param package Pointer to the package that has been found.
   */
  void addFoundPackage(Package* package);


    // EXTENSION 2 subscription functions
   /**
   * @brief Subscribes an observer to receive notifications from this Human instance.
   * @param observer A pointer to an instance of the Observer class that wishes to subscribe.
   */
  void subscribe(IObserver* observer);
  /**
   * @brief Unsubscribes an observer from receiving notifications from this Human instance.
   * @param observer A pointer to an instance of the Observer class that wishes to subscribe.
   */
  void unsubscribe(IObserver* observer);
  /**
   * @brief Notifies all subscribed observers about a change in the Human's state.
    * @return A boolean indicating the success of the notification process.
    *         - Returns true if the notification was successful.
    *         - Returns false if there was an issue during the notification process.
   */
  bool notifySubscribers(std::string context);

 private:
    IStrategy* movement = nullptr;
    IHumanState* state;
    PackageDataController* packages;
    Package* package = nullptr;
    std::vector<Package*> foundPackages;
};

#endif