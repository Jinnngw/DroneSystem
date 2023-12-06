#ifndef LOOKING_H_
#define LOOKING_H_

#include "IHumanState.h"

class Looking : public IHumanState {
 public:
  explicit Looking(Human* human) : IHumanState(human) {}

  void update(double dt) override;
};

#endif
