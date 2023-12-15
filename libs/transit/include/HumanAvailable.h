#ifndef HUMAN_AVAILABLE_H_
#define HUMAN_AVAILABLE_H_

#include "IHumanState.h"
#include "Human.h"
#include "Package.h"

class HumanAvailable : public IHumanState {
 public:
  /**
   * @brief Constructor for HumanAvailable state.
   * 
   * Initializes the HumanAvailable state with a reference to the Human object.
   * This state manages the Human's behavior when it is not actively seeking a package.
   * 
   * @param human Pointer to the Human object.
   */
  HumanAvailable(Human* human);
  /**
   * @brief Updates the state of the Human when it's available.
   * 
   * This method is responsible for updating the Human's attributes such as position
   * and potentially changing its state, based on its current state of being available.
   * 
   * @param dt Time step used for updating the state (type: double).
   */
  void update(double dt) override;

};

#endif