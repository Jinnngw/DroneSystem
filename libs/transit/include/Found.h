#ifndef FOUND_H_
#define FOUND_H_

#include "IHumanState.h"

class Found : public IHumanState {
 public:
  explicit Found(Human* human) : IHumanState(human) {}

  void update(double dt) override;

  void notifySubscribers(Vector3 location);

 private:
  void moveTowardsPackage();

  Package* findClosestPackage();
};

#endif
