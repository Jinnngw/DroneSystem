#ifndef HUMAN_H_
#define HUMAN_H_

#include <vector>

#include "ICarSubscriber.h"
#include "IEntity.h"
#include "IHumanState.h"
#include "IStrategy.h"
#include "PackageDataController.h"

class IHumanState;

class Human : public IEntity {
 public:
  /**
   * @brief Human are created with a name
   * @param obj JSON object containing the human's information
   */
  Human(JsonObject& obj);

  ~Human();

  void update(double dt);

  void changeState(IHumanState* state);

  IStrategy* getMovement();

  void setMovement(IStrategy* movement);

  void deleteMovement();

  std::vector<Package*> getPackages();

  std::vector<ICarSubscriber*> getCars();

 private:
  IStrategy* movement = nullptr;
  IHumanState* state;
  PackageDataController* packages;
  std::vector<ICarSubscriber*> cars;
};

#endif
