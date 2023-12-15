#ifndef HUMAN_FOUND_H_
#define HUMAN_FOUND_H_

#include "IHumanState.h"

class HumanFound : public IHumanState {
 public:
  // explicit Found(Human* human) : IHumanState(human) {}
  HumanFound(Human* human);

  void update(double dt) override;
  /**
   * @brief Notifies all Car subscribers about a specific location.
   *
   * @param location The location relevant to the notification.
   */
  void notifySubscribers(Vector3 location);

 private:
  // void moveTowardsPackage();

  // Package* findClosestPackage();
};

#endif