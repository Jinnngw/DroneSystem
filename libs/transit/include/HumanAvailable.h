#ifndef HUMAN_AVAILABLE_H_
#define HUMAN_AVAILABLE_H_

#include "IHumanState.h"
#include "Human.h"
#include "Package.h"

class HumanAvailable : public IHumanState {
 public:

  HumanAvailable(Human* human);

  void update(double dt) override;

};

#endif