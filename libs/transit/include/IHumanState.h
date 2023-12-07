#ifndef IHUMANSTATE_H_
#define IHUMANSTATE_H_

#include "Human.h"

class Human;

class IHumanState {
 public:
  // explicit IHumanState(Human* human) : human(human) {}
  // virtual ~IHumanState() = default;
  virtual void update(double dt) = 0;

 protected:
  Human* human;
};

#endif  // IHUMANSTATE_H_
