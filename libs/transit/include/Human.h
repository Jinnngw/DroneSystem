#ifndef HUMAN_H_
#define HUMAN_H_

#include <vector>

#include "ICarSubscriber.h"
#include "IEntity.h"
#include "IHumanState.h"
#include "IStrategy.h"
#include "PackageDataController.h"
#include "Package.h"
#include "SimulationModel.h"
#include "IHumanPublisher.h"
#include "math/vector3.h"

class IHumanState;

class Human : public IEntity, public IHumanPublisher {
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

  Package* getPackage();

  void setPackage(Package* package);

  SimulationModel* getModel();

  std::vector<ICarSubscriber*> getCars();

  void getNextDelivery();

  void subscribe(ICarSubscriber* observer);
  void unsubscribe(ICarSubscriber* observer);
  void notifySubscribers(Vector3 location);
  void updateSubscribers();

  void addFoundPackage(Package* package);


  private:
    IStrategy* movement = nullptr;
    IHumanState* state;
    PackageDataController* packages;
    Package* package = nullptr;
    std::vector<Package*> foundPackages;
};

#endif
