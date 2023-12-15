#ifndef HUMAN_LOOKING_H_
#define HUMAN_LOOKING_H_

#include "IHumanState.h"

/**
   * @brief Updates the state of the Human when it's looking for a package.
   * @param dt Time step used for updating the state (type: double).
   */
class HumanLooking : public IHumanState {
 public:
  // explicit Looking(Human* human) : IHumanState(human) {}
  HumanLooking(Human* human);
  void update(double dt) override;
   /**
   * @brief Notifies subscribers about a package's location.
   * @param location The location of the package (type: Vector3).
   */
  void notifySubscribers(Vector3 location);

};

#endif