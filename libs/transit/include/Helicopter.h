#ifndef Helicopter_H_
#define Helicopter_H_

#include "IEntity.h"
#include "IStrategy.h"

class Helicopter : public IEntity {
 public:
  /**
   * @brief Helicopter are created with a name
   * @param obj JSON object containing the drone's information
   */
  Helicopter(JsonObject& obj);

  ~Helicopter();

  /**
   * @brief Updates the Helicopter's state.
   * @param dt The time step for updating the helicopter's position and state.
   */
  void update(double dt);

 private:
  IStrategy* movement = nullptr;
};

#endif
