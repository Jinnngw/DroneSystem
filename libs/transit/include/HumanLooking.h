#ifndef HUMAN_LOOKING_H_
#define HUMAN_LOOKING_H_

#include "IHumanState.h"

class HumanLooking : public IHumanState {
 public:
  // explicit Looking(Human* human) : IHumanState(human) {}
  HumanLooking(Human* human);
  void update(double dt) override;
  void notifySubscribers(Vector3 location);

};

#endif