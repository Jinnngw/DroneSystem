#ifndef HUMAN_H_
#define HUMAN_H_

#include "IEntity.h"
#include "IStrategy.h"

class Human : public IEntity {
 public:
  /**
   * @brief Drones are created with a name
   * @param obj JSON object containing the drone's information
   */
  Human(JsonObject& obj);

  ~Human();

  /**
   * @brief Updates the Human's state.
   * @param dt The time step for updating the human's position and state.
   */
  void update(double dt);

 private:
  IStrategy* movement = nullptr;
};

#endif
